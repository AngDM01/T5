#pragma once

#include <list>
#include <map>
#include <string>

#include "DynamicView.hpp"
#include "TemplateEngine.hpp"

class ImagesModel;
class TemplateEngine;

class CreateLetterView : public DynamicView
{
 public:
  CreateLetterView(TemplateEngine& templateEnginer, std::string catalogImages, std::string userImages);
  ~CreateLetterView() = default;

 protected:
  std::map<std::string, std::string> GetHeaderVariables() override;
  std::map<std::string, std::string> GetPageVariables() override;

 protected:
  std::string catalogImages;
  std::string userImages;
};
