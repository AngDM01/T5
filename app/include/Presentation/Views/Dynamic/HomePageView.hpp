#pragma once

#include <map>
#include <string>

#include "DynamicView.hpp"
#include "TemplateEngine.hpp"

class TemplateEngine;
class UserModel;

class HomePageView : public DynamicView
{
 public:
  HomePageView(TemplateEngine& templateEnginer, UserModel& userData);
  ~HomePageView() = default;

 protected:
  std::map<std::string, std::string> GetHeaderVariables() override;
  std::map<std::string, std::string> GetPageVariables() override;

 protected:
  UserModel& userData;
};
