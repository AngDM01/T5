#pragma once

#include <string>

class SessionModel
{
public:
  SessionModel(const std::string& idSession = "", int idAssociateUser = 0, const std::string& expiration = "");
  ~SessionModel() = default;

  // Getters
  const std::string& getIdSession() const;
  int getIdAssociateUser() const;
  const std::string& getExpiration() const;

  // Setters
  void setIdSession(const std::string& idSession);
  void setIdAssociateUser(int idAssociateUser);
  void setExpiration(const std::string& expiration);

 private:
  std::string idSession;
  int idAssociateUser;
  std::string expiration;
};
