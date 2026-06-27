#pragma once

#include <string>

class OTPModel
{
public:
  OTPModel(int idOtp = 0, const std::string& secretOtp = "", bool isEnabled = false, int idOwnerUser = 0);
  ~OTPModel() = default;

  // Getters
  int GetIdOtp() const;
  std::string GetSecretOtp() const;
  bool IsEnabled() const;
  int GetIdOwnerUser() const;

  // Setters
  void SetIdOtp(int id);
  void SetSecretOtp(const std::string& secret);
  void SetIsEnabled(bool enabled);
  void SetIdOwnerUser(int idUser);

 private:
  int idOtp;
  std::string secretOtp;
  bool isEnabled;
  int idOwnerUser;
};
