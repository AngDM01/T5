#include <iostream>
#include <string>

#include "Authorization.hpp"
#include "DBConnection.hpp"
#include "DetailLetterView.hpp"
#include "EnvLoader.hpp"
#include "ImagesModel.hpp"
#include "ImagesRepository.hpp"
#include "ImagesService.hpp"
#include "JsonBuilder.hpp"
#include "LetterModel.hpp"
#include "LettersRepository.hpp"
#include "LettersService.hpp"
#include "Logger.hpp"
#include "Request.hpp"
#include "SessionLoader.hpp"
#include "TemplateEngine.hpp"
#include "UserModel.hpp"
#include "ViewUtils.hpp"

using namespace std;

string RenderViewLetterPage(LetterModel& letter)
{
	TemplateEngine templateEngine;
	DetailLetterView view(templateEngine, letter);

	string result = view.Render();

	return result;
}

string ViewLetter(Request& request, UserModel& userData)
{
	if (request.GetMethod() != "GET")
	{
		Logger::Warning("[ViewLetterCGI::ViewLetter]\n. Método HTTP no válido. "
				+ string(userData.GetIdUser() + ", " + userData.GetName()));

		return ViewUtils::LoadAdvicePage("Método HTTP no válido.");
	}

	if (!Authorization::CanViewLetters(userData))
  {
    Logger::Warning("[ViewLetterCGI::ViewLetter]\n No tiene permisos para acceder a este recurso: "
        + string(userData.GetIdUser() + ", " + userData.GetName()));

		return ViewUtils::LoadAdvicePage("No tiene permisos para acceder a este recurso.");
  }

	try
	{
		string letterId = request.GetQueryParam("letterId");

		auto config = EnvLoader::Load("/usr/local/apache2/app/db.env");
		DBConnection db;
		db.Connect(config["DB_HOST"], config["DB_USER"], config["DB_PASS"], config["DB_NAME"], stoi(config["DB_PORT"]));

		LettersRepository letterRepository(db);
		LettersService letterService(letterRepository);

		LetterModel letter = letterService.GetLetterDetails(userData.GetIdUser(), letterId);

		if (letter.GetIdLetter() == 0)
		{
			Logger::Warning("[ViewLetterCGI::ViewLetter]\n No se encontró información de la carta. "
        + string(userData.GetIdUser() + ", " + userData.GetName()));
			
			return ViewUtils::LoadAdvicePage("No se encontró información de la carta.");
		}

		if (letter.GetIdLetter() == -1)
		{
			Logger::Error("[ViewLetterCGI::ViewLetter]\n Ocurrió un error al obtener la información de la carta. "
        + string(userData.GetIdUser() + ", " + userData.GetName()));

			return ViewUtils::LoadAdvicePage("Ocurrió un error al obtener la información de la carta.");
		}

		ImagesModel imageData;

		if (letter.GetIdAssociateImage() != 0)
		{
			ImagesRepository imagesRepo(db);
			ImagesService imagesService(imagesRepo);
			
			Logger::Debug("asociateImgId: " + to_string(letter.GetIdAssociateImage()));

			imageData = imagesService.GetImageByImageId(letter.GetIdAssociateImage());

			if (imageData.GetIdImage() == -1)
			{
				Logger::Error("[ViewLetterCGI::ViewLetter]\n Ocurrió un error al obtener la imagen de la carta. "
        		+ to_string(userData.GetIdUser()) + ", " + userData.GetName());
				
				imageData.SetIdImage(0);
			}

		}
		
		Logger::Debug("imgid: " + to_string(imageData.GetIdImage()));
		letter.SetImage(imageData);

		if (!letterService.IsMarkedOpened(letterId))
		{
			bool openedLetter = letterService.MarkedLetterAsOpened(userData.GetIdUser(), letterId);
			
			if (!openedLetter)
			{
				Logger::Error("[ViewLetterCGI::ViewLetter]\n Ocurrió un error al actualizar el estado de la carta. "
						+ to_string(userData.GetIdUser()) + ", " + userData.GetName());
			}
		}

		return RenderViewLetterPage(letter);
	}
	catch(const std::exception& e)
	{
		Logger::Error("[ViewLetterCGI::ViewLetter]\n Ocurrió un error al cargar la pantalla detalle de la carta. "
        + string(userData.GetIdUser() + ", " + userData.GetName()) + string(e.what()));

		return ViewUtils::LoadAdvicePage("Ocurrió un error al cargar la pantalla detalle de la carta. " + string(e.what()));
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
			Logger::Error("[ViewLetterCGI::LoadSession]\n." + sessionLoader.GetError());

			return ViewUtils::LoadAdvicePage(sessionLoader.GetError());
		}

		return string();
	}
	catch(const std::exception& e)
	{
		Logger::Error("[ViewLetterCGI::LoadSession]\n. Hubo un error al verificar la sesión. " + string(e.what()));

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

	response = ViewLetter(request, userData);

	cout << response;

	return 0;
}
