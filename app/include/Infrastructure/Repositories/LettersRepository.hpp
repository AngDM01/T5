#pragma once

#include <list>

class DBConnection;
class LetterModel;

class LettersRepository
{
 public:
  LettersRepository(DBConnection &connection);
  ~LettersRepository() = default;

  int GetSendedLettersCountByOwnerId(int ownerId);
  std::list<LetterModel> GetSendedLettersBriefByOwnerId(int ownerId, int limit, int offset);
  int GetReceivedLettersCountByReceiverId(int receiverId);
	std::list<LetterModel> GetReceivedLettersBriefByReceiverId(int receiverId, int limit, int offset);
	LetterModel GetLetterFromUserByLetterId(int userId, int letterIdInt);
  bool GetOpenedStatus(int letterIdInt);
  bool ChangeLetterOpenedStatus(int userId, int letterIdInt, bool status);
  bool InsertLetter(LetterModel& letter);

 private:
  DBConnection& db;

  const char* getSendedLettersCountByOwnerIdQuery = "SELECT COUNT(*) AS TotalSendedLetters FROM Letters WHERE Id_owner_user = ?";
  const char* sendedLettersbriefByOwnerIdQuery =
      "SELECT Id_letter, Letter_title, Receiver_name, Receiver_email, Send_date " \
      "FROM Letters " \
      "WHERE Id_owner_user = ? " \
      "ORDER BY Send_date DESC " \
      "LIMIT ? OFFSET ?";
  const char* getReceivedLettersCountByReceiverIdQuery = "SELECT COUNT(*) AS TotalSendedLetters FROM Letters WHERE Id_receiver_user = ?";
	const char* receivedLettersbriefByReceiverIdQuery =
      "SELECT Id_letter, Letter_title, Sender_name, Sender_email, Send_date, Opened " \
      "FROM Letters " \
      "WHERE Id_receiver_user = ? " \
      "ORDER BY Send_date DESC " \
      "LIMIT ? OFFSET ?";
	const char* getLetterFromUserByLetterIdQuery =
			"SELECT Id_letter, Letter_title, Sender_name, Sender_email, Receiver_name, Receiver_email, Text_letter, " \
			"Send_date, Opened, Id_associate_image, Id_owner_user, Id_receiver_user " \
			"FROM Letters " \
			"WHERE Id_letter = ? " \
			"AND (Id_owner_user = ? OR Id_receiver_user = ?)";
  const char* sendedLetterQuery =
      "SELECT Id_letter, Letter_title, Receiver_name, Receiver_email, Send_date " \
      "FROM Letters " \
      "WHERE Id_letter = ? ";
  const char* geteOpenedLetterStatus = "SELECT Opened FROM Letters WHERE Id_letter = ?";
  const char* updateOpenedStatusQuery = "UPDATE Letters SET Opened = ? WHERE Id_letter = ? AND Id_receiver_user = ?;";
  const char* insertNewLetterQuery =
      "INSERT INTO Letters (Letter_title, Sender_name, Sender_email, Receiver_name, Receiver_email, Text_letter, " \
      "Id_associate_image, Id_owner_user, Id_receiver_user) " \
      "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);";
};
