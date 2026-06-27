#include "EmailService.hpp"

#include "IEmailSender.hpp"
#include "IEmailValidator.hpp"

EmailService::EmailService(IEmailSender &sender, IEmailValidator &validator)
  : sender(sender),
  validator(validator)
{
}

bool EmailService::SendEmail(const EmailMessage &email)
{
  if (!validator.Validate(email)) return false;

  return sender.Send(email);
}
