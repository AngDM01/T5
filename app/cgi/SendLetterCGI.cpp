#include <iostream>
#include <string>

#include "Authorization.hpp"
#include "DBConnection.hpp"
#include "EnvLoader.hpp"
#include "JsonBuilder.hpp"
#include "LetterModel.hpp"
#include "LettersRepository.hpp"
#include "LettersService.hpp"
#include "Logger.hpp"
#include "Request.hpp"
#include "SendLetterDTO.hpp"
#include "SessionLoader.hpp"
#include "UserModel.hpp"
#include "UserRepository.hpp"
#include "UserService.hpp"
#include "ViewUtils.hpp"

using namespace std;

string SendLetter(Request& request, UserModel& userData)
{
  if (request.GetMethod() != "POST")
  {
    Logger::Warning("[SendLetterCGI::SendLetter]\n. Metodo HTTP no valido: " + request.GetMethod());

    return ViewUtils::LoadAdvicePage("Método HTTP no válido");
  }

  if (!Authorization::CanSendLetters(userData))
  {
    Logger::Info("[SendLetterCGI::SendLetter]\n. No tiene permiso para ejecutar esta accion: "
        + to_string(userData.GetIdUser()) + ", " + userData.GetName());

    JsonBuilder response;
  
    cout << "Content-Type: application/json\r\n\r\n" << endl;

    response.addBool("success", false)
        .addString("type", string("info"))
        .addString("message", string("No tiene permisos para ejecutar esta acción."));

    return response.toString();
  }
 
  try
  {
    auto config = EnvLoader::Load("/usr/local/apache2/app/db.env");
		DBConnection db;
		db.Connect(config["DB_HOST"], config["DB_USER"], config["DB_PASS"], config["DB_NAME"], stoi(config["DB_PORT"]));

    SendLetterDTO letterDTO(request.GetBodyParam("from"), request.GetBodyParam("to"), request.GetBodyParam("destEmail"),
        request.GetBodyParam("letterTitle"), request.GetBodyParam("letterText"), request.GetBodyParam("imageId"));

    UserRepository userRepository(db);
    UserService userService(userRepository);

    int receivedUser = userService.GetUserIdByEmail(letterDTO.GetToEmail());

    if (receivedUser == -1)
    {
      Logger::Error("[SendLetterCGI::SendLetter]\n. Hubo un error al obtener el usuario destinatario: "
          + to_string(userData.GetIdUser()) + ", " + userData.GetName());
      
      JsonBuilder response;
  
      cout << "Content-Type: application/json\r\n\r\n" << endl;

      response.addBool("success", false)
          .addString("type", string("err"))
          .addString("message", string("Hubo un error al obtener el usuario destinatario."));

      return response.toString();
    }

    if (receivedUser == 0)
    {
      Logger::Info("[SendLetterCGI::SendLetter]\n. No se encontró al usuario destinatario con correo: " + letterDTO.GetToEmail()
          + to_string(userData.GetIdUser()) + ", " + userData.GetName());

      JsonBuilder response;
  
      cout << "Content-Type: application/json\r\n\r\n" << endl;

      response.addBool("success", true)
          .addString("message", string("Correo enviado. Si el usuario está registrado recibirá la carta."));

      return response.toString();
    }

    LettersRepository lettersRepository(db);
    LettersService letterService(lettersRepository);

    bool insertedLetter = letterService.SaveSendedLetter(letterDTO, userData, receivedUser);

    if (!insertedLetter)
    {
      Logger::Info("[SendLetterCGI::SendLetter]\n. Hubo un error al guardar la carta. O el usuario con correo: "
          + request.GetBodyParam("destEmail") + " no existe. " + to_string(userData.GetIdUser()) + ", " + userData.GetName());

      JsonBuilder response;
  
      cout << "Content-Type: application/json\r\n\r\n" << endl;

      response.addBool("success", false)
          .addString("type", "err")
          .addString("message", string("Correo enviado. Si el usuario está registrado recibirá la carta."));

      return response.toString();
    }

    JsonBuilder response;
  
    cout << "Content-Type: application/json\r\n\r\n" << endl;

    response.addBool("success", true)
        .addString("message", string("Correo enviado. Si el usuario está registrado recibirá la carta."));

    return response.toString();
  }
  catch(const std::exception& e)
  {
    Logger::Error("[SendLetterCGI::SendLetter]\n. Hubo un error al enviar la carta: "
        + to_string(userData.GetIdUser()) + ", " + userData.GetName() + ". Problema: " + string(e.what()));

    JsonBuilder response;
  
    cout << "Content-Type: application/json\r\n\r\n" << endl;

    response.addBool("success", false)
        .addString("type", string("err"))
        .addString("message", string("Hubo un error al enviar la carta. ") + e.what());

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
			Logger::Error("[SendLetterCGI::LoadSession]\n." + sessionLoader.GetError());

			return ViewUtils::LoadAdvicePage(sessionLoader.GetError());
		}

		return string();
	}
	catch(const std::exception& e)
	{
		Logger::Error("[SendLetterCGI::LoadSession]\n. Hubo un error al verificar la sesión. " + string(e.what()));

		return ViewUtils::LoadAdvicePage("Hubo un error al verificar la sesión.");
	}
	
}

int main() {
  Request request;
  
  UserModel userData;
	
	string response = LoadSession(userData);
	
	if (!response.empty())
	{
		cout << response;
		return 0;
	}


  response = SendLetter(request, userData);

  cout << response;

  return 0;
}
