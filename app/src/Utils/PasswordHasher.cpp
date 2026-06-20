#include "PasswordHasher.hpp"

#include <openssl/sha.h>
#include <sstream>
#include <iomanip>

using namespace std;

std::string PasswordHasher::hashPassword(const std::string& password)
{
  unsigned char hash[SHA256_DIGEST_LENGTH];
  
  SHA256(reinterpret_cast<unsigned char*>(const_cast<char*>(password.c_str())), 
      password.length(), hash);
  
  stringstream ss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
  {
    ss << hex << setw(2) << setfill('0') << static_cast<int>(hash[i]);
  }
  
  return ss.str();
}
