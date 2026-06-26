#include "ImagesRepository.hpp"

#include <vector>

#include "DBConnection.hpp"
#include "ImageDTO.hpp"
#include "ImagesModel.hpp"
#include "Logger.hpp"
#include "Statement.hpp"

using namespace std;

ImagesRepository::ImagesRepository(DBConnection& connection)
  : db(connection)
{
}

int ImagesRepository::GetImagesAsociateToUserCount(int uploaderId)
{
  try
  {
    Statement stmt(db.GetConnection(), getImagesAsociateToUserCountQuery);

    stmt.BindInt(uploaderId);

    int totalImages = 0;

    stmt.BindResultInt(totalImages);

    stmt.Execute();
    
    if (!stmt.Fetch()) return 0;
    
    stmt.Reset();

    return totalImages;
  }
  catch(const std::exception& e)
  {
    Logger::Error(string("[ImagesRepository::GetImagesAsociateToUserCount]\n") + e.what());
    return -1;
  }
}

list<ImagesModel> ImagesRepository::GetImagesInRangeByUploaderId(int uploaderId, int limit, int start)
{
  try
  {
    Statement stmt(db.GetConnection(), getImagesQuery);
    
    stmt.BindInt(uploaderId);
    stmt.BindInt(limit);
    stmt.BindInt(start);
    
    int idImage = 0;
    char alias[256]{};
    char extension[16]{};
    vector<uint8_t> imageBuffer(16 * 1024 * 1024);
    unsigned long imageLength = 0;
    uint8_t isCatalog = 0;
    char uploadDate[64]{};
    int idUploaderUser = 0;

    stmt.BindResultInt(idImage);
    stmt.BindResultString(alias, sizeof(alias));
    stmt.BindResultString(extension, sizeof(extension));
    stmt.BindResultBlob(reinterpret_cast<char*>(imageBuffer.data()), imageBuffer.size(), imageLength);
    stmt.BindResultUInt8(isCatalog);
    stmt.BindResultString(uploadDate, sizeof(uploadDate));
    stmt.BindResultInt(idUploaderUser);
    
    stmt.Execute();
    
    list<ImagesModel> images;
    
    while (stmt.Fetch())
    {
      imageBuffer.resize(imageLength);
      
      vector<uint8_t> imageData(imageBuffer.begin(), imageBuffer.begin() + imageLength);
      
      images.emplace_back(idImage, alias, extension, imageData, isCatalog != 0, uploadDate, idUploaderUser);
    }
    
    stmt.Reset();
    
    return images;
  }
  catch (const exception& e)
  {
    Logger::Error(string("[ImagesRepository::GetImagesInRangeByUploaderId]\n") + e.what());
    return list<ImagesModel>{ ImagesModel(-1) };
  }
}

bool ImagesRepository::InsertImage(int userId, bool isCatalog, const ImageDTO& image)
{
  try
  {
    Statement stmt(db.GetConnection(), insertImageQuery);

    stmt.BindString(image.GetAlias());
    stmt.BindString(image.GetExtension());
    stmt.BindBlob((const char*)image.GetImageData().data.data(), image.GetImageData().data.size());
    stmt.BindUInt8(isCatalog ? 1 : 0);
    stmt.BindInt(userId);

    stmt.Execute();

    return true;
  }
  catch(const std::exception& e)
  {
    Logger::Error(string("[ImagesRepository::InsertImage]\n") + e.what());
    return false;
  }
}

bool ImagesRepository::DeleteImageFromUserByImageId(int uploaderId, int imageId)
{
  try
  {
    Statement stmt(db.GetConnection(), deleteImageFromUserByImageIdQuery);

    stmt.BindInt(imageId);
    stmt.BindInt(uploaderId);

    stmt.Execute();

    return true;
  }
  catch(const std::exception& e)
  {
    Logger::Error(string("[ImagesRepository::DeleteImageByImageId]\n") + e.what());
    return false;
  }
}

int ImagesRepository::GetIsCatalogTotalImagesCount()
{
  try
  {
    Statement stmt(db.GetConnection(), getIsCatalogImageCountQuery);

    int catalogImagesCount = 0;

    stmt.BindResultInt(catalogImagesCount);

    stmt.Execute();
    
    if (!stmt.Fetch()) return 0;
    
    stmt.Reset();

    return catalogImagesCount;
  }
  catch(const std::exception& e)
  {
    Logger::Error(string("[ImagesRepository::GetIsCatalogTotalImagesCount]\n") + e.what());
    return -1;
  }
}

std::list<ImagesModel> ImagesRepository::GetCatalogImagesInRange(int limit, int start)
{
  try
  {
    Statement stmt(db.GetConnection(), getCatalogImagesQuery);
    
    stmt.BindInt(limit);
    stmt.BindInt(start);
    
    int idImage = 0;
    char alias[256]{};
    char extension[16]{};
    vector<uint8_t> imageBuffer(16 * 1024 * 1024);
    unsigned long imageLength = 0;
    uint8_t isCatalog = 0;
    char uploadDate[64]{};
    int idUploaderUser = 0;

    stmt.BindResultInt(idImage);
    stmt.BindResultString(alias, sizeof(alias));
    stmt.BindResultString(extension, sizeof(extension));
    stmt.BindResultBlob(reinterpret_cast<char*>(imageBuffer.data()), imageBuffer.size(), imageLength);
    stmt.BindResultUInt8(isCatalog);
    stmt.BindResultString(uploadDate, sizeof(uploadDate));
    stmt.BindResultInt(idUploaderUser);
    
    stmt.Execute();
    
    list<ImagesModel> images;
    
    while (stmt.Fetch())
    {
      imageBuffer.resize(imageLength);
      
      vector<uint8_t> imageData(imageBuffer.begin(), imageBuffer.begin() + imageLength);
      
      images.emplace_back(idImage, alias, extension, imageData, isCatalog != 0, uploadDate, idUploaderUser);
    }
    
    stmt.Reset();
    
    return images;
  }
  catch (const exception& e)
  {
    Logger::Error(string("[ImagesRepository::GetCatalogImagesInRange]\n") + e.what());
    return list<ImagesModel>{ ImagesModel(-1) };
  }
}

ImagesModel ImagesRepository::GetImageDataByImageId(int imageId)
{
  try
  {
    Statement  stmt(db.GetConnection(), getImageByImageIdQuery);

    stmt.BindInt(imageId);

    int idImage = 0;
    char alias[256]{};
    char extension[16]{};
    vector<uint8_t> imageBuffer(16 * 1024 * 1024);
    unsigned long imageLength = 0;
    uint8_t isCatalog = 0;
    char uploadDate[64]{};
    int idUploaderUser = 0;

    stmt.BindResultInt(idImage);
    stmt.BindResultString(alias, sizeof(alias));
    stmt.BindResultString(extension, sizeof(extension));
    stmt.BindResultBlob(reinterpret_cast<char*>(imageBuffer.data()), imageBuffer.size(), imageLength);
    stmt.BindResultUInt8(isCatalog);
    stmt.BindResultString(uploadDate, sizeof(uploadDate));
    stmt.BindResultInt(idUploaderUser);

    stmt.Execute();

    if (!stmt.Fetch()) return ImagesModel();

    stmt.Reset();

    imageBuffer.resize(imageLength);
      
    vector<uint8_t> imageData(imageBuffer.begin(), imageBuffer.begin() + imageLength);

    return ImagesModel(idImage, alias, extension, imageData, isCatalog != 0, uploadDate, idUploaderUser);
  }
  catch(const std::exception& e)
  {
    Logger::Error(string("[ImagesRepository::GetImageDataByImageId]\n") + e.what());
    return ImagesModel(-1);
  }
  
}
