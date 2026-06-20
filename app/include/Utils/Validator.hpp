#pragma once

#include<string>

class Validator
{
 public:
  static bool IsValidEmail(const std::string& email);
  static bool IsValidPassword(const std::string& password);
  static bool IsValidName(const std::string& name);
  static bool IsValidAge(const std::string& age);
  static bool AreEqualPasswords(const std::string& password, const std::string& confPassword);
};
