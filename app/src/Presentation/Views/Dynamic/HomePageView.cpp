#include "HomePageView.hpp"

#include <map>
#include <string>

#include "TemplateEngine.hpp"
#include "UserModel.hpp"

using namespace std;

HomePageView::HomePageView(TemplateEngine& templateEnginer, UserModel& userData)
  : DynamicView(templateEnginer, "/usr/local/apache2/app/templates/Dynamic/home.html")
  , userData(userData)
{
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
  variables["UserAge"] = to_string(static_cast<int>(userData.GetAge()));
  variables["UserEmail"] = userData.GetEmail();

  return variables;
}
