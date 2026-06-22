#pragma once

#include <string>

class SessionRepository;

class SessionService
{
 public:
  SessionService(SessionRepository& sessionRepository);
  ~SessionService() = default;

  std::string CreateNewUserSession(int userId,  int expirationTime);
  int GetUserIdBySessionId(std::string sessionId);

 private:
  SessionRepository& sessionRepository;
};
