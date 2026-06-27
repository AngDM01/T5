#pragma once

#include <cstdint>
#include <deque>
#include <mariadb/mysql.h>
#include <string>
#include <vector>

class Statement
{
public:
  Statement(MYSQL* connection, const std::string& query);
  ~Statement();

  void BindString(const std::string& value);
  void BindInt(int value);
  void BindUInt8(uint8_t value);
  void BindBlob(const char* data, unsigned long length);
  void BindResultString(char* buffer, unsigned long length);
  void BindResultBlob(void* buffer, unsigned long length, unsigned long& actualLength);
  void BindResultInt(int& value);
  void BindResultUInt8(uint8_t& value);
  void Execute();
  bool Fetch();
  void Reset();
  int GetAffectedRows(MYSQL* connection);

private:
  MYSQL_STMT* stmt;
  std::vector<MYSQL_BIND> params;
  std::vector<MYSQL_BIND> results;
  std::deque<std::string> stringStorage;
  std::deque<int> intStorage;
  std::deque<uint8_t>uint8Storage;
};
