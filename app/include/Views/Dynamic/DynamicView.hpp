#pragma once

#include "View.hpp"
#include "TemplateEngine.hpp"

#include <map>
#include <string>

using namespace std;

class DynamicView : protected View
{
 public:
  DynamicView(TemplateEngine& templateEngine)
    : View(templateEngine)
  {
  }

  ~DynamicView() = default;

 protected:
  virtual string BuildPage() = 0;
  virtual map<string, string> GetPageVariables() = 0;
};
