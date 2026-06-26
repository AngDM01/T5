#include "LettersService.hpp"

#include <list>
#include <stdexcept>

#include "LetterModel.hpp"
#include "LettersRepository.hpp"
#include "Validator.hpp"

using namespace std;

LettersService::LettersService(LettersRepository& lettersRepository)
  : lettersRepository(lettersRepository)
{
}

int LettersService::GetUserSendedLetterCount(int userId)
{
  if (!Validator::IsValidUserId(userId))
  {
    throw runtime_error("Formato de identificardor de usuario no válido.");
  }
  
  int totalSendedLettersCount = lettersRepository.GetSendedLettersCountByOwnerId(userId);

  return totalSendedLettersCount;
}

list<LetterModel> LettersService::GetUserSendedLettersInRange(int userId, int limit, int offset)
{
  if (!Validator::IsValidUserId(userId))
  {
    throw runtime_error("Formato de identificardor de usuario no válido.");
  }

  if (!Validator::IsValidPositiveInt(limit))
  {
    throw runtime_error("Valor del limite de imagenes no válido");
  }

  if (!Validator::IsValidPositiveInt(offset))
  {
    throw runtime_error("Valor de la imagen inicial no válido");
  }

  list<LetterModel> letters = lettersRepository.GetSendedLettersBriefByOwnerId(userId, limit, offset);

  return letters;
}

int LettersService::GetUserReceivedLetterCount(int userId)
{
  if (!Validator::IsValidUserId(userId))
  {
    throw runtime_error("Formato de identificardor de usuario no válido.");
  }
  
  int totalReceivedLettersCount = lettersRepository.GetReceivedLettersCountByReceiverId(userId);

  return totalReceivedLettersCount;
}

std::list<LetterModel> LettersService::GetUserReceivedLettersInRange(int userId, int limit, int offset)
{
  if (!Validator::IsValidUserId(userId))
  {
    throw runtime_error("Formato de identificardor de usuario no válido.");
  }

  if (!Validator::IsValidPositiveInt(limit))
  {
    throw runtime_error("Valor del limite de imagenes no válido");
  }

  if (!Validator::IsValidPositiveInt(offset))
  {
    throw runtime_error("Valor de la imagen inicial no válido");
  }

  list<LetterModel> letters = lettersRepository.GetReceivedLettersBriefByReceiverId(userId, limit, offset);

  return letters;
}

LetterModel LettersService::GetLetterDetails(int userId, string& letterId)
{
  if (!Validator::IsValidUserId(userId))
  {
    throw runtime_error("Formato de identificardor de usuario no válido.");
  }

  if (!Validator::IsValidLetterId(letterId))
  {
    throw runtime_error("Formato del identificador de la carta no válido.");
  }

  int letterIdInt = std::stoi(letterId);

  LetterModel letter = lettersRepository.GetLetterFromUserByLetterId(userId, letterIdInt);

  return letter;
}
