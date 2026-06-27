#include <iostream>
#include <string>

#include "Authorization.hpp"
#include "DBConnection.hpp"
#include "EnvLoader.hpp"
#include "JsonBuilder.hpp"
#include "Logger.hpp"
#include "Request.hpp"
#include "SessionLoader.hpp"
#include "SessionRepository.hpp"
#include "SessionService.hpp"
#include "TemplateEngine.hpp"
#include "UserModel.hpp"

using namespace std;

string DeleteUserSession(Request& request, UserModel& userData)
{
	if (request.GetMethod() != "POST")
	{
		Logger::Error("[CloseSessionCGI::DeleteUserSession]\n. Método HTTP no válido. ");

		JsonBuilder response;
  
    cout << "Content-Type: application/json\r\n\r\n" << endl;

    response.addBool("success", false)
        .addString("type", string("err"))      
        .addString("message", string("Método HTTP no válido. "));

    return response.toString();
	}

	if (!Authorization::CanCloseSession(userData))
	{
		Logger::Error("[CloseSessionCGI::DeleteUserSession]\n. No tiene permisos para ejecutar esta acción. ");

		JsonBuilder response;
  
    cout << "Content-Type: application/json\r\n\r\n" << endl;

    response.addBool("success", false)
        .addString("type", string("info"))      
        .addString("message", string("No tiene permisos para ejecutar esta acción. "));

    return response.toString();
	}

	try
	{
		auto config = EnvLoader::Load("/usr/local/apache2/app/db.env");
		DBConnection db;
		db.Connect(config["DB_HOST"], config["DB_USER"], config["DB_PASS"], config["DB_NAME"], stoi(config["DB_PORT"]));

		SessionRepository sessionRepository(db);
		SessionService sessionService(sessionRepository);

		std::string sessionId = request.GetCookie("SESSION_ID");

		bool deletedSession = sessionService.DeleteUserSession(sessionId);

		if (!deletedSession)
		{
			Logger::Error("[CloseSessionCGI::DeleteUserSession]\n. Hubo un error al eliminar la sesión: "
					+ sessionId);

			JsonBuilder response;
		
			cout << "Content-Type: application/json\r\n\r\n" << endl;

			response.addBool("success", false)
					.addString("type", string("warn"))      
					.addString("message", string("Hubo un error al eliminar la sesión. Es probable que ya no exista. "));

			return response.toString();
		}

		JsonBuilder response;
		
		cout << "Set-Cookie: SESSION_ID=; Max-Age=0; Path=/; HttpOnly\r\n";
		
		cout << "Content-Type: application/json\r\n\r\n" << endl;

		response.addBool("success", true)  
				.addString("message", string("Sesión eliminada correctamente. "));

		return response.toString();
	}
	catch(const std::exception& e)
	{
		Logger::Error("[CloseSessionCGI::DeleteUserSession]\n. Hubo un error al cerrar la sesión. " + string(e.what()));

		JsonBuilder response;
  
    cout << "Content-Type: application/json\r\n\r\n" << endl;

    response.addBool("success", false)
        .addString("type", string("err"))      
        .addString("message", string("Hubo un error al cerrar la sesión. Es probable que ya no exista. "));

    return response.toString();
	}
	
}

string LoadSession(UserModel& userData)
{
	try
	{
		auto config = EnvLoader::Load("/usr/local/apache2/app/db.env");

		DBConnection db;

		db.Connect(config["DB_HOST"], config["DB_USER"], config["DB_PASS"], config["DB_NAME"], stoi(config["DB_PORT"]));

		SessionLoader sessionLoader(db);

		if (!sessionLoader.Load(userData))
		{
			Logger::Error("[CloseSessionCGI::LoadSession]\n." + sessionLoader.GetError());

			JsonBuilder response;
  
			cout << "Content-Type: application/json\r\n\r\n" << endl;

			response.addBool("success", false)
					.addString("type", string("err"))      
					.addString("message", string("Hubo un error al cargar la sesión. Es probable que ya no exista. "));

			return response.toString();
		}

		return string();
	}
	catch(const std::exception& e)
	{
		Logger::Error("[CloseSessionCGI::LoadSession]\n. Hubo un error al verificar la sesión. " + string(e.what()));

		JsonBuilder response;
  
    cout << "Content-Type: application/json\r\n\r\n" << endl;

    response.addBool("success", false)
        .addString("type", string("err"))      
        .addString("message", string("Hubo un error al verificar la sesión. Es probable que ya no exista. "));

    return response.toString();
	}
}

int main()
{	
	UserModel userData;
	
	string response = LoadSession(userData);
	
	if (!response.empty())
	{
		cout << response;
		return 0;
	}

	Request request;

	response = DeleteUserSession(request, userData);

	cout << response;

	return 0;
}
