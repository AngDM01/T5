#include <iostream>
#include <fstream>
#include <string>

#include "Views/TemplateEngine.hpp"
#include "Views/View.hpp"
#include "Views/Static/StaticView.hpp"

using namespace std;

int main()
{
	string mainPageroute = "/usr/local/apache2/app/templates/Static/mainPage.html";

	TemplateEngine templateEngine = TemplateEngine();
	StaticView view(templateEngine, mainPageroute);

	string renderedPage = view.render();

	cout << renderedPage;

	return 0;
}
