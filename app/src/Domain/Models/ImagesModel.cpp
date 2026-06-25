#include "ImagesModel.hpp"

ImagesModel::ImagesModel(int idImage, const std::string& alias, const std::string& extension, const std::vector<uint8_t>& imageData,
    bool isCatalog, const std::string& uploadDate, int idUploaderUser)
  : idImage(idImage),
  alias(alias),
  extension(extension),
  imageData(imageData),
  isCatalog(isCatalog),
  uploadDate(uploadDate),
  idUploaderUser(idUploaderUser)
{
}

// Getters
int ImagesModel::GetIdImage() const
{
  return idImage;
}

const std::string& ImagesModel::GetAlias() const
{
  return alias;
}

const std::string& ImagesModel::GetExtension() const
{
  return extension;
}

const std::vector<uint8_t>& ImagesModel::GetImageData() const
{
  return imageData;
}

bool ImagesModel::GetIsCatalog() const
{
  return isCatalog;
}

const std::string& ImagesModel::GetUploadDate() const
{
  return uploadDate;
}

int ImagesModel::GetIdUploaderUser() const
{
  return idUploaderUser;
}

// Setters
void ImagesModel::SetIdImage(int idImage)
{
  this->idImage = idImage;
}

void ImagesModel::SetAlias(const std::string& alias)
{
  this->alias = alias;
}

void ImagesModel::SetExtension(const std::string& extension)
{
  this->extension = extension;
}

void ImagesModel::SetImageData(const std::vector<uint8_t>& imageData)
{
  this->imageData = imageData;
}

void ImagesModel::SetIsCatalog(bool isCatalog)
{
  this->isCatalog = isCatalog;
}

void ImagesModel::SetUploadDate(const std::string& uploadDate)
{
  this->uploadDate = uploadDate;
}

void ImagesModel::SetIdUploaderUser(int idUploaderUser)
{
  this->idUploaderUser = idUploaderUser;
}
