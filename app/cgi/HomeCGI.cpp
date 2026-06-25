#include <iostream>
#include <string>

#include "Authorization.hpp"
#include "DBConnection.hpp"
#include "EnvLoader.hpp"
#include "HomePageView.hpp"
#include "Logger.hpp"
#include "SessionLoader.hpp"
#include "TemplateEngine.hpp"
#include "UserModel.hpp"
#include "ViewUtils.hpp"

using namespace std;

string RenderHomePage(UserModel& userData)
{
	TemplateEngine templateEngine = TemplateEngine();
	HomePageView view(templateEngine, userData);

	string renderedPage = view.Render();

	return renderedPage;
}

string LoadHomePage(UserModel& userData)
{
	if (!Authorization::CanAccessHome(userData))
	{
		Logger::Error("[HomeCGI::LoadHomePage]\n No tiene permisos para acceder a este recurso");

		return ViewUtils::LoadAdvicePage("No tiene permisos para acceder a este recurso.");
	}

	try
	{
		return RenderHomePage(userData);
	}
	catch(const std::exception& e)
	{
		Logger::Error("[HomeCGI::LoadSession]\n" + string(e.what()));

		return ViewUtils::LoadAdvicePage("Hubo un error al cargar la pantalla de inicio.");
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
	UserModel userData;
	
	string response = LoadSession(userData);
	
	if (!response.empty())
	{
		cout << response;
		return 0;
	}

	response = LoadHomePage(userData);

	cout << response;

	return 0;
}
