#pragma once

class EmailMessage;

class IEmailValidator
{
public:
  virtual bool Validate(const EmailMessage& email) = 0;
  virtual ~IEmailValidator() = default;
};
