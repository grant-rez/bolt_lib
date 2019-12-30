#include "html_page.h"

#include <fstream>
#include <iostream>
#include <sstream>

class HtmlTemplate {
 public:
  void loadTemplateFromFile(std::string path) {
    std::ifstream file;
    file.open(path);
    file.seekg(0, std::ios::end);
    html.resize(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&html[0], html.size());
    file.close();
  }

  void loadTemplateFromString(std::string templ) { html = templ; }

  std::string getRenderedHtml(
      const std::unordered_map<std::string, std::string>& variables) {
    std::stringstream ss;
    for (htmlIter = html.begin(); htmlIter < html.end() - 1; ++htmlIter) {
      if (*htmlIter == '[' && *(htmlIter + 1) == '%') {
        loadVariableIntoTemplate(variables, ss);
      } else {
        ss << *htmlIter;
      }
    }
    ss << *htmlIter;

    return ss.str();
  }

 private:
  std::string html;
  std::string::iterator htmlIter;

  void loadVariableIntoTemplate(
      const std::unordered_map<std::string, std::string>& variables,
      std::stringstream& ss) {
    ++htmlIter;
    while (*(++htmlIter) == ' ')
      ;

    auto stringStart = htmlIter;
    while (*(++htmlIter) != ' ')
      ;

    std::string variableKey(stringStart, htmlIter);
    if (variables.find(variableKey) != variables.end()) {
      ss << variables.at(variableKey);
    }

    while (((*htmlIter != '%') || (*(htmlIter + 1) != ']')) &&
           htmlIter < html.end() - 1) {
      ++htmlIter;
    }
    ++htmlIter;
  }
};

HtmlPage::HtmlPage() : htmlTemplate(std::make_unique<HtmlTemplate>()) {}

HtmlPage::HtmlPage(const HtmlPage& other)
    : htmlTemplate(std::make_unique<HtmlTemplate>(*other.htmlTemplate)),
      header(other.header),
      templateVariables(other.templateVariables) {}
HtmlPage& HtmlPage::operator=(const HtmlPage& other) {
  if (this != &other) {
    htmlTemplate = std::make_unique<HtmlTemplate>(*other.htmlTemplate);
    header = other.header;
    templateVariables = other.templateVariables;
  }
  return *this;
}

HtmlPage ::~HtmlPage() {}

void HtmlPage::loadFromString(std::string html) {
  htmlTemplate->loadTemplateFromString(html);
}
void HtmlPage::loadFromFile(std::string path) {
  htmlTemplate->loadTemplateFromFile(path);
}

void HtmlPage::setValue(std::string key, std::string value) {
  templateVariables[key] = value;
}

std::string HtmlPage::getPageHtml() {
  return htmlTemplate->getRenderedHtml(templateVariables);
}