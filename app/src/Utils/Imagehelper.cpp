#include "Imagehelper.hpp"

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <cstdint>

std::string Imagehelper::Encode(const std::vector<uint8_t> &data)
{
  BIO* bio = BIO_new(BIO_s_mem());
  BIO* b64 = BIO_new(BIO_f_base64());

  // No newlines
  BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);

  bio = BIO_push(b64, bio);

  BIO_write(bio, data.data(), data.size());
  BIO_flush(bio);

  BUF_MEM* bufferPtr;
  BIO_get_mem_ptr(bio, &bufferPtr);

  std::string result(bufferPtr->data, bufferPtr->length);

  BIO_free_all(bio);

  return result;
}

std::string Imagehelper::ImageExtensionMIME(const std::string& extension)
{
  std::string mime = "image/jpeg";

  if (extension == "png")
    mime = "image/png";
  else if (extension == "jpg" || extension == "jpeg")
    mime = "image/jpeg";

  return mime;
}

std::string Imagehelper::ExtensionFromMIME(const std::string &mime)
{
  if (mime == "image/jpeg") return "jpeg";
  else if (mime == "image/jpg") return "jpg";
  else if (mime == "image/png") return "png";
  else
    return "";
}
