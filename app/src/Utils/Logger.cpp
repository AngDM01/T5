#include "Logger.hpp"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <filesystem>

using namespace std;

namespace
{
  string CurrentDateTime()
  {
    auto now = chrono::system_clock::now();
    time_t t = chrono::system_clock::to_time_t(now);

    tm tm = *localtime(&t);

    ostringstream oss;
    oss << put_time(&tm, "%Y-%m-%d %H:%M:%S");

    return oss.str();
  }

  filesystem::path GetLogFilePath(const string& fileName)
  {
    filesystem::path logsDir("/usr/local/apache2/app/logs");
    error_code ec;

    if (!filesystem::exists(logsDir, ec))
      filesystem::create_directories(logsDir, ec);

    return logsDir / fileName;
  }
}

void Logger::Error(const string& message)
{
  auto path = GetLogFilePath("error.log");
  ofstream file(path, ios::app);

  if (!file)
  {
    cerr << "[" << CurrentDateTime() << "] [ERROR] Unable to open log file: " << path << "\n"
        << message << "\n";
    return;
  }

  file << "[" << CurrentDateTime() << "] "
      << "[ERROR] "
      << message << endl;
}

void Logger::Info(const string& message)
{
  auto path = GetLogFilePath("info.log");
  ofstream file(path, ios::app);

  if (!file)
  {
    cerr << "[" << CurrentDateTime() << "] [ERROR] Unable to open log file: " << path << "\n"
        << message << "\n";
    return;
  }

  file << "[" << CurrentDateTime() << "] "
       << "[INFORMATION] "
       << message << endl;
}

void Logger::Warning(const string& message)
{
  auto path = GetLogFilePath("warning.log");
  ofstream file(path, ios::app);

  if (!file)
  {
    cerr << "[" << CurrentDateTime() << "] [ERROR] Unable to open log file: " << path << "\n"
        << message << "\n";
    return;
  }

  file << "[" << CurrentDateTime() << "] "
      << "[WARNING] "
      << message << endl;
}

void Logger::Debug(const std::string &message)
{
  auto path = GetLogFilePath("debug.log");
  ofstream file(path, ios::app);

  if (!file)
  {
    cerr << "[" << CurrentDateTime() << "] [ERROR] Unable to open log file: " << path << "\n"
        << message << "\n";
    return;
  }

  file << "[" << CurrentDateTime() << "] "
      << "[DEBUG] "
      << message << endl;
}
