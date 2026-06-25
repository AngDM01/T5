#pragma once

#include <string>

class DBConnection;

class LettersRepository
{
 public:
  LettersRepository(DBConnection &connection);
  ~LettersRepository() = default;

 private:
  DBConnection& db;

  const char* sendedLettersQuery =
      "SELECT Id_letter, Letter_title, Receiver_name, Receiver_email, Send_date " \
      "FROM Letters " \
      "WHERE Id_owner_user = ? " \
      "ORDER BY Send_date DESC " \
      "LIMIT ? OFFSET ?";
  const char* sendedLetterQuery =
      "SELECT Id_letter, Letter_title, Receiver_name, Receiver_email, Send_date " \
      "FROM Letters " \
      "WHERE Id_letter = ? ";
};
