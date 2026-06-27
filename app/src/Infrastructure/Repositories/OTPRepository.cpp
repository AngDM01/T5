#include "OTPRepository.hpp"

#include <string>

#include "DBConnection.hpp"
#include "Logger.hpp"
#include "OTPModel.hpp"
#include "Statement.hpp"

using namespace std;

OTPRepository::OTPRepository(DBConnection& connection)
  : db(connection)
{
}

OTPModel OTPRepository::GetOTPByUserId(int userId)
{
  try{
    Statement stmt(db.GetConnection(), GetOTPAdminByOwnerId);
    
    stmt.BindInt(userId);

    int otpId = 0;
    char secretOTP[256]{};
    uint8_t isEnabled = 0;
    int ownerUser = 0;

    stmt.BindResultInt(otpId);
    stmt.BindResultString(secretOTP, sizeof(secretOTP));
    stmt.BindResultUInt8(isEnabled);
    stmt.BindResultInt(ownerUser);

    stmt.Execute();
    
    if (!stmt.Fetch()) return OTPModel();
    
    stmt.Reset();

    return OTPModel(otpId, secretOTP, isEnabled != 0, ownerUser);
  }
  catch(const std::exception& e)
  {
    Logger::Error(string("[SessionRepository::GetOTPByUserId]\n") + e.what());
    return OTPModel(-1);
  }
}

bool OTPRepository::CheckAlreadyUsed(std::string &otp)
{
  try
  {
    Statement stmt(db.GetConnection(), CheckAlreadyUsedOTPQuery);

    stmt.BindString(otp);

    int exist = 0;

    stmt.BindResultInt(exist);

    stmt.Execute();

    if (!stmt.Fetch()) return false;

    return exist == 1;
  }
  catch (const std::exception &e)
  {
    Logger::Error(std::string("[SessionRepository::CheckAlreadyUsed]\n") + e.what());
    return false;
  }
}

bool OTPRepository::InsertUsedOTP(std::string &otp)
{
  try
  {
    Statement stmt(db.GetConnection(), InsertUsedOTPQuery);

    stmt.BindString(otp);

    stmt.Execute();

    return true;
  }
  catch (const std::exception &e)
  {
    Logger::Error(std::string("[SessionRepository::InsertUsedOTP]\n") + e.what());
    return false;
  }
}
