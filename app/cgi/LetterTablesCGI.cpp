#include <iostream>
#include <list>
#include <string>

#include "Authorization.hpp"
#include "ComponentsBuilder.hpp"
#include "DBConnection.hpp"
#include "EnvLoader.hpp"
#include "JsonBuilder.hpp"
#include "LetterModel.hpp"
#include "LettersRepository.hpp"
#include "LettersService.hpp"
#include "Logger.hpp"
#include "Request.hpp"
#include "SessionLoader.hpp"
#include "TemplateEngine.hpp"
#include "UserModel.hpp"
#include "Validator.hpp"
#include "ViewUtils.hpp"

#define LIMIT 5

using namespace std;

string RenderReceivedLetterTable(list<LetterModel>& receivedLetters, int receivedLettersCount, int limit, int offset)
{
	ComponentsBuilder builder;

	string table = builder.BuildReceivedLetterTable(receivedLetters, receivedLettersCount, limit, offset);
	
	JsonBuilder response;
  
	cout << "Content-Type: application/json\r\n\r\n" << endl;

	response.addBool("success", true)
			.addString("content", table);

	return response.toString();
}

string RenderSendedLetterTable(list<LetterModel>& sendedLetters, int sendedLettersCount, int limit, int offset)
{
	ComponentsBuilder builder;

	string table = builder.BuildSendedLetterTable(sendedLetters, sendedLettersCount, limit, offset);
	
	JsonBuilder response;
  
	cout << "Content-Type: application/json\r\n\r\n" << endl;

	response.addBool("success", true)
			.addString("content", table);

	return response.toString();
}

string LoadReceivedLetters(LettersService& service, UserModel& userData, int offsetInt)
{
  int receivedLettersCount = service.GetUserReceivedLetterCount(userData.GetIdUser());

	if (receivedLettersCount == -1)
	{
		Logger::Error("[LetterTablesCGI::LoadReceivedLetters]\n."
				+ string("Hubo un error al obtener el total de cartas recibidas por el usuario. ")
				+ string(userData.GetIdUser() + ", " + userData.GetName()));

		JsonBuilder response;

		cout << "Content-Type: application/json\r\n\r\n" << endl;

		response.addBool("success", false)
				.addString("type", string("err"))
				.addString("message", string("Hubo un error al obtener el total de cartas recibidas por el usuario. "));

		return response.toString();
	}

	list<LetterModel> receivedLetters = service.GetUserReceivedLettersInRange(userData.GetIdUser(), LIMIT, offsetInt);

	if (!receivedLetters.empty() && receivedLetters.front().GetIdLetter() == -1)
	{
		Logger::Error("[LetterTablesCGI::LoadReceivedLetters]\n."
				+ string("Hubo un error al obtener las cartas recibidas por el usuario. ")
				+ string(userData.GetIdUser() + ", " + userData.GetName()));

		JsonBuilder response;

		cout << "Content-Type: application/json\r\n\r\n" << endl;

		response.addBool("success", false)
				.addString("type", string("err"))
				.addString("message", string("Hubo un error al obtener las cartas recibidas por el usuario. "));

		return response.toString();
	}

	return RenderReceivedLetterTable(receivedLetters, receivedLettersCount, LIMIT, offsetInt);
}

string LoadSendedLetters(LettersService& service, UserModel& userData, int offsetInt)
{
  int sendedLettersCount = service.GetUserSendedLetterCount(userData.GetIdUser());

	if (sendedLettersCount == -1)
	{
		Logger::Error("[LetterTablesCGI::LoadSendedLetters]\n."
				+ string("Hubo un error al obtener el total de cartas enviadas por el usuario. ")
				+ string(userData.GetIdUser() + ", " + userData.GetName()));

		JsonBuilder response;

		cout << "Content-Type: application/json\r\n\r\n" << endl;

		response.addBool("success", false)
				.addString("type", string("err"))
				.addString("message", string("Hubo un error al obtener el total de cartas enviadas por el usuario. "));

		return response.toString();
	}

	list<LetterModel> sendedLetters = service.GetUserSendedLettersInRange(userData.GetIdUser(), LIMIT, offsetInt);

	if (!sendedLetters.empty() && sendedLetters.front().GetIdLetter() == -1)
	{
		Logger::Error("[LetterTablesCGI::LoadSendedLetters]\n."
				+ string("Hubo un error al obtener las cartas enviadas por el usuario. ")
				+ string(userData.GetIdUser() + ", " + userData.GetName()));

		JsonBuilder response;

		cout << "Content-Type: application/json\r\n\r\n" << endl;

		response.addBool("success", false)
				.addString("type", string("err"))
				.addString("message", string("Hubo un error al obtener las cartas enviadas por el usuario. "));

		return response.toString();
	}

	return RenderSendedLetterTable(sendedLetters, sendedLettersCount, LIMIT, offsetInt);
}

string CreateViewTable(Request& request, UserModel& userData)
{
	if (request.GetMethod() != "GET")
	{
		Logger::Warning("[LetterTablesCGI::CreateViewTable]\n. Método HTTP no válido. "
				+ string(userData.GetIdUser() + ", " + userData.GetName()));

		JsonBuilder response;
    
		cout << "Content-Type: application/json\r\n\r\n" << endl;

		response.addBool("success", false)
				.addString("type", string("warn"))
				.addString("message", string("Método HTTP no válido."));

		return response.toString();
	}

	if (!Authorization::CanViewLettersTables(userData))
  {
    Logger::Warning("[LetterTablesCGI::CreateViewTable]\n No tiene permisos para ejecutar esta acción: "
        + string(userData.GetIdUser() + ", " + userData.GetName()));

    JsonBuilder response;
  
    cout << "Content-Type: application/json\r\n\r\n" << endl;

    response.addBool("success", false)
        .addString("type", string("info"))
        .addString("message", string("No tiene permisos para ejecutar esta acción."));

    return response.toString();
  }

	try
	{
		bool isSendedLetters = request.GetQueryParam("isSendedLetters") == "true" ? true : false;
		string offsetStr = request.GetQueryParam("offset");

		if (!Validator::IsValidOffset(offsetStr))
		{
			Logger::Warning("[LetterTablesCGI::CreateViewTable]\n El valor del offset no es válido: " + offsetStr
					+ ". [Usuario]: " + string(userData.GetIdUser() + ", " + userData.GetName()));

      JsonBuilder response;
    
      cout << "Content-Type: application/json\r\n\r\n" << endl;

      response.addBool("success", false)
          .addString("type", string("warn"))
          .addString("message", string("El valor del offset no es válido."));

      return response.toString();
		}

		int offsetInt = std::stoi(offsetStr);

		auto config = EnvLoader::Load("/usr/local/apache2/app/db.env");
		DBConnection db;
		db.Connect(config["DB_HOST"], config["DB_USER"], config["DB_PASS"], config["DB_NAME"], stoi(config["DB_PORT"]));

		LettersRepository letterRepository(db);
		LettersService letterService(letterRepository);

		if (isSendedLetters)
		{
			return LoadSendedLetters(letterService, userData, offsetInt);
		}

		return LoadReceivedLetters(letterService, userData, offsetInt);
	}
	catch(const std::exception& e)
	{
		Logger::Error("[LetterTablesCGI::CreateViewTable]\n Hubo un error al cargar la tabla: "
        + string(userData.GetIdUser() + ", " + userData.GetName()));

    JsonBuilder response;
  
    cout << "Content-Type: application/json\r\n\r\n" << endl;

    response.addBool("success", false)
        .addString("type", string("err"))
        .addString("message", string("Hubo un error al cargar la tabla."));

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
			Logger::Error("[LetterTablesCGI::LoadSession]\n." + sessionLoader.GetError());

			return ViewUtils::LoadAdvicePage(sessionLoader.GetError());
		}

		return string();
	}
	catch(const std::exception& e)
	{
		Logger::Error("[LetterTablesCGI::LoadSession]\n. Hubo un error al verificar la sesión. " + string(e.what()));

		return ViewUtils::LoadAdvicePage("Hubo un error al verificar la sesión.");
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

	response = CreateViewTable(request, userData);

	cout << response;

	return 0;
}
