#include "LoginDTO.hpp"

#include <string>

using namespace std;

LoginDTO::LoginDTO(const std::string& email, const std::string& password)
  : email(email),
  password(password)
{
}

// Getters
const string& LoginDTO::GetEmail() const
{
  return email;
}

const string& LoginDTO::GetPassword() const
{
  return password;
}

// Setters
void LoginDTO::SetEmail(const string& email)
{
  this->email = email;
}

void LoginDTO::SetPassword(const string& password)
{
  this->password = password;
}
