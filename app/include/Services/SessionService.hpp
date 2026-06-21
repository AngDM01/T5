#pragma once

#include <string>

class SessionRepository;

class SessionService
{
 public:
  SessionService(SessionRepository& sessionRepository);
  ~SessionService() = default;

  std::string CreateNewUserSession(int userId,  int expirationTime);

 private:
  SessionRepository& sessionRepository;
};
