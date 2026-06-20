#include "Request.hpp"

#include <iostream>
#include <map>
#include <string>
#include <sstream>

using namespace std;

Request::Request()
{
  method = getenv("REQUEST_METHOD") ? getenv("REQUEST_METHOD") : "";
  contentType = getenv("CONTENT_TYPE") ? getenv("CONTENT_TYPE") : "";

  const char* length = getenv("CONTENT_LENGTH");
  contentLength = length ? stoul(length) : 0;

  MapQueryParams();

  if (method == "POST")
  {
    if (contentType.find("application/x-www-form-urlencoded") != string::npos)
      MapUrlEncodedBody();
    else if (contentType.find("multipart/form-data") != string::npos)
      MapMultipartBody();
  }

  MapCookies();
}

void Request::MapQueryParams()
{
  const char* query = getenv("QUERY_STRING");

  string queryStr = query ? query : "";

  MapParam(queryParams, queryStr);
}

void Request::MapUrlEncodedBody()
{
  string body(contentLength, '\0');
  cin.read(&body[0], contentLength);

  MapParam(bodyParams, body);
}

void Request::MapMultipartBody()
{
  string body(contentLength, '\0');
  cin.read(body.data(), contentLength);

  size_t pos = contentType.find("boundary=");
  
  if (pos == string::npos)  return;

  string boundary = "--" + contentType.substr(pos + 9);

  size_t start = 0;

  while (true)
  {
    size_t partBegin = body.find(boundary, start);

    if (partBegin == string::npos) break;

    partBegin += boundary.length();

    if (body.compare(partBegin, 2, "--") == 0) break;

    if (body.compare(partBegin, 2, "\r\n") == 0) partBegin += 2;

    size_t partEnd = body.find(boundary, partBegin);

    if (partEnd == string::npos) break;

    ParsePart(body.substr(partBegin, partEnd - partBegin));

    start = partEnd;
  }
}

void Request::ParsePart(const string& part)
{
    size_t headerEnd = part.find("\r\n\r\n");

    if (headerEnd == string::npos)
        return;

    string headers = part.substr(0, headerEnd);
    string content = part.substr(headerEnd + 4);

    size_t pos = headers.find("name=\"");

    if (pos == string::npos)
        return;

    pos += 6;

    size_t end = headers.find("\"", pos);

    string fieldName = headers.substr(pos, end - pos);

    bool isFile = headers.find("filename=\"") != string::npos;

    if (!isFile)
    {
      while (!content.empty() && (content.back() == '\r' || content.back() == '\n'))
      {
        content.pop_back();
      }

      bodyParams[fieldName] = content;
    }
    else
    {
      UploadedFile file;

      file.fieldName = fieldName;

      size_t pos = headers.find("filename=\"");

      if (pos != string::npos)
      {
        pos += 10;

        size_t end = headers.find("\"", pos);

        file.fileName = headers.substr(pos, end - pos);
      }

      pos = headers.find("Content-Type:");

      if (pos != string::npos)
      {
        pos += 13;

        while (pos < headers.size() && headers[pos] == ' ') pos++;

        size_t end = headers.find("\r\n", pos);

        file.contentType = headers.substr(pos, end - pos);
      }

      file.data.assign(content.begin(), content.end());

      uploadedFiles[fieldName] = std::move(file);
    }
}

void Request::MapCookies()
{
  const char* cookie = getenv("HTTP_COOKIE");

  string cookieStr = cookie ? cookie : "";

  stringstream ss(cookieStr);
  string pair;

  while (getline(ss, pair, ';'))
  {
    if (!pair.empty() && pair[0] == ' ') pair.erase(0, 1);

    size_t pos = pair.find('=');

    if (pos == string::npos) continue;

    cookies[pair.substr(0, pos)] = pair.substr(pos + 1);
  }
}

void Request::MapParam(map<string, string>& map, const string& data)
{
  stringstream ss(data);
  string pair;

  while (getline(ss, pair, '&')) {
    size_t pos = pair.find('=');

    if (pos == string::npos) continue;

    map[pair.substr(0, pos)] = pair.substr(pos + 1);
  }
}

string Request::GetQueryParam(const string& key)
{
  if (queryParams.find(key) == queryParams.end()) return "";

  return queryParams[key];
}

string Request::GetBodyParam(const string& key)
{
  if (bodyParams.find(key) == bodyParams.end()) return "";

  return bodyParams[key];
}

string Request::GetCookie(const string& key)
{
  if (cookies.find(key) == cookies.end()) return "";

  return cookies[key];
}

UploadedFile Request::GetFile(const string& key)
{
  if (uploadedFiles.find(key) == uploadedFiles.end()) return UploadedFile{};

  return uploadedFiles[key];
}

string Request::GetMethod()
{
  return method;
}

string Request::GetContentType()
{
  return contentType;
}

size_t Request::GetContentLength()
{
  return contentLength;
}
