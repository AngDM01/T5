#include "CreateLetterView.hpp"

CreateLetterView::CreateLetterView(TemplateEngine &templateEnginer, std::string catalogImages, std::string userImages)
  : DynamicView(templateEnginer, "/usr/local/apache2/app/templates/Dynamic/createLetter.html"),
  catalogImages(catalogImages),
  userImages(userImages)
{
}

std::map<std::string, std::string> CreateLetterView::GetHeaderVariables()
{
  map<string, string> variables;

  variables["PAGETITLE"] = pageTitle;

  string options = "<a href=\"#\" onclick=\"closeSession()\" class=\"menu-item\">Cerrar Sesión</a>";

  variables["OPTIONS"] = options;

  return variables;
}

std::map<std::string, std::string> CreateLetterView::GetPageVariables()
{
  map<string, string> variables;

  variables["CatalogImages"] = catalogImages;
  variables["UserImages"] = userImages;

  return variables;
}
