#pragma once

#include <string>

class DBConnection;

class SessionRepository
{
 public:
  SessionRepository(DBConnection &connection);

  bool CreateUserSession(int userId,  int expirationTime);
  std::string GetSessionIdByUserId(int userId);

 private:
  DBConnection& db;

  const char* createUserSessionQuery = "INSERT INTO Sessions (Id_associate_user, Expiration) VALUES (?, DATE_ADD(NOW(), INTERVAL ? MINUTE))";
  const char* getUserSessionQuery = "SELECT Id_session FROM Sessions WHERE Id_associate_user = ?";
};
