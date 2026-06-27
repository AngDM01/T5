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

    stmt.Reset();

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

    stmt.Reset();

    return true;
  }
  catch(const std::exception& e)
  {
    Logger::Error(string("[UserRepository::InsertNewUser]\n") + e.what());
    return false;
  }
}

int UserRepository::GetUserIdByCredentials(const string& email, const string& password)
{
  try
  {
    Statement stmt(db.GetConnection(), getUserIdByCredentialsQuery);

    stmt.BindString(email);
    stmt.BindString(password);

    int userId = 0;

    stmt.BindResultInt(userId);

    stmt.Execute();

    stmt.Reset();

    stmt.Fetch();

    return userId;
  }
  catch(const std::exception& e)
  {
    Logger::Error(string("[UserRepository::GetUserIdByCredentials]\n") + e.what());
    return -1;
  }
}

UserModel UserRepository::GetUserDataByUserId(int userId)
{
  try
  {
    Statement stmt(db.GetConnection(), getUserByIdUserQuery);

    stmt.BindInt(userId);

    int id;
    char name[101]{};
    uint8_t age;
    char email[256]{};
    int rolId;
    char description[256]{};

    stmt.BindResultInt(id);
    stmt.BindResultString(name, sizeof(name));
    stmt.BindResultUInt8(age);
    stmt.BindResultString(email, sizeof(email));
    stmt.BindResultInt(rolId);
    stmt.BindResultString(description, sizeof(description));

    stmt.Execute();

    if (!stmt.Fetch()) return UserModel();
    
    stmt.Reset();

    return UserModel(id, name, age, email, "", rolId, description);
  }
  catch(const std::exception& e)
  {
    Logger::Error(string("[UserRepository::InsertNewUser]\n") + e.what());
    return UserModel(-1);
  }
}

int UserRepository::GetUserRolByUserId(int userId)
{
  try
  {
    Statement stmt(db.GetConnection(), getUserRolByUserId);

    stmt.BindInt(userId);

    int rolId = 0;

    stmt.BindResultInt(rolId);

    stmt.Execute();
    
    if (!stmt.Fetch()) return 0;
    
    stmt.Reset();

    return rolId;
  }
  catch(const std::exception& e)
  {
    Logger::Error(string("[UserRepository::GetUserRolByUserId]\n") + e.what());
    return -1;
  }
}
