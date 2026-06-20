#include "UserRepository.hpp"

#include <exception>

#include "DBConnection.hpp"
#include "Logger.hpp"
#include "Statement.hpp"
#include "UserModel.hpp"

using namespace std;

UserRepository::UserRepository(DBConnection &connection)
  : db(connection)
{
}

int UserRepository::GetUserIdByEmail(const string& email)
{
  int userId = 0;

  try
  {
    Statement stmt(db.GetConnection(), getIdByEmailQuery);

    stmt.BindString(email);

    stmt.BindResultInt(userId);

    stmt.Execute();

    stmt.Fetch();
    
    return userId;
  }
  catch(const std::exception& e)
  {
    Logger::Error(string("[UserRepository::GetUserIdByEmail]\n") + e.what());
    return -1;
  }

}

bool UserRepository::InsertNewUser(UserModel& userTemp)
{
  try
  {
    Statement stmt(db.GetConnection(), insertNewUserQuery);

    stmt.BindString(userTemp.GetName());
    stmt.BindUInt8(userTemp.GetAge());
    stmt.BindString(userTemp.GetEmail());
    stmt.BindString(userTemp.GetPassword());
    stmt.BindInt(2);

    stmt.Execute();

    return true;
  }
  catch(const std::exception& e)
  {
    Logger::Error(string("[UserRepository::InsertNewUser]\n") + e.what());
    return false;
  }
}

UserModel UserRepository::GetUserByCredentials(const string& email, const string& password)
{
  return UserModel();
}
