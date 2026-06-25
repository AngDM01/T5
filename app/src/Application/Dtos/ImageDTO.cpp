#include "ImageDTO.hpp"

#include <cstdint>
#include <string>
#include <vector>

using namespace std;

ImageDTO::ImageDTO(const std::string &alias, UploadedFile imageData)
  : alias(alias),
  imageData(imageData)
{
  if (imageData.contentType == "image/png")
    SetExtension("png");
  else if (imageData.contentType == "image/jpeg")
    SetExtension("jpeg");
  else if (imageData.contentType == "image/jpg")
    SetExtension("jpg");
  else
    SetExtension("");
}

const string &ImageDTO::GetAlias() const
{
  return alias;
}

const std::string& ImageDTO::GetExtension() const
{
  return extension;
}

const UploadedFile& ImageDTO::GetImageData() const
{
  return imageData;
}

void ImageDTO::SetAlias(const string& alias)
{
  this->alias = alias;
}

void ImageDTO::SetExtension(const std::string& extension)
{
  this->extension = extension;
}

void ImageDTO::SetImageData(UploadedFile& imageData)
{
  this->imageData = imageData;
}
