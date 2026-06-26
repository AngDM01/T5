#pragma once

#include <list>
#include <string>

class DBConnection;
class ImageDTO;
class ImagesModel;

class ImagesRepository
{
 public:
  ImagesRepository(DBConnection &connection);
  ~ImagesRepository() = default;

  int GetImagesAsociateToUserCount(int uploaderId);
  std::list<ImagesModel> GetImagesInRangeByUploaderId(int uploaderId, int limit, int start);
  bool InsertImage(int userId, bool isCatalog, const ImageDTO& image);
  bool DeleteImageFromUserByImageId(int uploaderId, int imageId);
  int GetIsCatalogTotalImagesCount();
  std::list<ImagesModel> GetCatalogImagesInRange(int limit, int start);

 private:
  DBConnection& db;

  const char* getImagesAsociateToUserCountQuery = "SELECT COUNT(*) AS TotalImages FROM Images WHERE Id_uploader_user = ?";
  const char* getImagesQuery =
      "SELECT Id_image, Alias, Extension, Image_data, Is_catalog, Upload_date, Id_uploader_user " \
      "FROM Images " \
      "WHERE Id_uploader_user = ? "
      "ORDER BY Id_image DESC " \
      "LIMIT ? OFFSET ?;";
  const char* insertImageQuery =
      "INSERT INTO Images (Alias, Extension, Image_Data, Is_catalog, Id_uploader_user) " \
      "VALUES (?, ?, ?, ?, ?)";
  const char* deleteImageFromUserByImageIdQuery = "DELETE FROM Images WHERE Id_image = ? AND Id_uploader_user = ?";
	const char* getIsCatalogImageCountQuery = "SELECT COUNT(*) AS CatalogTotalImages FROM Images WHERE Is_catalog = TRUE";
	const char* getCatalogImagesQuery = "SELECT Id_image, Alias, Extension, Image_data, Is_catalog, Upload_date, Id_uploader_user " \
      "FROM Images " \
      "WHERE Is_catalog = TRUE "
      "ORDER BY Id_image DESC " \
      "LIMIT ? OFFSET ?;";
};
