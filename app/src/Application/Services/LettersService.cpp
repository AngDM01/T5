#include "LettersService.hpp"

#include <list>
#include <stdexcept>

#include "EmailMessage.hpp"
#include "EmailService.hpp"
#include "EmailValidator.hpp"
#include "FakeEmailSender.hpp"
#include "LetterModel.hpp"
#include "LettersRepository.hpp"
#include "SendedLetterTemplate.hpp"
#include "SendLetterDTO.hpp"
#include "UserModel.hpp"
#include "Validator.hpp"

#include "Logger.hpp"

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

bool LettersService::IsMarkedOpened(std::string &letterId)
{
  if (!Validator::IsValidLetterId(letterId))
  {
    throw runtime_error("Formato del identificador de la carta no válido.");
  }

  int letterIdInt = std::stoi(letterId);

  bool isOpened = lettersRepository.GetOpenedStatus(letterIdInt);

  return isOpened;
}

bool LettersService::MarkedLetterAsOpened(int userId, std::string &letterId)
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

  bool markedOpened = lettersRepository.ChangeLetterOpenedStatus(userId, letterIdInt, true);

  return markedOpened;
}

bool LettersService::SaveSendedLetter(SendLetterDTO& letterDTO, UserModel& userData, int receivedUser)
{
  LetterModel letter;

  if (!Validator::IsValidName(letterDTO.GetTitle()))
  {
    throw runtime_error("Formato de titulo de la carta no válido.");
  }
  
  letter.SetLetterTitle(letterDTO.GetTitle());

  if (!Validator::IsValidName(letterDTO.GetFrom()))
  {
    throw runtime_error("Formato del nombre del remitente de la carta no válido.");
  }
  
  letter.SetSenderName(letterDTO.GetFrom());

  if (!Validator::IsValidEmail(userData.GetEmail()))
  {
    throw runtime_error("Formato del correo del remitente de la carta no válido.");
  }
  
  letter.SetSenderEmail(userData.GetEmail());

  if (!Validator::IsValidName(letterDTO.GetTo()))
  {
    throw runtime_error("Formato del nombre del receptor de la no válido.");
  }
  
  letter.SetReceiverName(letterDTO.GetTo());

  if (!Validator::IsValidEmail(letterDTO.GetToEmail()))
  {
    throw runtime_error("Formato del correo del receptor de la carta no válido.");
  }
  
  letter.SetReceiverEmail(letterDTO.GetToEmail());

  if (!Validator::IsValidTextLetter(letterDTO.GetText()))
  {
    throw runtime_error("Formato del texto de la carta no válido. Maximo 2000 caracteres");
  }
  
  letter.SetTextLetter(letterDTO.GetText());

  if (!Validator::IsValidImageId(letterDTO.GetImageId()))
  { 
    throw runtime_error("Formato del texto de la carta no válido. Maximo 2000 caracteres");
  }
  
  letter.SetIdAssociateImage(stoi(letterDTO.GetImageId()));

  if (!Validator::IsValidUserId(userData.GetIdUser()))
  {
    throw runtime_error("Formato del texto de la carta no válido. Maximo 2000 caracteres");
  }

  letter.SetIdOwnerUser(userData.GetIdUser());

  if (!Validator::IsValidUserId(receivedUser))
  {
    throw runtime_error("Formato del identificador del receptor de la carta no válido. ");
  }

  letter.SetIdReceiverUser(receivedUser);

  bool insertedLetter = lettersRepository.InsertLetter(letter);
  
  if (insertedLetter) sendEmail(letter);

  return insertedLetter;
}

void LettersService::sendEmail(LetterModel &letter)
{
  FakeEmailSender sender;
  EmailValidator validator;

  SendedLetterTemplate sendeLetter(letter.GetSenderName(), letter.GetSenderEmail(), letter.GetReceiverName(), letter.GetLetterTitle());

  EmailService emailService(sender, validator);
  
  EmailMessage email(letter.GetSenderName(), letter.GetSenderEmail(), letter.GetReceiverName(), letter.GetReceiverEmail(),
      "Nueva carta recibida", sendeLetter.Build());
 
  emailService.SendEmail(email);
}
