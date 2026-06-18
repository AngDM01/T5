#include <iostream>
#include <cstdlib>
#include <string>

#include "Views/TemplateEngine.hpp"
#include "Views/View.hpp"
#include "Views/Static/StaticView.hpp"

using namespace std;

void loadLoginPage() {
  string loginRoute = "/usr/local/apache2/app/templates/Static/login.html";

  TemplateEngine templateEngine = TemplateEngine();
	StaticView view(templateEngine, loginRoute);

	string renderedPage = view.render();
  
	cout << renderedPage;
}

void loadHomePage() {
  const char* contentLengthStr = getenv("CONTENT_LENGTH");

  int contentLength = std::atoi(contentLengthStr);

  string body(contentLength, '\0');
  cin.read(&body[0], contentLength);

  cout << "Content-Type: application/json\r\n\r\n";
  cout << "{";
  cout << "\"success\": true,";
  cout << "\"message\": \"Inicio de sesión correcto. Redirigiendo...\",";
  cout << "\"data\": 1";
  cout << "}";
}

int main() {
  char* contentLength = getenv("CONTENT_LENGTH");
  
  if (!contentLength) {
    loadLoginPage();
  } else {
    loadHomePage();
  }

  return 0;
}