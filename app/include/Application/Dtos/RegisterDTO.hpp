#pragma once

#include <string>

class RegisterDTO
{
public:
  RegisterDTO(const std::string& name = "", const std::string& age = "0", const std::string& email = "",
      const std::string& password = "", const std::string& confirmedPassword = "");
  ~RegisterDTO() = default;

  // Getters
  const std::string& GetName() const;
  const std::string& GetAge() const;
  const std::string& GetEmail() const;
  const std::string& GetPassword() const;
  const std::string& GetConfirmedPassword() const;

  // Setters
  void SetName(const std::string& name);
  void SetAge(const std::string& age);
  void SetEmail(const std::string& email);
  void SetPassword(const std::string& password);
  void SetConfirmedPassword(const std::string& confirmedPassword);

private:
  std::string name;
  std::string age;
  std::string email;
  std::string password;
  std::string confirmedPassword;
};
