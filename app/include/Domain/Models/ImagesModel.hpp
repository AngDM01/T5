#pragma once

#include <cstdint>
#include <string>
#include <vector>

class ImagesModel
{

public:
  ImagesModel(int idImage = 0, const std::string& alias = "", const std::string& extension = "", const std::vector<uint8_t>& imageData = {},
      bool isCatalog = false, const std::string& uploadDate = "", int idUploaderUser = 0);
  ~ImagesModel() = default;

  // Getters
  int GetIdImage() const;
  const std::string& GetAlias() const;
  const std::string& GetExtension() const;
  const std::vector<uint8_t>& GetImageData() const;
  bool GetIsCatalog() const;
  const std::string& GetUploadDate() const;
  int GetIdUploaderUser() const;

  // Setters
  void SetIdImage(int idImage);
  void SetAlias(const std::string& alias);
  void SetExtension(const std::string& extension);
  void SetImageData(const std::vector<uint8_t>& imageData);
  void SetIsCatalog(bool isCatalog);
  void SetUploadDate(const std::string& uploadDate);
  void SetIdUploaderUser(int idUploaderUser);

 private:
  int idImage;
  std::string alias;
  std::string extension;
  std::vector<uint8_t> imageData;
  bool isCatalog;
  std::string uploadDate;
  int idUploaderUser;
};
