#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "UploadedFile.hpp"

class ImageDTO
{
public:
  ImageDTO(const std::string& alias, UploadedFile imageData);
  ~ImageDTO() = default;

  // Getters
  const std::string& GetAlias() const;
  const std::string& GetExtension() const;
  const UploadedFile& GetImageData() const;

  // Setters
  void SetAlias(const std::string& alias);
  void SetExtension(const std::string& extension);
  void SetImageData(UploadedFile& imageData);

private:
  std::string alias;
  UploadedFile imageData;
  std::string extension;
};
