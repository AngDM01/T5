#pragma once

#include <string>

class LoginDTO
{
public:
  LoginDTO(const std::string& email = "", const std::string& password = "");
  ~LoginDTO() = default;

  // Getters
  const std::string& GetEmail() const;
  const std::string& GetPassword() const;

  // Setters
  void SetEmail(const std::string& email);
  void SetPassword(const std::string& password);

private:
  std::string email;
  std::string password;
};
