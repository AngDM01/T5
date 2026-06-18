#include <iostream>
#include <cstdlib>
#include <string>

#include "Views/TemplateEngine.hpp"
#include "Views/View.hpp"
#include "Views/Static/StaticView.hpp"

void loadRegisterPage() {
  string registerRoute = "/usr/local/apache2/app/templates/Static/register.html";

  TemplateEngine templateEngine = TemplateEngine();
	StaticView view(templateEngine, registerRoute);

	string renderedPage = view.render();
  
	cout << renderedPage;
}

void loadLoginPage() {
  const char* contentLengthStr = getenv("CONTENT_LENGTH");

  int contentLength = std::atoi(contentLengthStr);

  string body(contentLength, '\0');
  cin.read(&body[0], contentLength);

  cout << "Content-Type: application/json\n\n";
  cout << "{";
  cout << "\"success\": " << "true" << ",";
  cout << "\"message\": \"" << "Registro exitoso, redirigiendo a iniciar sesión" << "\"";
  cout << "}";
}

int main() {
  char* contentLength = getenv("CONTENT_LENGTH");

  if (!contentLength) {
    loadRegisterPage();
  } else {
    loadLoginPage();
  }

  return 0;
}