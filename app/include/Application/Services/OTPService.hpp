#pragma once

#include <string>

class OTPRepository;

class OTPService
{
public:
  OTPService(OTPRepository& otpRepository);
  ~OTPService() = default;

  bool VerifyOTP(int userId, std::string& otp);

 private:
  bool ValidateYubiOTP(const std::string& storedKey, std::string& otp);
  bool IsOTPUsed(std::string& otp);
  bool MarkOTPAsUsed(std::string& otp);

 private:
  OTPRepository& otpRepository;
};
