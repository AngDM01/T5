#include <iostream>
#include <cstdlib>
#include <string>

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

class UserRepository;
class UserService;

using namespace std;

void LoadLoginPage()
{
  string loginRoute = "/usr/local/apache2/app/templates/Static/login.html";

  TemplateEngine templateEngine;
	StaticView view(templateEngine, loginRoute);

	string renderedPage = view.Render();
  
	cout << renderedPage;
}

void LoginAttempt(Request& request)
{
  if (request.GetMethod() != "POST")
  {
    Logger::Info("[loadLoginPage]\n Método http no válido: " + request.GetMethod());

    JsonBuilder response;
    response.addBool("success", false)
        .addString("message", string("Metodo http no valido."));

    cout << "Content-Type: application/json\r\n\r\n";
    cout << response.toString();
    return;
  }

  string email = request.GetBodyParam("email");
  string pwd = request.GetBodyParam("password");

  LoginDTO loginData(email, pwd);

  try
  {
    auto config = EnvLoader::Load("/usr/local/apache2/app/db.env");

    DBConnection db;

    db.Connect(config["DB_HOST"], config["DB_USER"], config["DB_PASS"],
        config["DB_NAME"], std::stoi(config["DB_PORT"]));

    UserRepository userRepo(db);
    UserService userService(userRepo);

    int userId = userService.GetUserIdByCredentials(loginData);

    if (userId == 0)
    {
      Logger::Info("[LoadHomePage]\n Credenciales proporcionadas inválidas.");

      JsonBuilder response;
      response.addBool("success", false)
          .addString("message", string("Las credenciales son incorrectas."));

      cout << "Content-Type: application/json\r\n\r\n";
      cout << response.toString();
      return;
    }

    if (userId == -1)
    {
      Logger::Info("[LoadHomePage]\n Error al validar las credenciales.");

      JsonBuilder response;
      response.addBool("success", false)
          .addString("message", string("Error: no se pudo validar las credenciales."));

      cout << "Content-Type: application/json\r\n\r\n";
      cout << response.toString();
      return;
    }

    SessionRepository sessionRepo(db);
    SessionService sessionService(sessionRepo);

    string sessionId = sessionService.CreateNewUserSession(userId, 6);

    if (sessionId.empty() || sessionId == "0")
    {
      Logger::Info("[LoadHomePage]\n Error al obtener la sesión.");

      JsonBuilder response;
      response.addBool("success", false)
          .addString("message", string("Error: no se pudo obtener la sesión."));

      cout << "Content-Type: application/json\r\n\r\n";
      cout << response.toString();
      return;
    }

    int maxAge = 25 * 60;

    cout << "Set-Cookie: SESSION_ID=" << sessionId
        << "; Max-Age=" << maxAge
        << "; Path=/"
        << "; HttpOnly"
        // << "; Secure"
        << "; SameSite=Lax"
        << "\r\n";

    JsonBuilder response;
    response.addBool("success", true)
        .addString("message", string("Inicio de sesión exitoso."));

    cout << "Content-Type: application/json\r\n\r\n";
    cout << response.toString();
  }
  catch(const std::exception& e)
  {
    Logger::Error(string("[LoginDTO::LoadHomePage]\n") + e.what());

    JsonBuilder response;
    response.addBool("success", false)
        .addString("message", string("Hubo un error al iniciar sesion: ") + e.what());

    cout << "Content-Type: application/json\r\n\r\n";
    cout << response.toString();
    return;
  }
  
}

int main() {
  Request request;
  
  if (request.GetContentLength() == 0) {
    LoadLoginPage();
  } else {
    LoginAttempt(request);
  }

  return 0;
}
