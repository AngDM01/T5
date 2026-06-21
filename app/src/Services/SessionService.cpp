#include "SessionService.hpp"

#include <stdexcept>
#include <string>

#include "SessionRepository.hpp"
#include "Validator.hpp"

using namespace std;

SessionService::SessionService(SessionRepository& sessionRepository)
  :sessionRepository(sessionRepository)
{
}

string SessionService::CreateNewUserSession(int userId, int expirationTime)
{
  if (!Validator::IsValidUserId(userId))
  {
    throw runtime_error("Valor de identificador de usuario no válido.");
  }

  if (!Validator::IsValidExpiration(expirationTime))
  {
    throw runtime_error("Tiempo límite de expiración excedido." + expirationTime);
  }

  bool sessionCreated = sessionRepository.CreateUserSession(userId, expirationTime);

  if (!sessionCreated)
  {
    throw runtime_error("No se pudo crear la sesión");
  }

  string sessionId = sessionRepository.GetSessionIdByUserId(userId);

  return sessionId;
}
