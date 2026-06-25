#include "Statement.hpp"

#include <mariadb/mysql.h>
#include <stdexcept>
#include <string>
#include <vector>

#include "Logger.hpp"

using namespace std;

Statement::Statement(MYSQL* connection, const string& query)
{
  stmt = mysql_stmt_init(connection);

  if (stmt == nullptr)
  {
    Logger::Error("[Statment::Statement]\n Unable to create statement.");

    throw runtime_error("Unable to create statement.");
  }

  if (mysql_stmt_prepare(stmt, query.c_str(), query.length()))
  {
    Logger::Error(string("[Statment::Statement]\n") + mysql_stmt_error(stmt));

    throw runtime_error("Error creando statement");
  }
}

Statement::~Statement()
{
  if (stmt) mysql_stmt_close(stmt);
}

void Statement::BindString(const string& value)
{
  stringStorage.push_back(value);

  MYSQL_BIND bind{};
  bind.buffer_type = MYSQL_TYPE_STRING;
  bind.buffer = (void*)stringStorage.back().c_str();
  bind.buffer_length = stringStorage.back().length();

  params.push_back(bind);
}

void Statement::BindInt(int value)
{
  intStorage.push_back(value);

  MYSQL_BIND bind{};
  bind.buffer_type = MYSQL_TYPE_LONG;
  bind.buffer = &intStorage.back();
  
  params.push_back(bind);
}

void Statement::BindUInt8(uint8_t value)
{
  uint8Storage.push_back(value);

  MYSQL_BIND bind{};

  bind.buffer_type = MYSQL_TYPE_TINY;
  bind.is_unsigned = true;
  bind.buffer = &uint8Storage.back();

  params.push_back(bind);
}

void Statement::BindBlob(const char *data, unsigned long length)
{
  MYSQL_BIND bind{};

  bind.buffer_type = MYSQL_TYPE_BLOB;
  bind.buffer = (void*)data;
  bind.buffer_length = length;

  params.push_back(bind);
}

void Statement::BindResultInt(int& value)
{
  MYSQL_BIND bind{};

  bind.buffer_type = MYSQL_TYPE_LONG;
  bind.buffer = &value;

  results.push_back(bind);
}

void Statement::BindResultString(char* buffer, unsigned long length)
{
  MYSQL_BIND bind{};

  bind.buffer_type = MYSQL_TYPE_STRING;
  bind.buffer = buffer;
  bind.buffer_length = length;

  results.push_back(bind);
}

void Statement::BindResultBlob(void* buffer, unsigned long length, unsigned long& actualLength)
{
  MYSQL_BIND bind{};

  bind.buffer_type = MYSQL_TYPE_BLOB;
  bind.buffer = buffer;
  bind.buffer_length = length;
  bind.length = &actualLength;
  bind.is_null = 0;

  results.push_back(bind);
}

void Statement::BindResultUInt8(uint8_t& value)
{
  MYSQL_BIND bind{};

  bind.buffer_type = MYSQL_TYPE_TINY;
  bind.is_unsigned = true;
  bind.buffer = &value;

  results.push_back(bind);
}

void Statement::Execute()
{
  if (!params.empty())
  {
    if (mysql_stmt_bind_param(stmt, params.data()))
    {
      Logger::Error(string("[Statment::Execute]\n") + mysql_stmt_error(stmt));

      throw runtime_error("Error bind parámetros");
    }
  }

  if (!results.empty())
  {
    if (mysql_stmt_bind_result(stmt, results.data()))
    {
      Logger::Error(string("[Statment::execute]\n") + mysql_stmt_error(stmt));

      throw runtime_error("Error bind resultados");
    }
  }

  if (mysql_stmt_execute(stmt))
  {
    Logger::Error(string("[Statment::execute]\n") + mysql_stmt_error(stmt));

    throw runtime_error("Error ejecutanto el query");
  }
}

bool Statement::Fetch()
{
  int status = mysql_stmt_fetch(stmt);

  if (status == 0) return true;

  if (status == MYSQL_NO_DATA) return false;

  Logger::Error(string("[Statment::Fetch]\n") + mysql_stmt_error(stmt));

  throw runtime_error("Error fecth el status");
}

void Statement::Reset()
{
  params.clear();
  results.clear();
  stringStorage.clear();
  intStorage.clear();
  uint8Storage.clear();
}
