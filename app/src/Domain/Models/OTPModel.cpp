#include "OTPModel.hpp"

// Constructor completo
OTPModel::OTPModel(int idOtp, const std::string &secretOtp, bool isEnabled, int idOwnerUser)
  : idOtp(idOtp),
  secretOtp(secretOtp),
  isEnabled(isEnabled),
  idOwnerUser(idOwnerUser)
{
}

// Getters
int OTPModel::GetIdOtp() const
{
  return idOtp;
}

std::string OTPModel::GetSecretOtp() const
{
  return secretOtp;
}

bool OTPModel::IsEnabled() const
{
  return isEnabled;
}

int OTPModel::GetIdOwnerUser() const
{
  return idOwnerUser;
}

// Setters
void OTPModel::SetIdOtp(int id)
{
  this->idOtp = id;
}

void OTPModel::SetSecretOtp(const std::string &secret)
{
  this->secretOtp = secret;
}

void OTPModel::SetIsEnabled(bool enabled)
{
  this->isEnabled = enabled;
}

void OTPModel::SetIdOwnerUser(int idUser)
{
  this->idOwnerUser = idUser;
}
