#include "LetterModel.hpp"

#include <string>

using namespace std;

LetterModel::LetterModel(int idLetter, const string &letterTitle, const string &senderName, const string &senderEmail,
    const string &receiverName, const string &receiverEmail, const string &textLetter, const string &sendDate, bool opened,
    int idAssociateImage, int idOwnerUser, int idReceiverUser)
  : idLetter(idLetter),
  letterTitle(letterTitle),
  senderName(senderName),
  senderEmail(senderEmail),
  receiverName(receiverName),
  receiverEmail(receiverEmail),
  textLetter(textLetter),
  sendDate(sendDate),
  opened(opened),
  idAssociateImage(idAssociateImage),
  idOwnerUser(idOwnerUser),
  idReceiverUser(idReceiverUser)
{
}

int LetterModel::GetIdLetter() const
{
  return idLetter;
}

const string& LetterModel::GetLetterTitle() const
{
  return letterTitle;
}

const string& LetterModel::GetSenderName() const
{
  return senderName;
}

const string& LetterModel::GetSenderEmail() const
{
  return senderEmail;
}

const string& LetterModel::GetReceiverName() const
{
  return receiverName;
}

const string& LetterModel::GetReceiverEmail() const
{
  return receiverEmail;
}

const string& LetterModel::GetTextLetter() const
{
  return textLetter;
}

const string& LetterModel::GetSendDate() const
{
  return sendDate;
}

bool LetterModel::GetOpenedStatus() const
{
  return opened;
}

int LetterModel::GetIdAssociateImage() const
{
  return idAssociateImage;
}

int LetterModel::GetIdOwnerUser() const
{
  return idOwnerUser;
}

int LetterModel::GetIdReceiverUser() const
{
  return idReceiverUser;
}

const ImagesModel& LetterModel::GetImage() const
{
  return image;
}

// Setters
void LetterModel::SetIdLetter(int idLetter)
{
  this->idLetter = idLetter;
}

void LetterModel::SetLetterTitle(const string& letterTitle)
{
   this->letterTitle = letterTitle;
}

void LetterModel::SetSenderName(const string& senderName)
{
   this->senderName = senderName;
}

void LetterModel::SetSenderEmail(const string& senderEmail)
{
   this->senderEmail = senderEmail;
}

void LetterModel::SetReceiverName(const string& receiverName)
{
  this->receiverName = receiverName;
}

void LetterModel::SetReceiverEmail(const string& receiverEmail)
{
  this->receiverEmail = receiverEmail;
}

void LetterModel::SetTextLetter(const string& textLetter)
{
  this->textLetter = textLetter;
}

void LetterModel::SetSendDate(const string& sendDate)
{
  this->sendDate = sendDate;
}

void LetterModel::SetOpenedStatus(bool opened)
{
  this->opened = opened;
}

void LetterModel::SetIdAssociateImage(int idAssociateImage)
{
  this->idAssociateImage = idAssociateImage;
}

void LetterModel::SetIdOwnerUser(int idOwnerUser)
{
  this->idOwnerUser = idOwnerUser;
}

void LetterModel::SetIdReceiverUser(int idReceiverUser)
{
  this->idReceiverUser = idReceiverUser;
}

void LetterModel::SetImage(ImagesModel &image)
{
  this->image = image;
}
