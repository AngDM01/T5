#include "SessionModel.hpp"

#include <string>

using namespace std;

SessionModel::SessionModel(const string& idSession, int idAssociateUser, const string& expiration)
  : idSession(idSession),
  idAssociateUser(idAssociateUser),
  expiration(expiration)
{
}

// Getters
const string& SessionModel::getIdSession() const
{
  return idSession;
}

int SessionModel::getIdAssociateUser() const
{
  return idAssociateUser;
}

const string& SessionModel::getExpiration() const
{
  return expiration;
}

// Setters
void SessionModel::setIdSession(const string& idSession)
{
  this->idSession = idSession;
}

void SessionModel::setIdAssociateUser(int idAssociateUser)
{
  this->idAssociateUser = idAssociateUser;
}

void SessionModel::setExpiration(const string& expiration)
{
  this->expiration = expiration;
}
