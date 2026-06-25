#include <iostream>
#include <list>
#include <string>

#include "Authorization.hpp"
#include "DBConnection.hpp"
#include "EnvLoader.hpp"
#include "ImageDTO.hpp"
#include "Imagehelper.hpp"
#include "ImagesMaintView.hpp"
#include "ImagesModel.hpp"
#include "ImagesRepository.hpp"
#include "ImagesService.hpp"
#include "JsonBuilder.hpp"
#include "Logger.hpp"
#include "Request.hpp"
#include "SessionLoader.hpp"
#include "TemplateEngine.hpp"
#include "UserModel.hpp"
#include "ViewUtils.hpp"

#define MAXIMAGESADMIN 100
#define MAXIMAGES 12
#define LIMIT 3
#define OFFSET 0

using namespace std;

string DeleteImage(Request& request, UserModel& user)
{
	if (request.GetMethod() != "POST")
	{
		Logger::Error("[ImagesMaintenance::UploadImage]\n. Método HTTP no válido");

		return ViewUtils::LoadAdvicePage("Método HTTP no válido");
	}

	if (!Authorization::CanDeleteImages(user))
	{
		Logger::Warning("[ImagesMaintenance::DeleteImage]\n No tiene permisos para ejecutar esta acción: " + string(user.GetIdUser() + ", " + user.GetName()));

		JsonBuilder response;
	
		cout << "Content-Type: application/json\r\n\r\n" << endl;

		response.addBool("success", false)
				.addString("message", string("No tiene permisos para ejecutar esta acción."));

		return response.toString();
	}
	
	try
	{
		string imageId = request.GetBodyParam("imageId");

		auto config = EnvLoader::Load("/usr/local/apache2/app/db.env");
		DBConnection db;
		db.Connect(config["DB_HOST"], config["DB_USER"], config["DB_PASS"], config["DB_NAME"], stoi(config["DB_PORT"]));

		ImagesRepository imagesRepository(db);
		ImagesService imagesService(imagesRepository);

		bool deleteResult = imagesService.DeleteImageById(imageId);

		if (!deleteResult)
		{
			Logger::Warning("[ImagesMaintenance::DeleteImage]\n No se pudo borrar la imagen: "
					+ std::string("Usuario: " + std::to_string(user.GetIdUser()) + ", Imagen: " + imageId));

			JsonBuilder response;
		
			cout << "Content-Type: application/json\r\n\r\n" << endl;

			response.addBool("success", false)
					.addString("message", string("No se pudo borrar la imagen. Es posible que la imagen ya no exista."));

			return response.toString();
		}

		JsonBuilder response;
		
		cout << "Content-Type: application/json\r\n\r\n" << endl;

		response.addBool("success", true)
				.addString("message", string("Imagen eliminada correctamente."));

		return response.toString();
	}
	catch(const std::exception& e)
	{
		Logger::Error("[ImagesMaintenance::DeleteImage]\n No se pudo borrar la imagen: "
				+ std::string("Usuario: " + std::to_string(user.GetIdUser())));

		JsonBuilder response;
		
		cout << "Content-Type: application/json\r\n\r\n" << endl;

		response.addBool("success", false)
				.addString("message", string("Hubo un erro al intentar borrar la imagen.") + e.what());

		return response.toString();
	}
	
}

string UploadImage(Request& request, UserModel& user)
{
	if (request.GetMethod() != "POST")
	{
		Logger::Error("[ImagesMaintenance::UploadImage]\n. Método HTTP no válido");

		return ViewUtils::LoadAdvicePage("Método HTTP no válido");
	}

	if (!Authorization::CanUploadImages(user))
	{
		Logger::Warning("[ImagesMaintenance::UploadImage]\n No tiene permisos para ejecutar esta acción: " + string(user.GetIdUser() + ", " + user.GetName()));

		JsonBuilder response;
	
		cout << "Content-Type: application/json\r\n\r\n" << endl;

		response.addBool("success", false)
				.addString("message", string("No tiene permisos para ejecutar esta acción."));

		return response.toString();
	}

	try
	{
		string alias = request.GetBodyParam("alias");

		ImageDTO imageDto(alias, request.GetFile("image"));

		auto config = EnvLoader::Load("/usr/local/apache2/app/db.env");

		DBConnection db;

		db.Connect(config["DB_HOST"], config["DB_USER"], config["DB_PASS"], config["DB_NAME"], stoi(config["DB_PORT"]));

		ImagesRepository imagesRepository(db);
		ImagesService imagesService(imagesRepository);

		bool insertedImage = imagesService.UploadImage(user.GetIdUser(), Authorization::isAdmin(user), imageDto);

		if (!insertedImage)
		{
			Logger::Error("[ImagesMaintenance::UploadImage]\n. No se pudo insertar la imagen.");

			JsonBuilder response;
			
			cout << "Content-Type: application/json\r\n\r\n" << endl;

			response.addBool("success", false)
					.addString("message", string("No se pudo insertar la imagen."));

			return response.toString();
		}

		JsonBuilder response;
		
		cout << "Content-Type: application/json\r\n\r\n" << endl;

		response.addBool("success", true)
				.addString("message", string("Imagen guardada correctamente."));

		return response.toString();
	}
	catch(const exception& e)
	{
		Logger::Error("[ImagesMaintenance::UploadImage]\n. Hubo un error al guardar la imagen." + string(e.what()));

		JsonBuilder response;
		
		cout << "Content-Type: application/json\r\n\r\n" << endl;

		response.addBool("success", false)
				.addString("message", string("Hubo un error al guardar la imagen.") + e.what());

		return response.toString();
	}
	
}

string RenderImagesMaintenancePage(list<ImagesModel> images, int totalImages, int MaxCount)
{
	TemplateEngine templateEngine = TemplateEngine();
	ImagesMaintView view(templateEngine, images, totalImages, MaxCount, LIMIT, OFFSET);

	string renderedPage = view.Render();

	return renderedPage;
}

string LoadImageMaintenancePage(UserModel& userData)
{
	if (!Authorization::CanViewImagesMaintenance(userData))
	{
		Logger::Warning("[ImagesMaintenance::LoadImageMaintenancePage]\n No tiene permisos para acceder a este recurso: " + string(userData.GetIdUser() + ", " + userData.GetName()));

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
			Logger::Error("[ImagesMaintenance::LoadImageMaintenancePage]\n " + string("Hubo un erro al obtener la cantidad de imágenes asociadas al usuario."));

			totalImages = 0;
		}

		list<ImagesModel> images = imagesService.GetImagesFromUserInRange(userData.GetIdUser(), LIMIT, OFFSET);

		if (!images.empty() && images.front().GetIdImage() == -1)
		{
			Logger::Error("[ImagesMaintenance::LoadImageMaintenancePage]\n." + string("Hubo un error al obtener las imagenes asociadas al usuario."));

			images.clear();
		}

		return RenderImagesMaintenancePage(images, totalImages, Authorization::isAdmin(userData) ? MAXIMAGESADMIN : MAXIMAGES);
	}
	catch(const exception& e)
	{
		Logger::Error("[ImagesMaintenance::LoadImageMaintenancePage]\n. Hubo un error al cargar la pantalla de mantenimiento de imagenes. " + string(e.what()));

		return ViewUtils::LoadAdvicePage("Hubo un error al cargar la pantalla de mantenimiento de imagenes");
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
			Logger::Error("[ImagesMaintenance::LoadSession]\n." + sessionLoader.GetError());

			return ViewUtils::LoadAdvicePage(sessionLoader.GetError());
		}

		return string();
	}
	catch(const std::exception& e)
	{
		Logger::Error("[ImagesMaintenance::LoadSession]\n. Hubo un error al verificar la sesión. " + string(e.what()));

		return ViewUtils::LoadAdvicePage("Hubo un error al verificar la sesión.");
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

	if (request.GetContentLength() == 0)
		response = LoadImageMaintenancePage(user);
	else if (request.GetContentType().find("application/json") !=  string::npos)
		response = DeleteImage(request, user);
	else
		response = UploadImage(request, user);

	cout << response;

	return 0;
}
