#pragma once

#include <cstdint>
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
  void BindResultString(char* buffer, unsigned long length);
  void BindResultInt(int& value);
  void BindResultUInt8(uint8_t& value);
  void Execute();
  bool Fetch();

private:
  MYSQL_STMT* stmt;
  std::vector<MYSQL_BIND> params;
  std::vector<MYSQL_BIND> results;
  std::vector<std::string> stringStorage;
  std::vector<int> intStorage;
  std::vector<uint8_t>uint8Storage;
};