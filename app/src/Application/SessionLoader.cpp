#include "SessionLoader.hpp"

#include "EnvLoader.hpp"
#include "Logger.hpp"
#include "Request.hpp"
#include "SessionRepository.hpp"
#include "SessionService.hpp"
#include "UserRepository.hpp"
#include "UserService.hpp"

SessionLoader::SessionLoader(DBConnection& db)
  : db(db)
{
}

bool SessionLoader::Load(UserModel& user)
{
  Request request;

  std::string sessionId = request.GetCookie("SESSION_ID");

  if (sessionId.empty())
  {
    error = "No existe la cookie de sesión.";
    return false;
  }

  SessionRepository sessionRepo(db);
  SessionService sessionService(sessionRepo);

  int userId = sessionService.GetUserIdBySessionId(sessionId);

  if (userId == 0)
  {
    error = "No existe usuario asociado a la sesión. ";
    return false;
  }

  if (userId == -1)
  {
    error = "No se pudo obtener el usuario asociado a la sesión. ";
    return false;
  }

  UserRepository userRepo(db);
  UserService userService(userRepo);

  user = userService.GetUserById(userId);

  if (user.GetIdUser() == 0)
  {
    error = "No se pudo cargar al usuario. ";
    return false;
  }

  if (user.GetIdUser() == -1)
  {
    error = "Hubo un error al cargar al usuario. ";
    return false;
  }

  return true;
}

const std::string& SessionLoader::GetError() const
{
  return error;
}
