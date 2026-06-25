#pragma once

#include <map>
#include <string>

#include "DynamicView.hpp"
#include "TemplateEngine.hpp"

class TemplateEngine;
class UserModel;

class AdviceView : public DynamicView
{
 public:
  AdviceView(TemplateEngine& templateEnginer, std::string message);
  ~AdviceView() = default;

 protected:
  std::map<std::string, std::string> GetPageVariables() override;

 protected:
  std::string message;
};
