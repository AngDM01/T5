#pragma once

#include <string>

class IEmailTemplate
{
public:
  virtual std::string Build() = 0;
  virtual ~IEmailTemplate() = default;
};
