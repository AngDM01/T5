#include <iostream>
#include <cstdlib>
#include <string>

#include "Authorization.hpp"
#include "DBConnection.hpp"
#include "EnvLoader.hpp"
#include "HomePageView.hpp" 
#include "JsonBuilder.hpp"
#include "Logger.hpp"
#include "LoginDTO.hpp"
#include "Request.hpp"
#include "SessionRepository.hpp"
#include "SessionService.hpp"
#include "StaticView.hpp"
#include "TemplateEngine.hpp"
#include "UserModel.hpp"
#include "UserRepository.hpp"
#include "UserService.hpp"
#include "View.hpp"

#define PENDINGSESSIONTIME 5
#define SESSIONTIME 30

class UserRepository;
class UserService;

using namespace std;

string LoadLoginPage()
{
  string loginRoute = "/usr/local/apache2/app/templates/Static/login.html";

  TemplateEngine templateEngine;
	StaticView view(templateEngine, loginRoute);

	string renderedPage = view.Render();
  
	return renderedPage;
}

string AdminLogin(SessionService& sessionService, int userId)
{
  string pendingSession = sessionService.CreatePendingAdminSession(userId, PENDINGSESSIONTIME);

  if (pendingSession.empty() || pendingSession == "0")
  {
    Logger::Warning("[LoginCGI::LoadHomePage]\n Error al obtener la sesión.");

    JsonBuilder response;
    response.addBool("success", false)
        .addString("message", string("Error: no se pudo obtener la sesión."));

    cout << "Content-Type: application/json" << "\r\n\r\n";
    return response.toString();
  }

  int maxAge = PENDINGSESSIONTIME * 60;

  cout << "Set-Cookie: PENDING_ADMIN_SESSION=" << pendingSession
       << "; Max-Age=" << maxAge
       << "; Path=/"
       << "; HttpOnly"
       << "; SameSite=Lax\r\n";

  JsonBuilder response;
  response.addBool("success", true)
      .addBool("requireOTP", true)
      .addString("type", "info")
      .addString("message", string("Segundo factor requerido."));

  cout << "Content-Type: application/json" << "\r\n\r\n";
  return response.toString();
}

string NormalLogin(SessionService& sessionService, int userId)
{
  string sessionId = sessionService.CreateNewUserSession(userId, SESSIONTIME);

  if (sessionId.empty() || sessionId == "0")
  {
    Logger::Warning("[LoginCGI::LoadHomePage]\n Error al obtener la sesión.");

    JsonBuilder response;
    response.addBool("success", false)
        .addString("message", string("Error: no se pudo obtener la sesión."));

    return response.toString();
  }

  int maxAge = SESSIONTIME * 60;

  cout << "Set-Cookie: SESSION_ID=" << sessionId
       << "; Max-Age=" << maxAge
       << "; Path=/"
       << "; HttpOnly"
       << "; SameSite=Lax\r\n";

  JsonBuilder response;
  response.addBool("success", true)
      .addBool("requireOTP", false)
      .addString("message", string("Inicio de sesión exitoso."));

  return response.toString();
}

string LoginAttempt(Request& request)
{
  if (request.GetMethod() != "POST")
  {
    Logger::Info("[LoginCGI::loadLoginPage]\n Método http no válido: " + request.GetMethod());

    JsonBuilder response;
    response.addBool("success", false)
        .addString("message", string("Metodo http no valido."));

    cout << "Content-Type: application/json" << "\r\n\r\n";
    return response.toString();
  }

  string email = request.GetBodyParam("email");
  string pwd = request.GetBodyParam("password");

  LoginDTO loginData(email, pwd);

  try
  {
    auto config = EnvLoader::Load("/usr/local/apache2/app/db.env");
    DBConnection db;
    db.Connect(config["DB_HOST"], config["DB_USER"], config["DB_PASS"], config["DB_NAME"], std::stoi(config["DB_PORT"]));
    UserRepository userRepo(db);
    UserService userService(userRepo);
    int userId = userService.GetUserIdByCredentials(loginData);

    if (userId == 0)
    {
      Logger::Info("[LoginCGI::LoadHomePage]\n Credenciales proporcionadas inválidas: "
          + to_string(userId));

      JsonBuilder response;
      response.addBool("success", false)
          .addString("message", string("Las credenciales son incorrectas."));

      cout << "Content-Type: application/json" << "\r\n\r\n";
      return response.toString();
    }

    if (userId == -1)
    {
      Logger::Error("[LoginCGI::LoadHomePage]\n Error al validar las credenciales: "
          + to_string(userId));

      JsonBuilder response;
      response.addBool("success", false)
          .addString("message", string("Error: no se pudo validar las credenciales."));

      cout << "Content-Type: application/json" << "\r\n\r\n";
      return response.toString();
    }

    int userRol = userService.GetUserRol(userId);

    if (userRol == 0)
    {
      Logger::Info("[LoginCGI::LoadHomePage]\n No se pudo validar el rol del usuario: "
          + to_string(userId));

      JsonBuilder response;
      response.addBool("success", false)
          .addString("message", string(" No se pudo validar su rol como usuario."));

      cout << "Content-Type: application/json" << "\r\n\r\n";
      return response.toString();
    }

    if (userRol == -1)
    {
      Logger::Error("[LoginCGI::LoadHomePage]\n Error al validar las el rol del usuario: "
          + to_string(userId));

      JsonBuilder response;
      response.addBool("success", false)
          .addString("message", string("Error: no se pudo validar su rol como usuario. "));

      cout << "Content-Type: application/json" << "\r\n\r\n";
      return response.toString();
    }

    SessionRepository sessionRepo(db);
    SessionService sessionService(sessionRepo);

    if (Authorization::isAdminRolId(userRol))
      return AdminLogin(sessionService, userId);

    return NormalLogin(sessionService, userId);
  }
  catch(const std::exception& e)
  {
    Logger::Error(string("[LoginCGI::LoadHomePage]\n") + e.what());

    JsonBuilder response;
    response.addBool("success", false)
        .addString("message", string("Hubo un error al iniciar sesion: ") + e.what());

    return response.toString();
  }
}

int main() {
  Request request;

  string responseBody;

  if (request.GetContentLength() == 0) {
    responseBody = LoadLoginPage();
  } else {
    responseBody = LoginAttempt(request);
  }

  cout << responseBody;

  return 0;
}
