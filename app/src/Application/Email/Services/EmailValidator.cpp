#include "EmailValidator.hpp"

#include "EmailMessage.hpp"
#include "Validator.hpp"

bool EmailValidator::Validate(const EmailMessage &email)
{
  if (email.GetSenderName().empty())
    return false;

  if (email.GetReceiverName().empty())
    return false;

  if (email.GetSubject().empty())
    return false;

  if (email.GetBody().empty())
    return false;

  if (!Validator::IsValidEmail(email.GetSenderEmail()))
    return false;

  if (!Validator::IsValidEmail(email.GetReceiverEmail()))
    return false;

  return true;  
}
