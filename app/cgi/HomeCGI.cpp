#include <iostream>
#include <fstream>
#include <string>

#include "AdviceView.hpp"
#include "Authorization.hpp"
#include "DBConnection.hpp"
#include "EnvLoader.hpp"
#include "HomePageView.hpp"
#include "Logger.hpp"
#include "Request.hpp"
#include "SessionRepository.hpp"
#include "SessionService.hpp"
#include "StaticView.hpp"
#include "TemplateEngine.hpp"
#include "UserModel.hpp"
#include "UserRepository.hpp"
#include "UserService.hpp"
#include "View.hpp"

using namespace std;

std::string LoadAdvicePage(string message)
{
	TemplateEngine templateEngine = TemplateEngine();
	AdviceView view(templateEngine, message);

	string renderedPage = view.Render();

	return renderedPage;
}

string LoadHomePage(UserModel& userData)
{
	TemplateEngine templateEngine = TemplateEngine();
	HomePageView view(templateEngine, userData);

	string renderedPage = view.Render();

	return renderedPage;
}

string LoadSession()
{
	Request request;

	string sessionId = request.GetCookie("SESSION_ID");

	if (sessionId == "")
	{
		Logger::Info("[HomeCGI::LoadSession]\n No se exite la cookie de sesión.");

		return LoadAdvicePage("No se exite la cookie de sesión");
	}

	try
	{
		auto config = EnvLoader::Load("/usr/local/apache2/app/db.env");

		DBConnection db;

		db.Connect(config["DB_HOST"], config["DB_USER"], config["DB_PASS"],
        config["DB_NAME"], std::stoi(config["DB_PORT"]));

		SessionRepository sessionRepo(db);
		SessionService sessionService(sessionRepo);

		int userId = sessionService.GetUserIdBySessionId(sessionId);

		if (userId == 0)
		{
			Logger::Info("[HomeCGI::LoadSession]\n No existe usuario asociado a la sesión.");

			return LoadAdvicePage(" No existe usuario asociado a la sesión.");
		}

		if (userId == -1)
		{
			Logger::Info("[HomeCGI::LoadSession]\n No se pudo obtener el usuario asociado a la sesión.");

			return LoadAdvicePage("No se pudo obtener el usuario asociado a la sesión.");
		}

		UserRepository userRepo(db);
		UserService userService(userRepo);

		UserModel userData = userService.GetUserById(userId);

		if (userData.GetIdUser() == 0)
		{
			Logger::Info("[HomeCGI::LoadSession]\n No se pudo cargar al usuario.");

			return LoadAdvicePage("No se pudo cargar al usuario.");
		}

		if (userData.GetIdUser() == -1)
		{
			Logger::Error("[HomeCGI::LoadSession]\n Hubo un error al cargar el usuario.");

			return LoadAdvicePage("Hubo un error al cargar el usuario.");
		}

		if (!Authorization::CanAccessHome(userData))
		{
			Logger::Error("[HomeCGI::LoadSession]\n No tiene permisos para acceder a este recurso");

			return LoadAdvicePage("No tiene permisos para acceder a este recurso.");
		}

		return LoadHomePage(userData);
	}
	catch(const std::exception& e)
	{
		Logger::Error(string("[HomeCGI::main]\n") + e.what());

		return LoadAdvicePage(string("Hubo un error al cargar el usuario.") + e.what());
	}
}

int main()
{	
	string resultPage = LoadSession();

	cout << resultPage;
}
