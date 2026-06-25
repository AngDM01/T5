#pragma once

#include <string>

class LettersRepository;

class LettersService
{
 public:
  LettersService(LettersRepository& lettersRepository);
  ~LettersService() = default;

 private:
  LettersRepository& lettersRepository;
};
