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
  if (name.empty() || name.length() > 255) return false;

  return true;
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
  
  return true;
}
