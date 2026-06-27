#include "Authorization.hpp"

#include "Logger.hpp"

enum class Role
{
  GUEST = 1,
  REGISTERED = 2,
  ADMIN = 3
};

bool Authorization::isAdmin(const UserModel &user)
{
  Role r = static_cast<Role>(user.GetIdAssignedRol());

  switch (r)
  {
    case Role::REGISTERED:
      return false;

    case Role::ADMIN:
      return true;

    default:
      return false;
  }
}

bool Authorization::isAdminRolId(const int rolId)
{
  Role r = static_cast<Role>(rolId);

  switch (r)
  {
    case Role::REGISTERED:
      return false;

    case Role::ADMIN:
      return true;

    default:
      return false;
  }
}

bool Authorization::CanAccessHome(const UserModel &user)
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

bool Authorization::CanViewLetters(const UserModel &user)
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

bool Authorization::CanCreateLetter(const UserModel &user)
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

bool Authorization::CanViewImagesMaintenance(const UserModel &user)
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

bool Authorization::CanUploadImages(const UserModel &user)
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

bool Authorization::CanDeleteImages(const UserModel &user)
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

bool Authorization::CanMoveGallery(const UserModel &user)
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

bool Authorization::CanViewLettersTables(const UserModel &user)
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

bool Authorization::CanCloseSession(const UserModel &user)
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
