#include "EmailMessage.hpp"

EmailMessage::EmailMessage(const std::string &senderName, const std::string &senderEmail, const std::string &receiverName,
    const std::string &receiverEmail, const std::string &subject, const std::string &body)
  : senderName(senderName),
  senderEmail(senderEmail),
  receiverName(receiverName),
  receiverEmail(receiverEmail),
  subject(subject),
  body(body)
{
}

// Getters
const std::string &EmailMessage::GetSenderName() const
{
  return senderName;
}

const std::string &EmailMessage::GetSenderEmail() const
{
  return senderEmail;
}

const std::string &EmailMessage::GetReceiverName() const
{
  return receiverName;
}

const std::string &EmailMessage::GetReceiverEmail() const
{
  return receiverEmail;
}

const std::string &EmailMessage::GetSubject() const
{
  return subject;
}

const std::string &EmailMessage::GetBody() const
{
  return body;
}

// Setters
void EmailMessage::SetSenderName(const std::string &senderName)
{
  this->senderName = senderName;
}

void EmailMessage::SetSenderEmail(const std::string &senderEmail)
{
  this->senderEmail = senderEmail;
}

void EmailMessage::SetReceiverName(const std::string &receiverName)
{
  this->receiverName = receiverName;
}

void EmailMessage::SetReceiverEmail(const std::string &receiverEmail)
{
  this->receiverEmail = receiverEmail;
}

void EmailMessage::SetSubject(const std::string &subject)
{
  this->subject = subject;
}

void EmailMessage::SetBody(const std::string &body)
{
  this->body = body;
}
