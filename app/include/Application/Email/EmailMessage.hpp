#pragma once

#include <string>

class EmailMessage
{
public:
  EmailMessage();
  EmailMessage(const std::string& senderName, const std::string& senderEmail, const std::string& receiverName,
      const std::string& receiverEmail, const std::string& subject, const std::string& body);
  ~EmailMessage() = default;

  // Getters
  const std::string& GetSenderName() const;
  const std::string& GetSenderEmail() const;
  const std::string& GetReceiverName() const;
  const std::string& GetReceiverEmail() const;
  const std::string& GetSubject() const;
  const std::string& GetBody() const;

  // Setters
  void SetSenderName(const std::string& senderName);
  void SetSenderEmail(const std::string& senderEmail);
  void SetReceiverName(const std::string& receiverName);
  void SetReceiverEmail(const std::string& receiverEmail);
  void SetSubject(const std::string& subject);
  void SetBody(const std::string& body);

 private:
  std::string senderName;
  std::string senderEmail;

  std::string receiverName;
  std::string receiverEmail;

  std::string subject;
  std::string body;
};
