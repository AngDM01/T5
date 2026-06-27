#pragma once

#include <string>

class SessionRepository;

class SessionService
{
 public:
  SessionService(SessionRepository& sessionRepository);
  ~SessionService() = default;

  std::string CreateNewUserSession(int userId,  int expirationTime);
  int GetUserIdBySessionId(std::string& sessionId);
  bool DeleteUserSession(std::string& sessionId);
  std::string CreatePendingAdminSession(int userId, int expirationTime);
  int GetPendingAdminUser(std::string& sessionId);
  bool DeletePendingAdminSession(int userId);

 private:
  SessionRepository& sessionRepository;
};
