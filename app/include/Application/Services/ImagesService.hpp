#pragma once

#include <list>
#include <string>

class ImageDTO;
class ImagesModel;
class ImagesRepository;

class ImagesService
{
public:
  ImagesService(ImagesRepository& repository);
  ~ImagesService() = default;

  int GetTotalImagesCountFromUser(int userId);
  std::list<ImagesModel> GetImagesFromUserInRange(int userId, int limit, int start);
  bool UploadImage(int userId, bool isCatalog, ImageDTO& imageDto);
  bool DeleteImageById(std::string& imageId);
  int GetIsCatalogImagesCount();
  std::list<ImagesModel> GetCatalogImagesInRange(int limit, int start);

 private:
  ImagesRepository& repository;
};
