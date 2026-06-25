#pragma once

#include <list>
#include <map>
#include <string>

#include "DynamicView.hpp"
#include "TemplateEngine.hpp"

class ImagesModel;
class TemplateEngine;

class ImagesMaintView : public DynamicView
{
 public:
  ImagesMaintView(TemplateEngine& templateEnginer, std::list<ImagesModel>& images, int imagesCount, int maxImagesCount, int limit, int offset);
  ~ImagesMaintView() = default;

 protected:
  std::map<std::string, std::string> GetHeaderVariables() override;
  std::map<std::string, std::string> GetPageVariables() override;
  std::string CreateImagesCards();

 protected:
  std::list<ImagesModel>& images;
  int imagesCount;
  int maxImagesCount;
  int limit;
  int offset;
};
