#pragma once

#include <list>
#include <string>

class LetterModel;
class LettersRepository;
class SendLetterDTO;
class UserModel;

class LettersService
{
 public:
  LettersService(LettersRepository& lettersRepository);
  ~LettersService() = default;

  int GetUserSendedLetterCount(int userId);
  std::list<LetterModel> GetUserSendedLettersInRange(int userId, int limit, int offset);
  int GetUserReceivedLetterCount(int userId);
  std::list<LetterModel> GetUserReceivedLettersInRange(int userId, int limit, int offset);
  LetterModel GetLetterDetails(int userId, std::string& letterId);
  bool IsMarkedOpened(std::string& letterId);
  bool MarkedLetterAsOpened(int userId, std::string& letterId);
  bool SaveSendedLetter(SendLetterDTO& letterDTO, UserModel& userData, int receivedUser);
  void sendEmail(LetterModel& letter);
  
 private:
  LettersRepository& lettersRepository;
};
