#ifndef BOLT_HTML_PAGE
#define BOLT_HTML_PAGE

#include <memory>
#include <string>
#include <unordered_map>

enum HttpStatus {
  OK = 200,
  BAD_REQUEST = 400,
  FORBIDDEN = 403,
  NOT_FOUND = 404,
  INTERNAL_SERVER_ERROR = 500
};

struct HttpHeader {
  HttpStatus status = OK;
  std::string ctype = "text/html";
};

class HtmlTemplate;

class HtmlPage {
 public:
  HtmlPage();
  HtmlPage(const HtmlPage& other);
  HtmlPage& operator=(const HtmlPage& other);
  ~HtmlPage();

  void loadFromString(std::string html);
  void loadFromFile(std::string path);
  void setValue(std::string key, std::string value);
  std::string getPageHtml();

  HttpHeader header;  // TEMP

 private:
  std::unordered_map<std::string, std::string> templateVariables;
  std::unique_ptr<HtmlTemplate> htmlTemplate;
};

#endif  // BOLT_HTML_PAGE