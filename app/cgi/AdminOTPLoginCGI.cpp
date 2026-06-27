#include <iostream>
#include <string>

#include "Authorization.hpp"
#include "DBConnection.hpp"
#include "EnvLoader.hpp"
#include "JsonBuilder.hpp"
#include "Logger.hpp"
#include "OTPRepository.hpp"
#include "OTPService.hpp"
#include "Request.hpp"
#include "SessionRepository.hpp"
#include "SessionService.hpp"
#include "StaticView.hpp"
#include "TemplateEngine.hpp"

#define SESSIONTIME 30

using namespace std;

string LoadOTPPage()
{
  TemplateEngine engine;
  StaticView view(engine, "/usr/local/apache2/app/templates/Static/adminLoginOTP.html");

  return view.Render();
}

string VerifyOTP(Request &request)
{
  if (request.GetMethod() != "POST")
  {
    Logger::Info("[AdminOTPLoginCGI::VerifyOTP]\n Método http no válido: " + request.GetMethod());

    JsonBuilder response;
    response.addBool("success", false)
        .addString("message", "Método HTTP inválido.");

    cout << "Content-Type: application/json\r\n\r\n";
    return response.toString();
  }

  string otp = request.GetBodyParam("otp");

  try
  {
    auto config = EnvLoader::Load("/usr/local/apache2/app/db.env");
    DBConnection db;
    db.Connect(config["DB_HOST"], config["DB_USER"], config["DB_PASS"], config["DB_NAME"], stoi(config["DB_PORT"]));

    SessionRepository sessionRepo(db);
    SessionService sessionService(sessionRepo);

    string sessionId = request.GetCookie("PENDING_ADMIN_SESSION");

    int userId = sessionService.GetPendingAdminUser(sessionId);

    if (userId <= 0)
    {
      Logger::Warning("[AdminOTPLoginCGI::VerifyOTP]\n La sesión de autenticación expiró. " + request.GetMethod());

      JsonBuilder response;
      response.addBool("success", false)
          .addString("message", "La sesión de autenticación expiró.");

      cout << "Content-Type: application/json\r\n\r\n";
      return response.toString();
    }

    OTPRepository otpRepository(db);
    OTPService otpService(otpRepository);

    if (!otpService.VerifyOTP(userId, otp))
    {
      Logger::Warning("[AdminOTPLoginCGI::VerifyOTP]\n OTP incorrecto. "
          + to_string(userId));

      JsonBuilder response;
      response.addBool("success", false)
          .addString("message", "OTP incorrecto.");

      cout << "Content-Type: application/json\r\n\r\n";
      return response.toString();
    }

    string newSessionId = sessionService.CreateNewUserSession(userId, SESSIONTIME);

    if (newSessionId.empty() || newSessionId == "0")
    {
      Logger::Warning("[AdminOTPLoginCGI::VerifyOTP]\n Error al obtener la sesión.");

      JsonBuilder response;
      response.addBool("success", false)
          .addString("message", string("Error: no se pudo obtener la sesión."));

      return response.toString();
    }

    bool pendingSessionDeleted = sessionService.DeletePendingAdminSession(userId);

    if (!pendingSessionDeleted)
    {
      Logger::Warning("[AdminOTPLoginCGI::VerifyOTP]\n Error al eliminar la sesión temporal.");

      JsonBuilder response;
      response.addBool("success", false)
          .addString("message", "Error al eliminar la sesión temporal.");

      cout << "Content-Type: application/json\r\n\r\n";
      return response.toString();
    }

    int maxAge = SESSIONTIME * 60;

    cout << "Set-Cookie: SESSION_ID=" << newSessionId
         << "; Max-Age=" << maxAge
         << "; Path=/"
         << "; HttpOnly"
         << "; SameSite=Lax\r\n";

    JsonBuilder response;
    response.addBool("success", true)
        .addString("message", "Inicio de sesión exitoso.");

    cout << "Content-Type: application/json\r\n\r\n";
    return response.toString();
  }
  catch (const exception &e)
  {
    Logger::Error(e.what());

    JsonBuilder response;
    response.addBool("success", false)
        .addString("message", e.what());

    cout << "Content-Type: application/json\r\n\r\n";
    return response.toString();
  }
}

int main()
{
  Request request;

  string response;

  if (request.GetContentLength() == 0)
    response = LoadOTPPage();
  else
    response = VerifyOTP(request);

  cout << response;
  return 0;
}