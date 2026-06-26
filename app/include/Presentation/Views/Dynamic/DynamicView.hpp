#pragma once

#include "View.hpp"
#include "TemplateEngine.hpp"

#include <map>
#include <string>

using namespace std;

class DynamicView : public View
{
 public:
  DynamicView(TemplateEngine& templateEngine, std::string pageRoute)
    : View(templateEngine)
    , pageRoute(pageRoute)
  {
  }

  ~DynamicView() = default;

 protected:
  string BuildPage()
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

  virtual map<string, string> GetPageVariables() = 0;

 protected:
  std::string pageRoute;
};
