#pragma once

#include <list>
#include <string>

class ImagesModel;

class ComponentsBuilder
{
 public:
  ComponentsBuilder() = default;
  ~ComponentsBuilder() = default;

  std::string BuildImageCarrouselType2(std::list<ImagesModel>& images, std::string containerId, int imagesCount, int limit, int offset);
  std::string BuildImageCarrouselType1(std::list<ImagesModel>& images, std::string containerId, int imagesCount,
      int limit, int offset, bool isCatalog = false);
 
 private:
};
