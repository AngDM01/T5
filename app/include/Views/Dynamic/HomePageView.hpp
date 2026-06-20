#pragma once

#include <map>
#include <string>

#include "DynamicView.hpp"
#include "TemplateEngine.hpp"

class View;
class TemplateEngine;
class UserModel;

class HomePageView : DynamicView
{
 public:
  HomePageView(TemplateEngine& templateEnginer, UserModel& userData);
  ~HomePageView() = default;

 protected:
  std::string BuildPage() override;
  std::map<std::string, std::string> GetHeaderVariables() override;
  std::map<std::string, std::string> GetPageVariables() override;

 protected:
  UserModel& userData;
  std::string pageRoute = "/usr/local/apache2/app/templates/Dynamic/home.html";
};
