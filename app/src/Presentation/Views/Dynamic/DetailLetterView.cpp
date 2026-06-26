#include "DetailLetterView.hpp"

#include "DynamicView.hpp"
#include "LetterModel.hpp"
#include "TemplateEngine.hpp"
#include "Logger.hpp"

DetailLetterView::DetailLetterView(TemplateEngine &templateEngine, LetterModel &letter)
  : DynamicView(templateEngine, "/usr/local/apache2/app/templates/Dynamic/viewLetter.html"),
  letter(letter)
{
}

std::map<std::string, std::string> DetailLetterView::GetHeaderVariables()
{
  map<string, string> variables;

  variables["PAGETITLE"] = pageTitle;

  string options = "<a href=\"/cgi/CloseSessionCGI.cgi\" class=\"menu-item\">Cerrar Sesión</a>";

  variables["OPTIONS"] = options;

  return variables;
}

std::map<std::string, std::string> DetailLetterView::GetPageVariables()
{
  map<string, string> variables;
  
  variables["SenderName"] = letter.GetSenderName();
  variables["ReceiverName"] = letter.GetReceiverName();
  variables["ReceiverEmail"] = letter.GetReceiverEmail();
  variables["SenderEmail"] = letter.GetSenderEmail();
  variables["LetterTitle"] = letter.GetLetterTitle();
  variables["LetterText"] = letter.GetTextLetter();

  return variables;
}
