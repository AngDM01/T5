#pragma once

#include <vector>
#include <string>

class DBConnection;
class UserModel;

class UserRepository
{
 public:
  UserRepository(DBConnection &connection);
  ~UserRepository() = default;

  int GetUserIdByEmail(const std::string& email);
  bool InsertNewUser(UserModel& userTemp);
  int GetUserIdByCredentials(const std::string& email, const std::string& password);
  UserModel GetUserDataByUserId(int userId);

 private:
  DBConnection& db;

  const char* getIdByEmailQuery = "SELECT Id_user FROM Users WHERE Email = ?";
  const char* insertNewUserQuery = "INSERT INTO Users (Name, Age, Email, Password, Id_assigned_rol) VALUES (?, ?, ?, ?, ?)";
  const char* getUserIdByCredentialsQuery = "SELECT Id_User FROM Users WHERE Email = ? AND Password = ?";
  const char* getUserByIdUserQuery =
      "SELECT u.Id_user, u.Name, u.Age, u.Email, u.Id_assigned_rol, r.Description " \
      "FROM Users u " \
      "INNER JOIN Rol r ON u.Id_assigned_rol = r.Id_rol " \
      "WHERE u.Id_user = ?";
};
