#include "UserService.hpp"

#include <regex>
#include <stdexcept>
#include <string>

#include "Logger.hpp"
#include "LoginDTO.hpp"
#include "PasswordHasher.hpp"
#include "RegisterDTO.hpp"
#include "UserRepository.hpp"
#include "UserModel.hpp"
#include "Validator.hpp"

using namespace std;

UserService::UserService(UserRepository& repository)
  : repository(repository)
{
}

int UserService::UserAlreadyExistByCheckEmail(const string& email)
{
  if (!Validator::IsValidEmail(email))
  {
    throw runtime_error("Formato de correo no válido: " + email);
  }

  int idUser = 0;

  idUser = repository.GetUserIdByEmail(email);

  return idUser;
}

bool UserService::RegisterNewUser(RegisterDTO& registerData)
{
  UserModel userTemp;

  if (!Validator::IsValidName(registerData.GetName()))
  {
    throw runtime_error("Formato de nombre no válido: " + registerData.GetName());
  }

  userTemp.SetName(registerData.GetName());

  if (!Validator::IsValidAge(registerData.GetAge()))
  {
    throw runtime_error("Formato de edad no válido: " + registerData.GetAge());
  }

  uint8_t age = static_cast<uint8_t>(std::stoi(registerData.GetAge()));
  userTemp.SetAge(age);

  if (!Validator::IsValidEmail(registerData.GetEmail()))
  {
    throw runtime_error("Formato de correo no válido: " + registerData.GetEmail());
  }

  userTemp.SetEmail(registerData.GetEmail());

  if (!Validator::IsValidPassword(registerData.GetPassword()))
  {
    throw runtime_error("Formato de contraseña no válido");
  }

  string hashedPassword = PasswordHasher::hashPassword(registerData.GetPassword());
  userTemp.SetPassword(hashedPassword);

  if (!Validator::AreEqualPasswords(registerData.GetPassword(), registerData.GetConfirmedPassword()))
  {
    throw runtime_error("Las contraseñas no coinciden");
  }

  bool result = repository.InsertNewUser(userTemp);

  return result;
}

int UserService::GetUserIdByCredentials(LoginDTO& logiData)
{ 
  if (!Validator::IsValidEmail(logiData.GetEmail()))
  {
    throw runtime_error("Formato de correo no válido: " + logiData.GetEmail());
  }

  if (!Validator::IsValidLoginPassword(logiData.GetPassword()))
  {
    throw runtime_error("Formato de contraseña no válido: " + logiData.GetPassword());
  }

  string hashedPassword = PasswordHasher::hashPassword(logiData.GetPassword());

  int idUser = 0;

  idUser = repository.GetUserIdByCredentials(logiData.GetEmail(), hashedPassword);

  return idUser;
}

UserModel UserService::GetUserById(int userId)
{
  if (!Validator::IsValidUserId(userId))
  {
    throw runtime_error("Formato de identificardor de usuario no válido.");
  }

  UserModel userData = repository.GetUserDataByUserId(userId);

  return userData;
}

int UserService::GetUserRol(int userId)
{
  if (!Validator::IsValidUserId(userId))
  {
    throw runtime_error("Formato de identificardor de usuario no válido.");
  }

  int rol = repository.GetUserRolByUserId(userId);

  return rol;
}
