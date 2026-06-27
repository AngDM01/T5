#pragma once

class EmailMessage;

class IEmailSender
{
public:
  virtual bool Send(const EmailMessage& email) = 0;
  virtual ~IEmailSender() = default;
};
