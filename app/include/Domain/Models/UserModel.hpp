#pragma once

#include <cstdint>
#include <string>

class UserModel
{
public:
  UserModel(int idUser = 0, const std::string& name = "", uint8_t age = 0, const std::string& email = "",
      const std::string& password = "", int idAssignedRol = 0, const std::string& rolDescription = "");

  ~UserModel() = default;

  // GETTERS
  int GetIdUser() const;
  const std::string& GetName() const;
  uint8_t GetAge() const;
  const std::string& GetEmail() const;
  const std::string& GetPassword() const;
  int GetIdAssignedRol() const;
  const std::string& GetRolDescription() const;

  // SETTERS
  void SetIdUser(int idUser);
  void SetName(const std::string &name);
  void SetAge(uint8_t age);
  void SetEmail(const std::string &email);
  void SetPassword(const std::string &password);
  void SetIdAssignedRol(int IdAssignedRol);
  void SetRolDescription(const std::string &rolDescription);

 private:
  int idUser;
  std::string name;
  uint8_t age;
  std::string email;
  std::string password;
  int IdAssignedRol;
  std::string rolDescription;
};
