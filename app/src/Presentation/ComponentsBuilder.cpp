#include "ComponentsBuilder.hpp"

#include <list>
#include <sstream>

#include "Imagehelper.hpp"
#include "ImagesModel.hpp"
#include "LetterModel.hpp"

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
        << "<img class=\"img-cust\" "
        << "data-image-id=\"" << image.GetIdImage() << "\" "
        << "onclick=\"selectImage(this, '" << src << "')\" "
        << "src=\"" << src << "\">"
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

std::string ComponentsBuilder::BuildSendedLetterTable(std::list<LetterModel> &sendedLetters, int sendedLetterCount, int limit, int offset)
{
  ostringstream html;

  int totalPages = (sendedLetterCount + limit - 1) / limit;
  int currentPage = (offset / limit) + 1;
  
  html << "<section class=\"letters-table\"> "
      << "<div class=\"flex-row jutf-cont-spcbet\">"
      << "<h2>Cartas enviadas</h2>"
      << "Página " << currentPage << " "
      << "de " << totalPages
      << "<div>"
      << sendedLetterCount <<  " cartas enviadas"
      << "</div>"
      << "</div>";

  html << "<div class=\"flex-col\">"
      << "<section class=\"letters-tabl\">"
      << "<span class=\"table-h\">"
      << "<span>Título</span> "
      << "<span>Destinatario</span> "
      << "<span>Correo del destinatario</span> "
      << "<span>Fecha de envío</span> "
      << "<span>Acciones</span> "
      << "</span>";

  for (const LetterModel& letter : sendedLetters)
  {
    html << "<span class=\"table-r\">"
        << "<span>" << letter.GetLetterTitle() << "</span> "
        << "<span>" << letter.GetReceiverName() << "</span> "
        << "<span>" << letter.GetReceiverEmail() << "</span> "
        << "<span>" << letter.GetSendDate() << "</span> "
        << "<span class=\"custom-bttn2\" onclick=\"viewLetterDetails("
        << letter.GetIdLetter()
        << ")\">Ver</span>"
        << "</span>";
  }

  html << "</div>";
  
  html << "<div class=\"pagination\">";

  // paginador
  if (currentPage > 1)
  {
    html << "<button class=\"arrow-btn\" "
        << "onclick=\"loadLetterTable(true, "
        << (offset - limit)
        << ")\">◀</button>";
  }

  for (int page = 1; page <= totalPages; ++page)
  {
    bool show = page == 1 || page == totalPages || abs(page - currentPage) <= 1;

    if (!show)
    {
      if (page == 2 && currentPage > 4)
          html << "<span>...</span>";

      if (page == totalPages - 1 && currentPage < totalPages - 3)
          html << "<span>...</span>";

      continue;
    }

    if (page == currentPage)
    {
      html << "<button class=\"custom-bttn2 active\">"
          << page
          << "</button>";
    }
    else
    {
        html << "<button class=\"custom-bttn2\" "
            << "onclick=\"loadLetterTable(true, "
            << (page - 1) * limit
            << ")\">"
            << page
            << "</button>";
    }
  }

  if (currentPage < totalPages)
  {
    html << "<button class=\"arrow-btn\" "
        << "onclick=\"loadLetterTable(true, "
        << (offset + limit)
        << ")\">▶</button>";
  }

  html << "</div>"
      << "</section>";

  return html.str();
}

std::string ComponentsBuilder::BuildReceivedLetterTable(std::list<LetterModel> &receivedLetters, int receivedLetterCount, int limit, int offset)
{
  ostringstream html;

  int totalPages = (receivedLetterCount + limit - 1) / limit;
  int currentPage = (offset / limit) + 1;

  html << "<section class=\"letters-table\"> "
      << "<div class=\"flex-row jutf-cont-spcbet\">"
      << "<h2>Cartas Recibidas</h2>"
      << "Página " << currentPage << " "
      << "de " << totalPages
      << "<div>"
      << receivedLetterCount <<  " cartas recibidas"
      << "</div>"
      << "</div>";

  html << "<div class=\"flex-col\">"
      << "<section class=\"letters-tabl\">"
      << "<span class=\"table-h\">"
      << "<span>Título</span> "
      << "<span>Remitente</span> "
      << "<span>Correo del remitente</span> "
      << "<span>Fecha de envío</span> "
      << "<span>Acciones</span> "
      << "</span>";

  for (const LetterModel& letter : receivedLetters)
  {
    html << "<span class=\"table-r\">";

    if (!letter.GetOpenedStatus())
    {
      html << "<span class=\"resaltedDot\"></span>";
    }

    html << "<span>" << letter.GetLetterTitle() << "</span> "
        << "<span>" << letter.GetSenderName() << "</span> "
        << "<span>" << letter.GetSenderEmail() << "</span> "
        << "<span>" << letter.GetSendDate() << "</span> "
        << "<span class=\"custom-bttn2\" onclick=\"viewLetterDetails("
        << letter.GetIdLetter()
        << ")\">Ver</span>"
        << "</span>";
  }

  html << "</div>";
  
  html << "<div class=\"pagination\">";

  // paginador
  if (currentPage > 1)
  {
    html << "<button class=\"arrow-btn\" "
        << "onclick=\"loadLetterTable(false, "
        << (offset - limit)
        << ")\">◀</button>";
  }

  for (int page = 1; page <= totalPages; ++page)
  {
    bool show = page == 1 || page == totalPages || abs(page - currentPage) <= 1;

    if (!show)
    {
      if (page == 2 && currentPage > 4)
          html << "<span>...</span>";

      if (page == totalPages - 1 && currentPage < totalPages - 3)
          html << "<span>...</span>";

      continue;
    }

    if (page == currentPage)
    {
      html << "<button class=\"custom-bttn2 active\">"
          << page
          << "</button>";
    }
    else
    {
        html << "<button class=\"custom-bttn2\" "
            << "onclick=\"loadLetterTable(false, "
            << (page - 1) * limit
            << ")\">"
            << page
            << "</button>";
    }
  }

  if (currentPage < totalPages)
  {
    html << "<button class=\"arrow-btn\" "
        << "onclick=\"loadLetterTable(false, "
        << (offset + limit)
        << ")\">▶</button>";
  }

  html << "</div>"
      << "</section>";

  return html.str();
}

std::string ComponentsBuilder::BuildImageSource(const ImagesModel& image)
{
  if (image.GetIdImage() == 0) return "none";

  std::string mime = Imagehelper::ImageExtensionMIME(image.GetExtension());

  std::string src = "data:image/" + mime + ";base64," + Imagehelper::Encode(image.GetImageData());

  return "url('" + src + "')";
}
