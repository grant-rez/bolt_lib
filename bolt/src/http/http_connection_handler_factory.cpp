#include "http/http_connection_handler_factory.h"

std::unique_ptr<HttpConnectionHandler>
HttpConnectionHandlerFactory::getHttpConnectionHandler() {
  return std::make_unique<SocketHttpConnectionHandler>();
}