#pragma once

#include <string>

#include "UserModel.hpp"
#include "DBConnection.hpp"

class SessionLoader
{
 public:
  explicit SessionLoader(DBConnection& db);

  bool Load(UserModel& user);

  const std::string& GetError() const;

 private:
  DBConnection& db;
  std::string error;
};
