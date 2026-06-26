#include "LettersRepository.hpp"

#include <list>
#include <string>

#include "DBConnection.hpp"
#include "LetterModel.hpp"
#include "Logger.hpp"
#include "Statement.hpp"

using namespace std;

LettersRepository::LettersRepository(DBConnection &connection)
  : db(connection)
{
}

int LettersRepository::GetSendedLettersCountByOwnerId(int ownerId)
{
  try
  {
    Statement stmt(db.GetConnection(), getSendedLettersCountByOwnerIdQuery);

    stmt.BindInt(ownerId);

    int totalSendedLetters = 0;

    stmt.BindResultInt(totalSendedLetters);

    stmt.Execute();
    
    if (!stmt.Fetch()) return 0;
    
    stmt.Reset();

    return totalSendedLetters;
  }
  catch(const std::exception& e)
  {
    Logger::Error(string("[LettersRepository::GetSendedLettersCountByOwnerId]\n") + e.what());
    return -1;
  }
}

list<LetterModel> LettersRepository::GetSendedLettersBriefByOwnerId(int ownerId, int limit, int offset)
{
  try
  {
    Statement stmt(db.GetConnection(), sendedLettersbriefByOwnerIdQuery);

    stmt.BindInt(ownerId);
    stmt.BindInt(limit);
    stmt.BindInt(offset);

    int letterId = 0;
    char letterTitle[101]{};
    char receiverName[101]{};
    char receiverEmail[256]{};
    char sendedDate[64]{};

    stmt.BindResultInt(letterId);
    stmt.BindResultString(letterTitle, sizeof(letterTitle));
    stmt.BindResultString(receiverName, sizeof(receiverName));
    stmt.BindResultString(receiverEmail, sizeof(receiverEmail));
    stmt.BindResultString(sendedDate, sizeof(sendedDate));

    stmt.Execute();

    list<LetterModel> sendedLetters;

    while (stmt.Fetch())
    {
      sendedLetters.emplace_back(letterId, letterTitle, "", "", receiverName, receiverEmail, "", sendedDate);
    }

    stmt.Reset();

    return sendedLetters;
  }
  catch(const std::exception& e)
  {
    Logger::Error(string("[LettersRepository::GetSendedLettersBriefByOwnerId]\n") + e.what());
    return list<LetterModel>{ LetterModel(-1) };
  }
}

int LettersRepository::GetReceivedLettersCountByReceiverId(int receiverId)
{
  try
  {
    Statement stmt(db.GetConnection(), getReceivedLettersCountByReceiverIdQuery);

    stmt.BindInt(receiverId);

    int totalReceivedLetters = 0;

    stmt.BindResultInt(totalReceivedLetters);

    stmt.Execute();
    
    if (!stmt.Fetch()) return 0;
    
    stmt.Reset();

    return totalReceivedLetters;
  }
  catch(const std::exception& e)
  {
    Logger::Error(string("[LettersRepository::GetSendedLettersCountByOwnerId]\n") + e.what());
    return -1;
  }
}

list<LetterModel> LettersRepository::GetReceivedLettersBriefByReceiverId(int receiverId, int limit, int offset)
{
  try
  {
    Statement stmt(db.GetConnection(), receivedLettersbriefByReceiverIdQuery);

    stmt.BindInt(receiverId);
    stmt.BindInt(limit);
    stmt.BindInt(offset);

    int letterId = 0;
    char letterTitle[101]{};
    char senderName[101]{};
    char senderEmail[256]{};
    char sendedDate[64]{};

    stmt.BindResultInt(letterId);
    stmt.BindResultString(letterTitle, sizeof(letterTitle));
    stmt.BindResultString(senderName, sizeof(senderName));
    stmt.BindResultString(senderEmail, sizeof(senderEmail));
    stmt.BindResultString(sendedDate, sizeof(sendedDate));

    stmt.Execute();

    list<LetterModel> sendedLetters;

    while (stmt.Fetch())
    {
      sendedLetters.emplace_back(letterId, letterTitle, senderName, senderEmail, "", "", "", sendedDate);
    }

    stmt.Reset();

    return sendedLetters;
  }
  catch(const std::exception& e)
  {
    Logger::Error(string("[LettersRepository::GetSendedLettersBriefByOwnerId]\n") + e.what());
    return list<LetterModel>{ LetterModel(-1) };
  }
}

LetterModel LettersRepository::GetLetterFromUserByLetterId(int userId, int letterIdInt)
{
  try
  {
    Statement stmt(db.GetConnection(), getLetterFromUserByLetterIdQuery);

    stmt.BindInt(letterIdInt);
    stmt.BindInt(userId);
    stmt.BindInt(userId);

    int letterId = 0;
    char letterTitle[101]{};
    char senderName[101]{};
    char senderEmail[256]{};
    char receiverName[101]{};
    char receiverEmail[256]{};
    char textLetter[2001]{};
    char sendDate[64]{};
    int idAssociateImage = 0;
    int idOwnerUser = 0;
    int idReceiverUser = 0;

    stmt.BindResultInt(letterId);
    stmt.BindResultString(letterTitle, sizeof(letterTitle));
    stmt.BindResultString(senderName, sizeof(senderName));
    stmt.BindResultString(senderEmail, sizeof(senderEmail));
    stmt.BindResultString(receiverName, sizeof(receiverName));
    stmt.BindResultString(receiverEmail, sizeof(receiverEmail));
    stmt.BindResultString(textLetter, sizeof(textLetter));
    stmt.BindResultString(sendDate, sizeof(sendDate));
    stmt.BindResultInt(idAssociateImage);
    stmt.BindResultInt(idOwnerUser);
    stmt.BindResultInt(idReceiverUser);

    stmt.Execute();

    if (!stmt.Fetch()) return LetterModel();

    stmt.Reset();

    return LetterModel(letterId, letterTitle, senderName, senderEmail, receiverName, receiverEmail,
        textLetter, sendDate, idAssociateImage, idOwnerUser, idReceiverUser);
  }
  catch(const std::exception& e)
  {
    Logger::Error(string("[LettersRepository::GetLetterFromUserByLetterId]\n") + e.what());
    return LetterModel(-1);
  }
}
