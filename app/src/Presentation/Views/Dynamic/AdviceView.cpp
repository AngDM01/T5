#include "AdviceView.hpp"

using namespace std;

AdviceView::AdviceView(TemplateEngine &templateEnginer, string message)
  : DynamicView(templateEnginer, "/usr/local/apache2/app/templates/Dynamic/advice.html")
  , message(message)
{
}

map<string, string> AdviceView::GetPageVariables()
{
  map<string, string> variables;

  variables["Message"] = message;

  return variables;
}
