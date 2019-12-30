#ifndef BOLT_BOLT_IMPL_H
#define BOLT_BOLT_IMPL_H

#include <memory>
#include <string>
#include <unordered_map>

#include "html_page.h"
#include "http/http_connection_handler.h"
#include "http/http_connection_handler_factory.h"

class BoltImpl {
 public:
  BoltImpl(std::unique_ptr<HttpConnectionHandler> ch);

  void run();

  void registerHandler(std::string, HtmlPage (*)());

  void setDefaultPath(HtmlPage (*)());

  void serveNextRequest();

 private:
  std::unordered_map<std::string, HtmlPage (*)()> mappings;
  HtmlPage (*default_page)();

  std::unique_ptr<HttpConnectionHandler> connHandler;

  const HtmlPage getHtmlPage(std::string);

  std::unique_ptr<HttpConnection> getNextConnection();
};

#endif