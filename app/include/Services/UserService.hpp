#pragma once

#include <string>

class UserRepository;
class UserModel;
class RegisterDTO;
class LoginDTO;

class UserService
{
 public:
  UserService(UserRepository& Repository);
  ~UserService() = default;

  int UserAlreadyExistByCheckEmail(const std::string& email);
  bool RegisterNewUser(RegisterDTO& registerData);
  int GetUserIdByCredentials(LoginDTO& logiData);

 private:
  UserRepository& repository;
};
