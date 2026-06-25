#include "ViewUtils.hpp"

#include "AdviceView.hpp"
#include "TemplateEngine.hpp"

using namespace std;

string ViewUtils::LoadAdvicePage(const string& message)
{
  TemplateEngine templateEngine;
  AdviceView view(templateEngine, message);

  return view.Render();
}
