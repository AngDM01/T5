#pragma once

#include <cstdint>
#include<string>
#include <vector>

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
  static bool IsValidPositiveInt(int value);
  static bool IsValidImageAlias(const std::string& alias);
  static bool IsValidImageExtension(const std::string& extension);
  static bool IsValidImageData(const std::vector<uint8_t>& data);
  static bool IsValidImageSize(const std::vector<uint8_t>& data);
  static bool IsValidImageId(const std::string& imageId);
  static bool IsValidOffset(const std::string& offset);
  static bool IsValidLetterId(const std::string& letterId);
};
