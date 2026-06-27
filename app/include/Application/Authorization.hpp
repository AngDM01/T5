#include "UserModel.hpp"

class Authorization
{
 public:
  static bool isAdmin(const UserModel& user);
  static bool isAdminRolId(const int rolId);
  static bool CanAccessHome(const UserModel& user);
  static bool CanViewLetters(const UserModel& user);
  static bool CanCreateLetter(const UserModel& user);
  static bool CanViewImagesMaintenance(const UserModel& user);
  static bool CanUploadImages(const UserModel& user);
  static bool CanDeleteImages(const UserModel& user);
  static bool CanMoveGallery(const UserModel& user);
  static bool CanViewLettersTables(const UserModel& user);
  static bool CanCloseSession(const UserModel& user);
  static bool CanSendLetters(const UserModel& user);
};
