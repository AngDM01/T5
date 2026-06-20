#pragma once

#include <map>
#include <string>

class EnvLoader
{
public:
  static std::map<std::string, std::string> Load(const std::string &file);
};
