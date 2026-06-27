#pragma once

class IEmailSender;
class IEmailValidator;
class EmailMessage;

class EmailService
{
 public:
  EmailService(IEmailSender& sender, IEmailValidator& validator);
  ~EmailService() = default;

  bool SendEmail(const EmailMessage& email);

 private:
  IEmailSender& sender;
  IEmailValidator& validator;
};
