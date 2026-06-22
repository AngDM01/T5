#include "UserModel.hpp"

class Authorization
{
 public:
  static bool CanAccessHome(const UserModel& user);
};
