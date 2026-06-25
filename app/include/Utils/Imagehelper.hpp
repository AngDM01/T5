#pragma once

#include <cstdint>
#include <string>
#include <vector>

class Imagehelper
{
public:
  static std::string Encode(const std::vector<uint8_t>& data);
  static std::string ImageExtensionMIME(const std::string& extension);
  static std::string ExtensionFromMIME(const std::string& mime);
};