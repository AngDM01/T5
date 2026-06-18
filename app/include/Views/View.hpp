#pragma once

#include "TemplateEngine.hpp"

#include <map>
#include <string>

using namespace std;

class View
{
 public:
  View(TemplateEngine& templateEnginer) : templateEnginer(templateEnginer) {}

  virtual ~View() = default;

  string render() {
    string header = buildHeader();
    string footer = buildFooter();
    string page = buildPage();

    return "Content-Type: text/html\r\n\r\n" + header + page + footer;
  }

 protected:
  string buildHeader()
  {
    try {
      templateEnginer.loadTemplate(headerRoute);
      return templateEnginer.renderHtml(getHeaderVariables());
    }
    catch (const exception& e) {
      cerr << "Error: " << e.what() << endl;
      return "<html><body><h1>Error</h1><p>Un error ocurrió mientras se renderizaba la cabecera.</p></body></html>";
    }
  }

  string buildFooter() {
    try {
      templateEnginer.loadTemplate(footerRoute);
      return templateEnginer.renderHtml(getFooterVariables());
    }
    catch (const exception& e) {
      cerr << "Error: " << e.what() << endl;
      return "<html><body><h1>Error</h1><p>Un error ocurrió mientras se renderizaba el pie de página.</p></body></html>";
    }
  }

  virtual string buildPage() = 0;

  virtual map<string, string> getHeaderVariables()
  {
    map<string, string> variables;

    variables["PAGETITLE"] = pageTitle;

    string options = "<a href=\"/cgi/loginCGI.cgi\" class=\"menu-item\">Ingresar</a>";

    variables["OPTIONS"] = options;

    return variables;
  }

  virtual map<string, string> getFooterVariables()
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
