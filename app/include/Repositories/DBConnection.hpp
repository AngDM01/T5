#pragma once

#include <mariadb/mysql.h>
#include <string>
#include <stdexcept>
#include <exception>

class DBConnection
{
 public:
  DBConnection()
  {
    connection = mysql_init(nullptr);
    if (!connection)
    {
      throw std::runtime_error("mysql_init fallo");
    }
  }

  ~DBConnection()
  {
    Close();
  }

  void Connect(const std::string &host, const std::string &user, const std::string &pass,
      const std::string &db, int port = 3306)
  {
    if (!mysql_real_connect(connection, host.c_str(), user.c_str(), pass.c_str(), db.c_str(), port, nullptr, 0))
    {
      throw std::runtime_error(mysql_error(connection));
    }
  }

  MYSQL* GetConnection()
  {
    return connection;
  }

  void Close()
  {
    if (connection)
    {
      mysql_close(connection);
      connection = nullptr;
    }
  }

 private:
  MYSQL *connection;
};
