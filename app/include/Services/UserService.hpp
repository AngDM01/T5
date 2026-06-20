#pragma once

#include <string>

class UserRepository;
class UserModel;
class RegisterDTO;


class UserService
{
 public:
  UserService(UserRepository& Repository);
  ~UserService() = default;

  int UserAlreadyExistByCheckEmail(const std::string& email);
  bool RegisterNewUser(RegisterDTO& registerData);
  UserModel GetUserByCredentials(const std::string& email, const std::string& password);

 private:
  UserRepository& repository;
};
