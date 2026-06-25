#include <iostream>
#include <string>

#include "Authorization.hpp"
#include "ComponentsBuilder.hpp"
#include "CreateLetterView.hpp"
#include "DBConnection.hpp"
#include "EnvLoader.hpp"
#include "ImagesModel.hpp"
#include "ImagesRepository.hpp"
#include "ImagesService.hpp"
#include "Logger.hpp"
#include "Request.hpp"
#include "SessionLoader.hpp"
#include "TemplateEngine.hpp"
#include "UserModel.hpp"
#include "UserRepository.hpp"
#include "UserService.hpp"
#include "ViewUtils.hpp"

#define LIMIT 3
#define OFFSET 0

using namespace std;

string RenderCreateLetterPage(string catalogImages, string userImages)
{
	TemplateEngine templateEngine = TemplateEngine();
	CreateLetterView view(templateEngine, catalogImages, userImages);

	string renderedPage = view.Render();

	return renderedPage;
}

string RenderImageCarrousel(list<ImagesModel>& images, string idContainer, int imagesCount, int offset, bool isCatalog)
{
  ComponentsBuilder builder;

  string carrusel = builder.BuildImageCarrouselType1(images, idContainer, imagesCount, LIMIT, offset, isCatalog);

  return carrusel;
}

string LoadCreateLetterPage(UserModel& userData)
{
	if (!Authorization::CanCreateLetter(userData))
	{
		Logger::Warning("[CreateLetterCGI::LoadCreateLetterPage]\n No tiene permisos para acceder a este recurso: "
				+ string(userData.GetIdUser() + ", " + userData.GetName()));

		return ViewUtils::LoadAdvicePage("No tiene permisos para acceder a este recurso.");
	}

	try
	{

		auto config = EnvLoader::Load("/usr/local/apache2/app/db.env");

		DBConnection db;

		db.Connect(config["DB_HOST"], config["DB_USER"], config["DB_PASS"], config["DB_NAME"], stoi(config["DB_PORT"]));

		ImagesRepository imagesRepo(db);
		ImagesService imagesService(imagesRepo);

		int totalImages = imagesService.GetTotalImagesCountFromUser(userData.GetIdUser());

		if (totalImages == -1)
		{
			Logger::Error("[CreateLetterCGI::LoadCreateLetterPage]\n "
					+ string("Hubo un error al obtener la cantidad de imágenes asociadas al usuario. ")
					+ string(userData.GetIdUser() + ", " + userData.GetName()));

			totalImages = 0;
		}

		int isCatalogTotalImages = imagesService.GetIsCatalogImagesCount();

		if (isCatalogTotalImages == -1)
		{
			Logger::Error("[CreateLetterCGI::LoadCreateLetterPage]\n "
					+ string("Hubo un error al obtener la cantidad de imágenes del catálogo.")
					+ string(userData.GetIdUser() + ", " + userData.GetName()));

			isCatalogTotalImages = 0;
		}

		list<ImagesModel> userImages = imagesService.GetImagesFromUserInRange(userData.GetIdUser(), LIMIT, OFFSET);

		if (!userImages.empty() && userImages.front().GetIdImage() == -1)
		{
			Logger::Error("[CreateLetterCGI::LoadCreateLetterPage]\n."
					+ string("Hubo un error al obtener las imagenes asociadas al usuario. ")
					+ string(userData.GetIdUser() + ", " + userData.GetName()));

			userImages.clear();
		}

		list<ImagesModel> catalogImages = imagesService.GetCatalogImagesInRange(LIMIT, OFFSET);

		if (!catalogImages.empty() && catalogImages.front().GetIdImage() == -1)
		{
			Logger::Error("[CreateLetterCGI::LoadCreateLetterPage]\n."
					+ string("Hubo un error al obtener las imagenes del catálogo. ")
					+ string(userData.GetIdUser() + ", " + userData.GetName()));

			catalogImages.clear();
		}
		
		string catalogCarrousel = RenderImageCarrousel(catalogImages, "catalogCarr", isCatalogTotalImages, OFFSET, true);

		string userImagesCarrousel = RenderImageCarrousel(userImages, "userCarr", totalImages, OFFSET, false);

		return RenderCreateLetterPage(catalogCarrousel, userImagesCarrousel);
	}
	catch(const std::exception& e)
	{
		Logger::Error("[CreateLetterCGI::LoadCreateLetterPage]\n "
					+ string("Hubo un error al cargar la pantalla de crear carta. ")
					+ string(userData.GetIdUser() + ", " + userData.GetName()));
		
		return ViewUtils::LoadAdvicePage("Hubo un error al cargar la pantalla de crear carta. " + string(e.what()));
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
			Logger::Error("[CreateLetterCGI::LoadSession]\n." + sessionLoader.GetError());

			return ViewUtils::LoadAdvicePage(sessionLoader.GetError());
		}

		return string();
	}
	catch(const std::exception& e)
	{
		Logger::Error("[CreateLetterCGI::LoadSession]\n. Hubo un error al verificar la sesión. " + string(e.what()));

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

	if (request.GetContentLength() == 0)
		response = LoadCreateLetterPage(userData);
	else
	{
		response = LoadCreateLetterPage(userData);
	}

	cout << response;

	return 0;
}
