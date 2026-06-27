#include "Validator.hpp"

#include <cctype>
#include<string>
#include <regex>
#include <iostream>

using namespace std;

bool Validator::IsValidEmail(const string& email)
{
  if (email.empty() || email.length() > 255) return false;

  static const regex emailRegex(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");

  return regex_match(email, emailRegex);
}

bool Validator::IsValidPassword(const string& password)
{
  if (password.empty() || password.length() > 255) return false;

  bool hasUppercase = false;
  bool hasSpecialCharacter = false;

  for (unsigned char c : password)
  {
    if (isupper(c))
      hasUppercase = true;
    else if (!isalnum(c))
      hasSpecialCharacter = true;
  }

  return hasUppercase && hasSpecialCharacter;
}

bool Validator::IsValidLoginPassword(const std::string &password)
{
  if (password.empty() || password.length() > 255) return false;

  return true;
}

bool Validator::IsValidName(const string& name)
{
  if (name.empty() || name.length() > 100) return false;

  for (char c : name)
      if (!isspace(c)) return true;

  return false;
}

bool Validator::IsValidAge(const string& age)
{
  if (age.empty() || age.length() > 3) return false;

  for (unsigned char c : age)
  {
    if (!isdigit(c)) return false;
  }

  int value = std::stoi(age);

  return value >= 18 && value <= 150;
}

bool Validator::AreEqualPasswords(const string& password, const string& confPassword)
{
  if (password.length() != confPassword.length()) return false;

  return password == confPassword;
}

bool Validator::IsValidUserId(int userId)
{
  if (userId < 1) return false;

  return true;
}

bool Validator::IsValidExpiration(int expirationTime)
{
  if (expirationTime < 0 || expirationTime > 120) return false;

  return true;
}

bool Validator::IsValidSessionId(std::string sessionId)
{
  if (sessionId.empty()) return false;

  if (sessionId.length() != 36) return false;
  
  for (char c : sessionId)
      if (!isspace(c)) return true;

  return false;
}

bool Validator::IsValidPositiveInt(int value)
{
  if (value < 0) return false;
  
  return true;
}

bool Validator::IsValidImageAlias(const std::string& alias)
{
  if (alias.empty()) return false;
  if (alias.size() > 255) return false;

  for (char c : alias)
      if (!isspace(c)) return true;

  return false;
}

bool Validator::IsValidImageExtension(const std::string& extension)
{
  return extension == "png" || extension == "jpg" || extension == "jpeg";
}

bool Validator::IsValidImageData(const std::vector<uint8_t>& data)
{
  return !data.empty();
}

bool Validator::IsValidImageSize(const std::vector<uint8_t>& data)
{
  const size_t MAX_SIZE = 16 * 1024 * 1024; // 16MB (MEDIUMBLOB)

  return data.size() > 0 && data.size() <= MAX_SIZE;
}

bool Validator::IsValidImageId(const std::string& imageId)
{
  if (imageId.empty()) return false;

  for (char c : imageId)
  {
    if (!std::isdigit(static_cast<unsigned char>(c))) return false;
  }

  try
  {
    long id = std::stol(imageId);
    return id > 0;
  }
  catch (...)
  {
    return false;
  }
}

bool Validator::IsValidOffset(const std::string& offset)
{
  if (offset.empty()) return false;

  for (char c : offset)
  {
    if (!std::isdigit(static_cast<unsigned char>(c))) return false;
  }

  try
  {
    long offs = std::stol(offset);
    return offs >= 0;
  }
  catch (...)
  {
    return false;
  }
}

bool Validator::IsValidLetterId(const std::string& letterId)
{
  if (letterId.empty()) return false;

  for (char c : letterId)
  {
    if (!std::isdigit(static_cast<unsigned char>(c))) return false;
  }

  try
  {
    long id = std::stol(letterId);
    return id > 0;
  }
  catch (...)
  {
    return false;
  }
}

bool Validator::IsValidOTP(const std::string &otp)
{
  if (otp.empty() || otp.length() < 12) return false;

  return true;
}

bool Validator::IsValidTextLetter(const std::string &text)
{
  if (text.length() > 2000) return false;

  for (char c : text)
      if (!isspace(c)) return true;

  return false;
}
