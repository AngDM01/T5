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

int SessionService::GetUserIdBySessionId(std::string sessionId)
{
  if(!Validator::IsValidSessionId(sessionId))
  {
    throw runtime_error("Formato de identificador de sesión no válido.");
  }

  string existSession = sessionRepository.CheckIsValidSession(sessionId);

  if (existSession == "0" || existSession == "EXPIRED")
  {
    throw runtime_error("La sesión no existe o expiró.");
  }

  if (existSession.empty())
  {
    throw runtime_error("Hubo un error al verificar la sesión.");
  }

  int userId = sessionRepository.GetUserIdBySessionId(sessionId);

  return userId;
}
