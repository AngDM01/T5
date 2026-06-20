#include "HomePageView.hpp"

#include <map>
#include <string>

#include "TemplateEngine.hpp"
#include "UserModel.hpp"

using namespace std;

HomePageView::HomePageView(TemplateEngine& templateEnginer, UserModel& userData)
  : DynamicView(templateEnginer), userData(userData)
{
}

string HomePageView::BuildPage()
{
  try
  {
    templateEnginer.LoadTemplate(pageRoute);
    return templateEnginer.RenderHtml(GetPageVariables());
  }
  catch (const exception& e)
  {
    return "<h1>Error: </h1><p>Un error ocurrió mientras se renderizaba la página de inicio.</p>";
  }
}

map<string, string> HomePageView::GetHeaderVariables()
{
  map<string, string> variables;

  variables["PAGETITLE"] = pageTitle;

  string options = "<a href=\"/cgi/CloseSessionCGI.cgi\" class=\"menu-item\">Cerrar Sesión</a>";

  variables["OPTIONS"] = options;

  return variables;
}

map<string, string> HomePageView::GetPageVariables()
{
  map<string, string> variables;

  variables["UserName"] = userData.GetName();
  variables["UserAge"] = userData.GetAge();
  variables["UserEmail"] = userData.GetEmail();

  return variables;
}
