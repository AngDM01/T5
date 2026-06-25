#include <iostream>
#include <list>
#include <string>

#include "Authorization.hpp"
#include "ComponentsBuilder.hpp"
#include "DBConnection.hpp"
#include "EnvLoader.hpp"
#include "ImageDTO.hpp"
#include "Imagehelper.hpp"
#include "ImagesModel.hpp"
#include "ImagesRepository.hpp"
#include "ImagesService.hpp"
#include "JsonBuilder.hpp"
#include "Logger.hpp"
#include "Request.hpp"
#include "SessionLoader.hpp"
#include "UserModel.hpp"
#include "Validator.hpp"
#include "ViewUtils.hpp"

#define LIMIT 3

using namespace std;

string buildGallery2(list<ImagesModel>& images, string idContainer, int imagesCount, int offsetInt, bool isCatalog)
{
  ComponentsBuilder builder;

  string carrusel = builder.BuildImageCarrouselType1(images, idContainer, imagesCount, LIMIT, offsetInt, isCatalog);

  JsonBuilder response;
    
  cout << "Content-Type: application/json\r\n\r\n" << endl;

  response.addBool("success", true)
      .addString("message", carrusel);

  return response.toString();
}

string buildGalley1(list<ImagesModel>& images, int imagesCount, int offset)
{
  ComponentsBuilder builder;

  string carrusel = builder.BuildImageCarrouselType2(images, "carrImgId", imagesCount, LIMIT, offset);

  JsonBuilder response;
    
  cout << "Content-Type: application/json\r\n\r\n" << endl;

  response.addBool("success", true)
      .addString("message", carrusel);

  return response.toString();
}

string moveGallery(Request& request, UserModel& userData)
{
  if (request.GetMethod() != "GET")
  {
    Logger::Error("[ImagesGalleryCIG::moveGallery]\n. Método HTTP no válido");

		return ViewUtils::LoadAdvicePage("Método HTTP no válido");
  }

  if (!Authorization::CanMoveGallery(userData))
  {
    Logger::Warning("[ImagesGalleryCIG::moveGallery]\n No tiene permisos para ejecutar esta acción: "
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
    string idContainer = request.GetQueryParam("idContainer");
    string offset = request.GetQueryParam("offset");
    bool isCatalog = request.GetQueryParam("isCatalog") == "true" ? true : false;

    if (!Validator::IsValidOffset(offset))
    {
      Logger::Warning("[ImagesGalleryCIG::moveGallery]\n El valor del offset no es válido: " + offset);

      JsonBuilder response;
    
      cout << "Content-Type: application/json\r\n\r\n" << endl;

      response.addBool("success", false)
          .addString("type", string("warn"))
          .addString("message", string("El valor del offset no es válido."));

      return response.toString();
    }

    int offsetInt = std::stoi(offset);

    auto config = EnvLoader::Load("/usr/local/apache2/app/db.env");

		DBConnection db;

		db.Connect(config["DB_HOST"], config["DB_USER"], config["DB_PASS"], config["DB_NAME"], stoi(config["DB_PORT"]));

    ImagesRepository imagesRepo(db);
		ImagesService imagesService(imagesRepo);

    if (!isCatalog)
    {
      int totalImages = imagesService.GetTotalImagesCountFromUser(userData.GetIdUser());

      if (totalImages == -1)
      {
        Logger::Error("[ImagesGalleryCIG::moveGallery]\n " + string("Hubo un error al obtener la cantidad de imágenes asociadas al usuario."));

        JsonBuilder response;
      
        cout << "Content-Type: application/json\r\n\r\n" << endl;

        response.addBool("success", false)
        .addString("type", string("err"))      
        .addString("message", string("No se pudo obtener la cantidad de imagenes asociadas."));
        
        return response.toString();
        
        totalImages = 0;
      }
            
      list<ImagesModel> images = imagesService.GetImagesFromUserInRange(userData.GetIdUser(), LIMIT, offsetInt);

      if (!images.empty() && images.front().GetIdImage() == -1)
      {
        Logger::Error("[CreateLetterCGI::LoadCreateLetterPage]\n."
            + string("Hubo un error al obtener las imagenes asociadas al usuario. ")
            + string(userData.GetIdUser() + ", " + userData.GetName()));

        images.clear();
      }

      if (idContainer == "carrImgId")
      {
        return buildGalley1(images, totalImages, offsetInt);
      }

      return buildGallery2(images, idContainer, totalImages, offsetInt, isCatalog);
    }

    int isCatalogTotalImages = imagesService.GetIsCatalogImagesCount();

    if (isCatalogTotalImages == -1)
    {
      Logger::Error("[CreateLetterCGI::LoadCreateLetterPage]\n "
          + string("Hubo un error al obtener la cantidad de imágenes del catálogo.")
          + string(userData.GetIdUser() + ", " + userData.GetName()));

      isCatalogTotalImages = 0;
    }

    list<ImagesModel> catalogImages = imagesService.GetCatalogImagesInRange(LIMIT, offsetInt);

    if (!catalogImages.empty() && catalogImages.front().GetIdImage() == -1)
    {
      Logger::Error("[CreateLetterCGI::LoadCreateLetterPage]\n."
          + string("Hubo un error al obtener las imagenes del catálogo. ")
          + string(userData.GetIdUser() + ", " + userData.GetName()));

      catalogImages.clear();
    }

    return buildGallery2(catalogImages, idContainer, isCatalogTotalImages, offsetInt, isCatalog);
  }
  catch(const std::exception& e)
  {
    Logger::Error("[ImagesGalleryCIG::moveGallery]\n " + string("Hubo un error al mover el carrusel de imagenes."));

    JsonBuilder response;
  
    cout << "Content-Type: application/json\r\n\r\n" << endl;

    response.addBool("success", false)
        .addString("type", string("err"))      
        .addString("message", string("Hubo un error al mover el carrusel de imagenes."));

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
			Logger::Error("[ImagesMaintenance::LoadImageMaintenancePage]\n." + sessionLoader.GetError());

			return ViewUtils::LoadAdvicePage(sessionLoader.GetError());
		}

		return string();
	}
	catch(const std::exception& e)
	{
		Logger::Error("[ImagesMaintenance::LoadImageMaintenancePage]\n. Hubo un error al cargar la verificar la sesión. " + string(e.what()));

		return ViewUtils::LoadAdvicePage("Hubo un error al cargar la verificar la sesión.");
	}
	
}

int main()
{	
	Request request;

	UserModel user;

	string response = LoadSession(user);

	if (!response.empty())
	{
		cout << response;
		return 0;
	}

  response = moveGallery(request, user);

	cout << response;

	return 0;
}
