#pragma once

#include <string>

class SendLetterDTO
{
public:
  SendLetterDTO(std::string from = "", std::string to = "", std::string toEmail = "", std::string title = "",
      std::string text = "", std::string imageId= "");
  ~SendLetterDTO() = default;

  // GETTERS
  std::string GetFrom() const;
  std::string GetTo() const;
  std::string GetToEmail() const;
  std::string GetTitle() const;
  std::string GetText() const;
  std::string GetImageId() const;

  // SETTERS
  void SetFrom(const std::string& from);
  void SetTo(const std::string& to);
  void SetToEmail(const std::string& toEmail);
  void SetTitle(const std::string& title);
  void SetText(const std::string& text);
  void SetImageId(const std::string& imageId);
  
 private:
  std::string from;
  std::string to;
  std::string toEmail;
  std::string title;
  std::string text;
  std::string imageId;
};
