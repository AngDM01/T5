#include "UserModel.hpp"

#include <string>

using namespace std;

UserModel::UserModel(int idUser, const string &name, uint8_t age, const string &email,
    const string &password, int idAssignedRol, const string &rolDescription)
  : idUser(idUser),
  name(name),
  age(age),
  email(email),
  password(password),
  IdAssignedRol(idAssignedRol),
  rolDescription(rolDescription)
{
}

// GETTERS
int UserModel::GetIdUser() const
{
  return idUser;
}

const std::string& UserModel::GetName() const
{
  return name;
}

uint8_t UserModel::GetAge() const
{
  return age;
}

const std::string& UserModel::GetEmail() const
{
  return email;
}

const std::string& UserModel::GetPassword() const
{
  return password;
}

int UserModel::GetIdAssignedRol() const
{
  return IdAssignedRol;
}

const std::string& UserModel::GetRolDescription() const
{
  return rolDescription;
}

// SETTERS
void UserModel::SetIdUser(int idUser)
{
  this->idUser = idUser;
}

void UserModel::SetName(const string& name)
{
  this->name = name;
}

void UserModel::SetAge(uint8_t age)
{
  this->age = age;
}

void UserModel::SetEmail(const string& email)
{
  this->email = email;
}

void UserModel::SetPassword(const string& password)
{
  this->password = password;
}

void UserModel::SetIdAssignedRol(int IdAssignedRol)
{
  this->IdAssignedRol = IdAssignedRol;
}

void UserModel::SetRolDescription(const string& rolDescription)
{
  this->rolDescription = rolDescription;
}
