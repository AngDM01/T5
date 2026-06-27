#pragma once

#include "TemplateEngine.hpp"

#include <map>
#include <string>
#include <exception>

using namespace std;

class View
{
 public:
  View(TemplateEngine& templateEnginer)
    : templateEnginer(templateEnginer)
  {
  }

  virtual ~View() = default;

  string Render()
  {
    string header = BuildHeader();
    string footer = BuildFooter();
    string page = BuildPage();

    return "Content-Type: text/html\r\n\r\n" + header + page + footer;
  }

 protected:
  string BuildHeader()
  {
    try
    {
      templateEnginer.LoadTemplate(headerRoute);
      return templateEnginer.RenderHtml(GetHeaderVariables());
    }
    catch (const exception& e)
    {
      return "<html><body><h1>Error</h1><p>Un error ocurrió mientras se renderizaba la cabecera.</p></body></html>";
    }
  }

  string BuildFooter()
  {
    try
    {
      templateEnginer.LoadTemplate(footerRoute);
      return templateEnginer.RenderHtml(GetFooterVariables());
    }
    catch (const exception& e)
    {
      return "<html><body><h1>Error</h1><p>Un error ocurrió mientras se renderizaba el pie de página.</p></body></html>";
    }
  }

  virtual string BuildPage() = 0;

  virtual map<string, string> GetHeaderVariables()
  {
    map<string, string> variables;

    variables["PAGETITLE"] = pageTitle;

    string options = "<a href=\"/cgi/LoginCGI.cgi\" class=\"menu-item\">Ingresar</a>";

    variables["OPTIONS"] = options;

    return variables;
  }

  virtual map<string, string> GetFooterVariables()
  {
    map<string, string> variables;

    variables["PAGETITLE"] = pageTitle;
    variables["AUTHOR"] = "Ángel Jesús Mena Coudin";
    variables["YEAR"] = year;

    return variables;
  }

 protected:
  string headerRoute = "/usr/local/apache2/app/templates/Header/header.html";
  string footerRoute = "/usr/local/apache2/app/templates/Footer/footer.html";
  string pageTitle = "Con Cariño";
  string year = "2026";

  TemplateEngine& templateEnginer;
};
