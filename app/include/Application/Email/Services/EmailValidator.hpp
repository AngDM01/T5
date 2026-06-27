#pragma once

#include "IEmailValidator.hpp"

class EmailMessage;

class EmailValidator : public IEmailValidator
{
public:
  bool Validate(const EmailMessage& email) override;
};
