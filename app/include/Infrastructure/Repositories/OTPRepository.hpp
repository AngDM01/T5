#pragma once

#include <string>


class DBConnection;
class OTPModel;

class OTPRepository
{
public:
  OTPRepository(DBConnection& connection);
  ~OTPRepository() = default;

  OTPModel GetOTPByUserId(int userId);
  bool CheckAlreadyUsed(std::string& otp);
  bool InsertUsedOTP(std::string& otp);

 private:
  DBConnection& db;

  const char* GetOTPAdminByOwnerId = "SELECT Id_otp, Secret_otp, Is_enabled, Id_owner_user FROM OTP_admin WHERE Id_owner_user = ?";
  const char* CheckAlreadyUsedOTPQuery = "SELECT EXISTS(SELECT 1 FROM UsedOTPs WHERE Otp = ?);";
  const char* InsertUsedOTPQuery = "INSERT INTO UsedOTPs (Otp) VALUES (?)";
};
