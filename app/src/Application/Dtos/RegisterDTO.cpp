#include "RegisterDTO.hpp"

#include <string>

using namespace std;

RegisterDTO::RegisterDTO(const std::string& name, const std::string& age, const std::string& email,
      const std::string& password, const std::string& confirmedPassword)
  : name(name),
  age(age),
  email(email),
  password(password),
  confirmedPassword(confirmedPassword)
{
}

// Getters
const string& RegisterDTO::GetName() const
{
  return name;
}

const std::string& RegisterDTO::GetAge() const
{
  return age;
}

const string& RegisterDTO::GetEmail() const
{
  return email;
}

const string& RegisterDTO::GetPassword() const
{
  return password;
}

const string& RegisterDTO::GetConfirmedPassword() const
{
  return confirmedPassword;
}

// Setters
void RegisterDTO::SetName(const string& name)
{
  this->name = name;
}

void RegisterDTO::SetAge(const std::string& age)
{
  this->age = age;
}

void RegisterDTO::SetEmail(const string& email)
{
  this->email = email;
}

void RegisterDTO::SetPassword(const string& password)
{
  this->password = password;
}

void RegisterDTO::SetConfirmedPassword(const string& confirmedPassword)
{
  this->confirmedPassword = confirmedPassword;
}
