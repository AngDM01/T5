#pragma once

#include "View.hpp"
#include "TemplateEngine.hpp"

#include <map>
#include <string>

using namespace std;

class StaticView : public View
{
 public:
  StaticView(TemplateEngine& templateEnginer, string staticPageRoute)
      : View(templateEnginer), staticPageRoute(staticPageRoute) {}

  ~StaticView() = default;
  
 protected:
  string BuildPage() override
  {
    try {
      templateEnginer.LoadTemplate(staticPageRoute);
      return templateEnginer.RenderHtml();
    }
    catch (const exception& e) {
      cerr << "Error: " << e.what() << endl;
      return "<html><body><h1>Error</h1><p>Un error ocurrió mientras se renderizaba el contenido.</p></body></html>";
    }
  }

 protected:
  string staticPageRoute;
};
