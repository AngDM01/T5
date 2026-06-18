#pragma once

#include "../View.hpp"
#include "../TemplateEngine.hpp"

#include <map>
#include <string>

using namespace std;

class DynamicView : View
{
 protected:
  virtual string buildPage() = 0;
  {
    map<string, string> variables;

    variables["PAGETITLE"] = pageTitle;
    variables["AUTHOR"] = "Ángel Jesús Mena Coudin";
    variables["YEAR"] = year;

    return variables;
  }

 protected:
  virtual map<string, string> getPageVariables() = 0;
};
