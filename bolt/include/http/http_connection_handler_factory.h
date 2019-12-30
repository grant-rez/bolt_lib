#ifndef BOLT_CONNECTION_HANDLER_FACTORY_H
#define BOLT_CONNECTION_HANDLER_FACTORY_H

#include "socket_http_connection_handler.h"

class HttpConnectionHandlerFactory {
 public:
  static std::unique_ptr<HttpConnectionHandler> getHttpConnectionHandler();
};

#endif  // BOLT_CONNECTION_HANDLER_FACTORY_H