#include "http/http_request.h"

namespace {
HttpType getHttpType(std::string type) {
  if (type == "GET") {
    return HttpType::GET;
  } else if (type == "POST") {
    return HttpType::POST;
  } else {
    return HttpType::OTHER;
  }
}
}  // namespace

HttpRequest::HttpRequest(std::unique_ptr<HttpConnection>& conn) {
  const std::unique_ptr<char[]>& rawReq = conn->getRawRequest();
  std::cout << "Request Cnstr: ";
  int length = conn->getRawRequestLength();
  for (int i = 0; i < length; ++i) {
    std::cout << rawReq[i];
  }
  std::cout << std::endl;
  BufferedReader bf(rawReq, length);
  parseType(bf);
  parsePath(bf);
  parseHeaders(bf);
}

HttpType HttpRequest::getType() { return httpType; }

std::string HttpRequest::getPath() { return path; }

std::string HttpRequest::getHeader(std::string headerKey) {
  if (headers.find(headerKey) == headers.end()) {
    throw std::runtime_error("header not in specified in request");
  } else {
    return headers[headerKey];
  }
}

void HttpRequest::parseType(BufferedReader& bf) {
  std::string typeStr = bf.nextWord();
  httpType = getHttpType(typeStr);
}

void HttpRequest::parsePath(BufferedReader& bf) { path = bf.nextWord(); }

void HttpRequest::parseHeaders(BufferedReader& bf) {
  while (!bf.pastEnd()) {
    std::string headerKey = bf.nextWord();
    std::string headerValue = bf.nextWord();

    // strip trailing colon on key and  append to map
    headers[headerKey.substr(0, headerKey.length() - 1)] = headerValue;
  }
}