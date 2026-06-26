#pragma once

#include <string>

#include "ImagesModel.hpp"

class LetterModel
{
public:
  LetterModel(int idLetter = 0, const std::string& letterTitle = "", const std::string& senderName = "",
        const std::string& senderEmail = "", const std::string& receiverName = "", const std::string& receiverEmail = "",
        const std::string& textLetter = "", const std::string& sendDate = "", int idAssociateImage = 0, int idOwnerUser = 0, int idReceiverUser = 0);
  ~LetterModel() = default;

  // Getters
    int GetIdLetter() const;
    const std::string& GetLetterTitle() const;
    const std::string& GetSenderName() const;
    const std::string& GetSenderEmail() const;
    const std::string& GetReceiverName() const;
    const std::string& GetReceiverEmail() const;
    const std::string& GetTextLetter() const;
    const std::string& GetSendDate() const;
    int GetIdAssociateImage() const;
    int GetIdOwnerUser() const;
    int GetIdReceiverUser() const;
    const ImagesModel& GetImage() const;

    // Setters
    void SetIdLetter(int value);
    void SetLetterTitle(const std::string& value);
    void SetSenderName(const std::string& value);
    void SetSenderEmail(const std::string& value);
    void SetReceiverName(const std::string& value);
    void SetReceiverEmail(const std::string& value);
    void SetTextLetter(const std::string& value);
    void SetSendDate(const std::string& value);
    void SetIdAssociateImage(int value);
    void SetIdOwnerUser(int value);
    void SetIdReceiverUser(int value);
    void SetImage(ImagesModel& image);

 private:
  int idLetter;
  std::string letterTitle;
  std::string senderName;
  std::string senderEmail;
  std::string receiverName;
  std::string receiverEmail;
  std::string textLetter;
  std::string sendDate;
  int idAssociateImage;
  int idOwnerUser;
  int idReceiverUser;

  ImagesModel image;
};
