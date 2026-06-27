#pragma once

#include "IEmailSender.hpp"

class EmailMessage;

class FakeEmailSender : public IEmailSender
{
public:
  bool Send(const EmailMessage& email) override;
};
