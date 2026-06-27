#include "SendLetterDTO.hpp"

SendLetterDTO::SendLetterDTO(std::string from, std::string to, std::string toEmail, std::string title,
    std::string text, std::string imageId)
  : from(from),
  to(to),
  toEmail(toEmail),
  title(title),
  text(text),
  imageId(imageId)
{
}

std::string SendLetterDTO::GetFrom() const { return from; }

std::string SendLetterDTO::GetTo() const { return to; }

std::string SendLetterDTO::GetToEmail() const { return toEmail; }

std::string SendLetterDTO::GetTitle() const { return title; }

std::string SendLetterDTO::GetText() const { return text; }

std::string SendLetterDTO::GetImageId() const { return imageId; }

void SendLetterDTO::SetFrom(const std::string& from)
{
  this->from = from;
}

void SendLetterDTO::SetTo(const std::string& to)
{
  this->to = to;
}

void SendLetterDTO::SetToEmail(const std::string& toEmail)
{
  this->toEmail = toEmail;
}

void SendLetterDTO::SetTitle(const std::string& title)
{
  this->title = title;
}

void SendLetterDTO::SetText(const std::string& text)
{
  this->text = text;
}

void SendLetterDTO::SetImageId(const std::string& imageId)
{
  this->imageId = imageId;
}