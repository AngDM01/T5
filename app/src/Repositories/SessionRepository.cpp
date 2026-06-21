#include "SessionRepository.hpp"

#include "DBConnection.hpp"
#include "Logger.hpp"
#include "Statement.hpp"

using namespace std;

SessionRepository::SessionRepository(DBConnection &connection)
  : db(connection)
{
}

bool SessionRepository::CreateUserSession(int userId,  int expirationTime)
{
  Logger::Debug("UserId: " + std::to_string(userId));
  try
  {
    Statement stmt(db.GetConnection(), createUserSessionQuery);

    stmt.BindInt(userId);
    stmt.BindInt(expirationTime);

    stmt.Execute();
    
    stmt.Reset();
    
    return true;
  }
  catch(const std::exception& e)
  {
    Logger::Error(string("[SessionRepository::CreateUserSession]\n") + e.what());
    return false;
  }
}

string SessionRepository::GetSessionIdByUserId(int userId)
{
  try
  {
    Statement stmt(db.GetConnection(), getUserSessionQuery);

    stmt.BindInt(userId);

    char sessionId[37]{};

    stmt.BindResultString(sessionId, sizeof(sessionId));

    stmt.Execute();
    
    stmt.Reset();

    if (!stmt.Fetch()) return string("0");

    return string(sessionId);
  }
  catch(const std::exception& e)
  {
    Logger::Error(string("[SessionRepository::GetSessionIdByUserId]\n") + e.what());
    return string();
  }
}
