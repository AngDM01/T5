#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <sstream>
#include <vector>

struct UploadedFile
{
  std::string fieldName;
  std::string fileName;
  std::string contentType;
  std::vector<uint8_t> data;
};

class Request
{
 public:
  Request();
  ~Request() = default;

  std::string GetMethod();
  std::string GetContentType();
  size_t GetContentLength();
  std::string GetQueryParam(const std::string& key);
  std::string GetBodyParam(const std::string& key);
  std::string GetCookie(const std::string& key);
  UploadedFile GetFile(const std::string& key);

 private:
  void MapParam(std::map<std::string, std::string>& map, const std::string& data);
  void MapQueryParams();
  void MapUrlEncodedBody();
  void MapMultipartBody();
  void ParsePart(const std::string& part);
  void MapCookies();

 private:
  std::string method;
  std::string contentType;
  size_t contentLength;

  std::map<std::string, std::string> queryParams;
  std::map<std::string, std::string> bodyParams;
  std::map<std::string, std::string> cookies;
  std::map<std::string, UploadedFile> uploadedFiles;
};
