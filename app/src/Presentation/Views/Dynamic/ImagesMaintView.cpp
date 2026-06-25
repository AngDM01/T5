#include "ImagesMaintView.hpp"

#include <sstream>

#include "ComponentsBuilder.hpp"
#include "Imagehelper.hpp"
#include "ImagesModel.hpp"

using namespace std;

ImagesMaintView::ImagesMaintView(TemplateEngine &templateEnginer, list<ImagesModel>& images, int imagesCount, int maxImagesCount, int limit, int offset)
  : DynamicView(templateEnginer, "/usr/local/apache2/app/templates/Dynamic/imagesMant.html"),
  images(images),
  imagesCount(imagesCount),
  maxImagesCount(maxImagesCount),
  limit(limit),
  offset(offset)
{
}

map<string, string> ImagesMaintView::GetHeaderVariables()
{
  map<string, string> variables;

  variables["PAGETITLE"] = pageTitle;

  string options = "<a href=\"/cgi/CloseSessionCGI.cgi\" class=\"menu-item\">Cerrar Sesión</a>";

  variables["OPTIONS"] = options;

  return variables;
}

map<string, string> ImagesMaintView::GetPageVariables()
{
  map<string, string> variables;

  variables["ImagesCount"] = std::to_string(imagesCount);
  variables["MaxImagesCount"] = std::to_string(maxImagesCount);
  variables["ImagesCards"] = CreateImagesCards();

  return variables;
}

string ImagesMaintView::CreateImagesCards()
{
  ComponentsBuilder builder;

  return builder.BuildImageCarrouselType2(images, "carrImgId", imagesCount, limit, offset);
}
