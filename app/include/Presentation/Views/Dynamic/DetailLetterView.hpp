#pragma once

#include "DynamicView.hpp"
#include "LetterModel.hpp"

class TemplateEngine;

class DetailLetterView : public DynamicView
{
 public:
  DetailLetterView(TemplateEngine& templateEngine, LetterModel& letter);
  ~DetailLetterView() = default;

 protected:
  std::map<std::string, std::string> GetHeaderVariables() override;
  std::map<std::string, std::string> GetPageVariables() override;

 protected:
  LetterModel letter;
};
