#include "OTPService.hpp"

#include <stdexcept>

#include "OTPModel.hpp"
#include "OTPRepository.hpp"
#include "Validator.hpp"

using namespace std;

OTPService::OTPService(OTPRepository& otpRepository)
  : otpRepository(otpRepository)
{
}

bool OTPService::VerifyOTP(int userId, string& otp)
{
  if (!Validator::IsValidUserId(userId))
  {
    throw runtime_error("Formato de identificardor de usuario no válido.");
  }

  if (!Validator::IsValidOTP(otp))
  {
    throw runtime_error("Formato de OTP no válido.");
  }

  OTPModel otpData = otpRepository.GetOTPByUserId(userId);

  if (!otpData.IsEnabled())
  {
    return false;
  }

  return ValidateYubiOTP(otpData.GetSecretOtp(), otp);
}

bool OTPService::ValidateYubiOTP(const string &storedKey, string &otp)
{
  string otpKeyId = otp.substr(0, storedKey.length());

  if (otpKeyId != storedKey) return false;

  if (IsOTPUsed(otp)) return false;

  return MarkOTPAsUsed(otp);
}

bool OTPService::IsOTPUsed(string &otp)
{
  if (!Validator::IsValidOTP(otp))
  {
    throw runtime_error("Formato de OTP no válido.");
  }

  bool result = otpRepository.CheckAlreadyUsed(otp);

  return result;
}

bool OTPService::MarkOTPAsUsed(string &otp)
{
  if (!Validator::IsValidOTP(otp))
  {
    throw runtime_error("Formato de OTP no válido.");
  }

  bool result = otpRepository.InsertUsedOTP(otp);

  return result;
}
