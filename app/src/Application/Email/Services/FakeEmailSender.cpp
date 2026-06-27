#include "FakeEmailSender.hpp"

#include "EmailMessage.hpp"
#include "Logger.hpp"

bool FakeEmailSender::Send(const EmailMessage &email)
{
  Logger::Info(email.GetSenderName());
  Logger::Info(email.GetSenderEmail());
  Logger::Info(email.GetReceiverName());
  Logger::Info(email.GetReceiverEmail());
  Logger::Info(email.GetSubject());
  Logger::Info(email.GetBody());
  Logger::Info("Correo enviado");

  return true;
}
