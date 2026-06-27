#pragma once

#include "IEmailTemplate.hpp"

class SendedLetterTemplate : public IEmailTemplate
{
  
  public:
  SendedLetterTemplate(const std::string& senderName, const std::string& senderEmail, const std::string& receiverName,
      const std::string& title);
  
  std::string Build() override;

 private:
  std::string senderName;
  std::string senderEmail;
  std::string receiverName;
  std::string title;
};
