#include "ImagesService.hpp"

#include <list>
#include <stdexcept>
#include <string>

#include "ImageDTO.hpp"
#include "ImagesModel.hpp"
#include "ImagesRepository.hpp"
#include "Validator.hpp"

#define MAXIMAGES 12

using namespace std;

ImagesService::ImagesService(ImagesRepository& repository)
  : repository(repository)
{
}

int ImagesService::GetTotalImagesCountFromUser(int userId)
{
  if (!Validator::IsValidUserId(userId))
  {
    throw runtime_error("Formato de identificardor de usuario no válido.");
  }
  
  int totalImagesCount = repository.GetImagesAsociateToUserCount(userId);

  return totalImagesCount;
}

list<ImagesModel> ImagesService::GetImagesFromUserInRange(int userId, int limit, int start)
{
  if (!Validator::IsValidUserId(userId))
  {
    throw runtime_error("Formato de identificardor de usuario no válido.");
  }

  if (!Validator::IsValidPositiveInt(limit))
  {
    throw runtime_error("Valor del limite de imagenes no válido");
  }

  if (!Validator::IsValidPositiveInt(start))
  {
    throw runtime_error("Valor de la imagen inicial no válido");
  }

  list<ImagesModel> images = repository.GetImagesInRangeByUploaderId(userId, limit, start);

  return images;
}

bool ImagesService::UploadImage(int userId, bool isCatalog, ImageDTO& imageDto)
{
  if (!Validator::IsValidUserId(userId))
  {
    throw runtime_error("Formato de identificardor de usuario no válido.");
  }

  if (!Validator::IsValidImageAlias(imageDto.GetAlias()))
  {
    throw runtime_error("El formato del alias no es válido");
  }

  if (!Validator::IsValidImageExtension(imageDto.GetExtension()))
  {
    throw runtime_error("La extensión del archivo no es válido");
  }

  if (!Validator::IsValidImageData(imageDto.GetImageData().data))
  {
    throw runtime_error("El archivo no puede estar vacío");
  }

  if (!Validator::IsValidImageSize(imageDto.GetImageData().data))
  {
    throw runtime_error("El archivo es demasiado grande. Máximo 16MB");
  }

  if (!isCatalog)
  {
    int imagesCount = GetTotalImagesCountFromUser(userId);

    if (imagesCount >= MAXIMAGES)
    {
      throw runtime_error("Limite de imagenes alcanzado");
    }
  }

  bool insertResult = repository.InsertImage(userId, isCatalog, imageDto);

  return insertResult;
}

bool ImagesService::DeleteImageById(int userId, string& imageId)
{
  if (!Validator::IsValidUserId(userId))
  {
    throw runtime_error("Formato de identificardor de usuario no válido.");
  }

  if (!Validator::IsValidImageId(imageId))
  {
    throw runtime_error("Formato del identificador de la Imagen no válido.");
  }

  int id = std::stoi(imageId);

  bool deleteResult = repository.DeleteImageFromUserByImageId(userId, id);

  return deleteResult;
}

std::list<ImagesModel> ImagesService::GetCatalogImagesInRange(int limit, int start)
{
  if (!Validator::IsValidPositiveInt(limit))
  {
    throw runtime_error("Valor del limite de imagenes no válido");
  }

  if (!Validator::IsValidPositiveInt(start))
  {
    throw runtime_error("Valor de la imagen inicial no válido");
  }

  list<ImagesModel> images = repository.GetCatalogImagesInRange(limit, start);

  return images;
}

ImagesModel ImagesService::GetImageByImageId(int imageId)
{
  if (!Validator::IsValidImageId(to_string(imageId)))
  {
    throw runtime_error("Formato del identificador de la Imagen no válido.");
  }

  ImagesModel image = repository.GetImageDataByImageId(imageId);

  return image;
}

int ImagesService::GetIsCatalogImagesCount()
{
  int isCatalogTotalImages = 0;

  isCatalogTotalImages = repository.GetIsCatalogTotalImagesCount();

  return isCatalogTotalImages;
}
