#include <fstream>
#include <iostream>
#include <sstream>

#include "bolt.h"
#include "bolt_impl.h"
#include "buffered_reader.h"
#include "constants.h"
#include "http/http_connection_handler.h"
#include "http/http_connection_handler_factory.h"
#include "http/http_request.h"

Bolt::Bolt()
    : pImpl(std::make_unique<BoltImpl>(
          HttpConnectionHandlerFactory::getHttpConnectionHandler())) {}

Bolt::Bolt(Bolt &&other) : pImpl(std::move(other.pImpl)) {}

Bolt Bolt::operator=(Bolt &&other) {
  if (this != &other) {
    pImpl = std::move(other.pImpl);
  }
  return std::move(*this);
}

Bolt::~Bolt() = default;

void Bolt::run() { pImpl->run(); }

void Bolt::registerHandler(std::string path, HtmlPage (*page)()) {
  return pImpl->registerHandler(path, page);
}

void Bolt::setDefaultPath(HtmlPage (*page)()) {
  return pImpl->setDefaultPath(page);
}

namespace {
const std::string createResponse(HtmlPage page) {
  std::stringstream ss;
  std::string html = page.getPageHtml();
  ss << HTTP_VERSION << " " << page.header.status << "\n";
  ss << "Content-Type: " << page.header.ctype << "\n";
  ss << "Content-Length: " << html.size() << "\n";
  ss << "\n";
  ss << html;

  return ss.str();
}

const std::string parseRequest(char *buf, int length) {
  BufferedReader bf(buf, length);
  bf.nextWord();
  return bf.nextWord();
}

}  // namespace

HtmlPage BoltDefaultDefaultPage() {
  HtmlPage page;
  page.loadFromString("<h1>Page is not found!</h1>");
  page.header.status = HttpStatus::NOT_FOUND;
  return page;
}

BoltImpl::BoltImpl(std::unique_ptr<HttpConnectionHandler> ch)
    : connHandler(std::move(ch)), default_page(BoltDefaultDefaultPage) {}

void BoltImpl::run() {
  connHandler->setup();
  while (true) {
    serveNextRequest();
  }
}

void BoltImpl::serveNextRequest() {
  std::unique_ptr<HttpConnection> conn = getNextConnection();

  HttpRequest request(conn);

  HtmlPage page = getHtmlPage(request.getPath());

  std::string response = createResponse(page);
  std::unique_ptr<char[]> responseBuf =
      std::make_unique<char[]>(response.size());
  memcpy(responseBuf.get(), response.c_str(), response.size());
  conn->setRawResponse(std::move(responseBuf), response.size());
  connHandler->sendResponse(std::move(conn));
}

std::unique_ptr<HttpConnection> BoltImpl::getNextConnection() {
  return connHandler->getRequest();
}

void BoltImpl::registerHandler(std::string path, HtmlPage(func)()) {
  if (mappings.find(path) != mappings.end()) {
    throw std::runtime_error("Already add a handler for this path");
  } else {
    mappings[path] = func;
  }
}

void BoltImpl::setDefaultPath(HtmlPage(func)()) { default_page = func; }

const HtmlPage BoltImpl::getHtmlPage(std::string path) {
  std::cout << "Path: " << path << std::endl;
  if (mappings.find(path) != mappings.end()) {
    return mappings[path]();
  } else {
    return default_page();
  }
}