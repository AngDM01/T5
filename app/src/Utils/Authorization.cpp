#include "Authorization.hpp"

#include "Logger.hpp"

enum class Role
{
  GUEST = 1,
  REGISTERED = 2,
  ADMIN = 3
};

bool Authorization::CanAccessHome(const UserModel& user)
{
  Role r = static_cast<Role>(user.GetIdAssignedRol());

  switch (r)
  {
    case Role::REGISTERED:
      return true;

    case Role::ADMIN:
      return true;

    default:
      return false;
  }
}
