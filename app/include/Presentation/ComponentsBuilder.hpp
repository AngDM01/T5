#pragma once

#include <list>
#include <string>

class ImagesModel;
class LetterModel;

class ComponentsBuilder
{
 public:
  ComponentsBuilder() = default;
  ~ComponentsBuilder() = default;

  std::string BuildImageCarrouselType2(std::list<ImagesModel>& images, std::string containerId, int imagesCount, int limit, int offset);
  std::string BuildImageCarrouselType1(std::list<ImagesModel>& images, std::string containerId, int imagesCount,
      int limit, int offset, bool isCatalog = false);
	std::string BuildSendedLetterTable(std::list<LetterModel>& sendedLetters, int sendedLetterCount, int limit, int offset);
	std::string BuildReceivedLetterTable(std::list<LetterModel>& receivedLetters, int receivedLetterCount, int limit, int offset);
  std::string BuildImageSource(const ImagesModel& image);
};
