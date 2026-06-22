#pragma once

#include<string>

class Validator
{
 public:
  static bool IsValidEmail(const std::string& email);
  static bool IsValidPassword(const std::string& password);
  static bool IsValidLoginPassword(const std::string& password);
  static bool IsValidName(const std::string& name);
  static bool IsValidAge(const std::string& age);
  static bool AreEqualPasswords(const std::string& password, const std::string& confPassword);
  static bool IsValidUserId(int userId);
  static bool IsValidExpiration(int expirationTime);
  static bool IsValidSessionId(std::string sessionId);
};
