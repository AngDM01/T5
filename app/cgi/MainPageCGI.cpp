#include <iostream>
#include <string>

#include "TemplateEngine.hpp"
#include "View.hpp"
#include "StaticView.hpp"

using namespace std;

int main()
{
	string mainPageroute = "/usr/local/apache2/app/templates/Static/mainPage.html";

	TemplateEngine templateEngine = TemplateEngine();
	StaticView view(templateEngine, mainPageroute);

	string renderedPage = view.Render();

	cout << renderedPage;

	return 0;
}
