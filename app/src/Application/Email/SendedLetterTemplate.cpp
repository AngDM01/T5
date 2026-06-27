#include "SendedLetterTemplate.hpp"

#include <sstream>

SendedLetterTemplate::SendedLetterTemplate(const std::string &senderName, const std::string &senderEmail,
    const std::string &receiverName, const std::string &title)
  : senderName(senderName),
  senderEmail(senderEmail),
  receiverName(receiverName),
  title(title)
{
}

std::string SendedLetterTemplate::Build()
{
  std::ostringstream html;

  html << "<h2>Nueva carta recibida</h2>";

  html << "<p>";
  html << "¡Enhorabuena <strong>" << receiverName << "</strong>!, ";
  html << "has recibido una nueva carta titulada ";
  html << "<strong>\"" << title << "\"</strong> ";
  html << "de <strong>" << senderName << "</strong> ";
  html << "desde <a href=\"mailto:" << senderEmail << "\">"
        << senderEmail << "</a>.";
  html << "</p>";

  html << "<br>";

  html << "<h4>De parte del equipo CON CARIÑO</h4>";
  
  return html.str();
}
