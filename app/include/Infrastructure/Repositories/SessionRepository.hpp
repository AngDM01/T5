#pragma once

#include <string>

class DBConnection;

class SessionRepository
{
 public:
  SessionRepository(DBConnection &connection);
  ~SessionRepository() = default;

  bool CreateUserSession(int userId,  int expirationTime);
  std::string GetSessionIdByUserId(int userId);
  std::string CheckIsValidSession(std::string sessionId);
  int GetUserIdBySessionId(std::string sessionId);

 private:
  DBConnection& db;

  const char* createUserSessionQuery = "INSERT INTO Sessions (Id_associate_user, Expiration) VALUES (?, DATE_ADD(NOW(), INTERVAL ? MINUTE))";
  const char* getUserSessionQuery = "SELECT Id_session FROM Sessions WHERE Id_associate_user = ?";
  const char* checkValidSessionQuery = "SELECT CASE WHEN Expiration > NOW() THEN 'VALID' ELSE 'EXPIRED' END AS Status FROM Sessions WHERE Id_session = ?;";
  const char* getUserIdBySessionIdQuery = "SELECT Id_associate_user FROM Sessions WHERE Id_session = ?";
};
