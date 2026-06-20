#include "EnvLoader.hpp"

#include <fstream>
#include <stdexcept>

std::map<std::string, std::string> EnvLoader::Load(const std::string &file)
{
  std::ifstream f(file);

  if (!f.is_open())
  {
    throw std::runtime_error("No se pudo abrir el archivo: " + file);
  }

  std::map<std::string, std::string> env;
  std::string line;

  while (std::getline(f, line))
  {
    if (line.empty()) continue;

    if (!line.empty() && line.back() == '\r') line.pop_back();

    if (line[0] == '#') continue;

    size_t pos = line.find('=');

    if (pos == std::string::npos) continue;

    std::string key = line.substr(0, pos);
    std::string value = line.substr(pos + 1);

    env[key] = value;
  }

  return env;
}