#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct UploadedFile
{
  std::string fieldName;
  std::string fileName;
  std::string contentType;
  std::vector<uint8_t> data;
};
