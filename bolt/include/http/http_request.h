#ifndef BOLT_HTTP_REQUEST_H
#define BOLT_HTTP_REQUEST_H

#include <string>
#include <unordered_map>

#include "buffered_reader.h"
#include "http/http_connection_handler.h"

enum HttpType { GET, POST, OTHER };

class HttpRequest {
 public:
  HttpRequest(std::unique_ptr<HttpConnection> &conn);
  HttpType getType();
  std::string getPath();
  std::string getHeader(std::string headerKey);

 private:
  HttpType httpType;
  std::string path;
  std::unordered_map<std::string, std::string> headers;

  void parseType(BufferedReader &bf);
  void parsePath(BufferedReader &bf);
  void parseHeaders(BufferedReader &bf);
};

#endif  // BOLT_HTTP_REQUEST_H