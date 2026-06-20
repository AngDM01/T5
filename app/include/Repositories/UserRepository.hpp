#pragma once

#include <vector>
#include <string>

class DBConnection;
class UserModel;
class RegisterDTO;

class UserRepository
{
 public:
  UserRepository(DBConnection &connection);

  int GetUserIdByEmail(const std::string& email);
  bool InsertNewUser(UserModel& userTemp);
  UserModel GetUserByCredentials(const std::string& email, const std::string& password);

 private:
  DBConnection &db;

  const char* getIdByEmailQuery = "SELECT Id_user FROM Users WHERE Email = ?";
  const char* getByCredentialsQuery = "SELECT Id, Name, Email, CreatedAt FROM Users WHERE Email = ? AND Password = ?";
  const char* insertNewUserQuery = "INSERT INTO Users (Name, Age, Email, Password, Id_assigned_rol) VALUES (?, ?, ?, ?, ?)";
};
