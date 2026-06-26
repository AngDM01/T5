#pragma once

#include <list>
#include <string>

class LetterModel;
class LettersRepository;

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

 private:
  LettersRepository& lettersRepository;
};
