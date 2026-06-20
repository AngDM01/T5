#include <iostream>
#include <cstdlib>
#include <string>

#include "DBConnection.hpp"
#include "EnvLoader.hpp"
#include "JsonBuilder.hpp"
#include "Logger.hpp"
#include "RegisterDTO.hpp"
#include "Request.hpp"
#include "StaticView.hpp"
#include "TemplateEngine.hpp"
#include "UserModel.hpp"
#include "UserRepository.hpp"
#include "UserService.hpp"
#include "View.hpp"

using namespace std;

void LoadRegisterPage() {
  string registerRoute = "/usr/local/apache2/app/templates/Static/register.html";

  TemplateEngine templateEngine = TemplateEngine();
	StaticView view(templateEngine, registerRoute);

	string renderedPage = view.Render();
  
	cout << renderedPage;
}

void LoadLoginPage(Request& request) {
  if (request.GetMethod() != "POST")
  {
    Logger::Info("[loadLoginPage]\n Método http no válido: " + request.GetMethod());

    cout << "Content-Type: application/json\r\n\r\n";
    cout << "{\"success\": false, \"message\": \"Metodo http no valido\"}";
    return;
  }

  string name = request.GetBodyParam("name");
  string age = request.GetBodyParam("age");
  string email = request.GetBodyParam("email");
  string pwd = request.GetBodyParam("password");
  string pwdConf = request.GetBodyParam("passwordConf");

  RegisterDTO registerData(name, age, email, pwd, pwdConf);

  try {
    auto config = EnvLoader::Load("/usr/local/apache2/app/db.env");

    DBConnection db;

    db.Connect(config["DB_HOST"], config["DB_USER"], config["DB_PASS"],
        config["DB_NAME"], std::stoi(config["DB_PORT"]));

    UserRepository repo(db);
    UserService service(repo);

    int userId = service.UserAlreadyExistByCheckEmail(registerData.GetEmail());

    if (userId != 0)
    {
      Logger::Info("[loadLoginPage]\n El correo proporcionado ya está en uso.");

      cout << "Content-Type: application/json\r\n\r\n";
      cout << "{\"success\": false, \"message\": \"El correo proporcionado ya esta en uso.\"}";
      return;
    }

    if (userId == -1)
    {
      Logger::Warning("[loadLoginPage]\n No se pudo comprobar el correo.");

      cout << "Content-Type: application/json\r\n\r\n";
      cout << "{\"success\": false, \"message\": \"No se pudo comprobar si la cuenta esta registrada.\"}";
      return;
    }

    bool userRegistered = service.RegisterNewUser(registerData);

    if (!userRegistered)
    {
      Logger::Warning("[loadLoginPage]\n No se pudo registrar al usuario");

      cout << "Content-Type: application/json\r\n\r\n";
      cout << "{\"success\": false, \"message\": \"No se pudo registrar la cuenta.\"}";
      return;
    }

    cout << "Content-Type: application/json\r\n\r\n";
    cout << "{\"success\": true, \"message\": \"Registro correcto.\"}";
    return;
  }
  catch(const exception& e)
  {
    Logger::Error(string("[UserService::userAlreadyExistByCheckEmail]\n") + e.what());

    JsonBuilder response;
    response.addBool("success", false)
        .addString("message", string("Hubo un error al registrar la cuenta: ") + e.what());

    cout << "Content-Type: application/json\r\n\r\n";
    cout << response.toString();
    return;
  }
}

int main() {
  Request request;

  if (request.GetContentLength() == 0) {
    LoadRegisterPage();
  } else {
    LoadLoginPage(request);
  }

  return 0;
}
