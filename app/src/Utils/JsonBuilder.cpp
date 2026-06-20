#include "JsonBuilder.hpp"

#include <sstream>
#include <cstdio>

using namespace std;

JsonBuilder::JsonBuilder() {}

string JsonBuilder::escape(const string& s)
{
  string result;
  result.reserve(s.size());

  for (unsigned char c : s)
  {
    switch (c)
    {
      case '"': result += "\\\""; break;
      case '\\': result += "\\\\"; break;
      case '\b': result += "\\b"; break;
      case '\f': result += "\\f"; break;
      case '\n': result += "\\n"; break;
      case '\r': result += "\\r"; break;
      case '\t': result += "\\t"; break;
      default:
        if (c < 0x20)
        {
          char buf[7];
          snprintf(buf, sizeof(buf), "\\u%04x", c);
          result += buf;
        }
        else
        {
          result += static_cast<char>(c);
        }
        break;
    }
  }

  return result;
}

JsonBuilder& JsonBuilder::addString(const string& key, const string& value)
{
  parts.push_back("\"" + escape(key) + "\": \"" + escape(value) + "\"");
  return *this;
}

JsonBuilder& JsonBuilder::addBool(const string& key, bool value)
{
  parts.push_back("\"" + escape(key) + "\": " + (value ? "true" : "false"));
  return *this;
}

JsonBuilder& JsonBuilder::addInt(const string& key, int value)
{
  parts.push_back("\"" + escape(key) + "\": " + to_string(value));
  return *this;
}

string JsonBuilder::toString() const
{
  string out = "{";
  for (size_t i = 0; i < parts.size(); ++i)
  {
    out += parts[i];
    if (i + 1 < parts.size()) out += ", ";
  }
  out += "}";
  return out;
}
