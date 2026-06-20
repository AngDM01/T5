#include <iostream>
#include <cstdlib>
#include <string>

#include "TemplateEngine.hpp"
#include "View.hpp"
#include "StaticView.hpp"
#include "HomePageView.hpp" 
#include "EnvLoader.hpp"
#include "UserModel.hpp"

class DBConnection;
class UserRepository;
class UserService;

using namespace std;

void LoadLoginPage() {
  string loginRoute = "/usr/local/apache2/app/templates/Static/login.html";

  TemplateEngine templateEngine;
	StaticView view(templateEngine, loginRoute);

	string renderedPage = view.Render();
  
	cout << renderedPage;
}

void LoadHomePage() {
  string homeRoute = "/usr/local/apache2/app/templates/Static/home.html";

  TemplateEngine templateEngine;
	StaticView view(templateEngine, homeRoute);

	string renderedPage = view.Render();
  
	cout << renderedPage;
}

int main() {
  char* contentLength = getenv("CONTENT_LENGTH");
  
  if (!contentLength) {
    LoadLoginPage();
  } else {
    LoadHomePage();
  }

  return 0;
}
