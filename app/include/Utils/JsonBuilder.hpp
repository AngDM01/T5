#pragma once

#include <string>
#include <vector>

class JsonBuilder
{
 public:
  JsonBuilder();

  JsonBuilder& addString(const std::string& key, const std::string& value);
  JsonBuilder& addBool(const std::string& key, bool value);
  JsonBuilder& addInt(const std::string& key, int value);

  std::string toString() const;

 private:
  std::vector<std::string> parts;
  static std::string escape(const std::string& s);
};
