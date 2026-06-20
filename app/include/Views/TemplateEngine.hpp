#pragma once

#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <exception>

using namespace std;

class TemplateEngine
{
 public:
  TemplateEngine() = default;
  ~TemplateEngine() = default;

  void LoadTemplate(const string &path)
  {
    try {
    ifstream file(path);
    
    if (!file.is_open()) {
      throw runtime_error("No se pudo abrir el archivo de plantilla: " + path);
    }

    stringstream buffer;
    buffer << file.rdbuf();

    html = buffer.str(); 
  }
  catch (const exception &e) {
    throw runtime_error("Error loading template file: " + string(e.what()));
  }
  }

  string RenderHtml() { return html; }

  string RenderHtml(map<string, string> variables)
  {
    try {
      string result = html;

      for (const auto &[key, value] : variables)
      {
        string marker = "{{" + key + "}}";

        size_t pos;

        while ((pos = result.find(marker)) != string::npos)
        {
          result.replace(
              pos,
              marker.length(),
              value);
        }
      }

      return result;
    }
    catch (const exception &e) {
      throw runtime_error("Error al renderizar HTML: " + string(e.what()));
    }
  }

 private:
  string html;
};