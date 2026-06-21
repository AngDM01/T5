#pragma once

#include <vector>
#include <string>

class DBConnection;
class UserModel;
class RegisterDTO;
class LoginDTO;

class UserRepository
{
 public:
  UserRepository(DBConnection &connection);

  int GetUserIdByEmail(const std::string& email);
  bool InsertNewUser(UserModel& userTemp);
  int GetUserIdByCredentials(const std::string& email, const std::string& password);

 private:
  DBConnection &db;

  const char* getIdByEmailQuery = "SELECT Id_user FROM Users WHERE Email = ?";
  const char* insertNewUserQuery = "INSERT INTO Users (Name, Age, Email, Password, Id_assigned_rol) VALUES (?, ?, ?, ?, ?)";
  const char* getUserIdByCredentialsQuery = "SELECT Id_User FROM Users WHERE Email = ? AND Password = ?";
};
