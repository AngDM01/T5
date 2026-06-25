#include "ComponentsBuilder.hpp"

#include <list>
#include <sstream>

#include "Imagehelper.hpp"
#include "ImagesModel.hpp"

using namespace std;

string ComponentsBuilder::BuildImageCarrouselType2(list<ImagesModel>& images, string containerId, int imagesCount, int limit, int offset)
{
  ostringstream html;

  html << "<div class=\"flex-row jutf-cont-spcbet\" style=\"gap: 10px;\">";

  if (offset > 0)
  {
    html << "<button class=\"arrow-btn\" onclick=\"loadImages('"
      << containerId
      << "', "
      << (offset - limit)
      << ")\">◀</button>";
  }

  html << "<div class=\"carrousel2\">";

  for (const ImagesModel& image : images)
  {
    string mime = Imagehelper::ImageExtensionMIME(image.GetExtension());

    html << "<div class=\"imageCard2\">"
        << "<div>"
        << image.GetAlias()
        << "<label class=\"custom-bttn2\" onclick=\"deleteImagePopUp("
        << image.GetIdImage()
        << ")\">X</label>"
        << "</div>"
        << "<img class=\"img-cust\" src=\"data:image/"
        << mime
        << ";base64,"
        << Imagehelper::Encode(image.GetImageData())
        << "\">"
        << "</div>";
  }

  html << "</div>";

  if ((offset + limit) < imagesCount)
  {
    html << "<button class=\"arrow-btn\" onclick=\"loadImages('"
      << containerId
      << "', "
      << (offset + limit)
      << ")\">▶</button>";
  }

  html << "</div>";

  return html.str();
}

string ComponentsBuilder::BuildImageCarrouselType1(list<ImagesModel> &images, string containerId, int imagesCount, int limit,
    int offset, bool isCatalog)
{
  ostringstream html;

  html << "<div class=\"flex-row jutf-cont-spcbet\" style=\"gap: 10px;\">";

  if (offset > 0)
  {
    html << "<button class=\"arrow-btn\" onclick=\"loadImages('"
     << containerId
     << "', "
     << (offset - limit)
     << ", "
     << (isCatalog ? "true" : "false")
     << ")\">◀</button>";
  }

  html << "<div class=\"carrousel\">";

  for (const ImagesModel& image : images)
  {
    string mime = Imagehelper::ImageExtensionMIME(image.GetExtension());

    string src = "data:image/" + mime + ";base64," + Imagehelper::Encode(image.GetImageData());

    html << "<div class=\"imageCard\">"
        << "<img class=\"img-cust\" onclick=\"setBackgroundImage('"
        << src
        << "')\" src=\""
        << src
        << "\">"
        << "</div>";
  }

  html << "</div>";

  if ((offset + limit) < imagesCount)
  {
    html << "<button class=\"arrow-btn\" onclick=\"loadImages('"
      << containerId
      << "', "
      << (offset + limit)
      << ", "
      << (isCatalog ? "true" : "false")
      << ")\">▶</button>";
  }

  html << "</div>";

  return html.str();
}
