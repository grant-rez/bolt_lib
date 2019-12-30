#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>

#include "bolt_impl.h"
#include "http/http_connection_handler.h"

const char* HTML_REQUEST =
    "GET / HTTP/1.1\n"
    "Host: localhost:8080\n"
    "Connection: keep-alive\n"
    "Cache-Control: max-age=0\n"
    "Upgrade-Insecure-Requests: 1\n"
    "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_4) "
    "AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.131 "
    "Safari/537.36\n"
    "Accept: "
    "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/"
    "apng,*/*;q=0.8,application/signed-exchange;v=b3\n"
    "Accept-Encoding: gzip, deflate, br\n"
    "Accept-Language: en-US,en;q=0.9\n\n";

const std::string HTML_REQUEST_STRING(HTML_REQUEST);

const char* EXPECTED_RESPONSE =
    "HTTP/1.1 404\n"
    "Content -\n"
    "Type : text / html Content -\n"
    "Length : 27 \n\n"
    "<h1>Page is not found!</h1>";

const std::string EXPECTED_RESPONSE_STRING(EXPECTED_RESPONSE);

class MockConnectionHandler
    : public trompeloeil::mock_interface<HttpConnectionHandler> {
 public:
  IMPLEMENT_MOCK0(setup);
  IMPLEMENT_MOCK0(getRequest);
  IMPLEMENT_MOCK1(sendResponse);
};

class MockConnection : public trompeloeil::mock_interface<HttpConnection> {
 public:
  IMPLEMENT_MOCK0(getRawRequest);
  IMPLEMENT_MOCK0(getRawRequestLength);
  IMPLEMENT_MOCK2(setRawResponse);
};

TEST_CASE("simple test", "[bolt]") {
  std::unique_ptr<MockConnectionHandler> mockConnHandler =
      std::make_unique<MockConnectionHandler>();

  MockConnectionHandler& mockConnHandlerRef = *mockConnHandler.get();

  std::unique_ptr<MockConnection> mockConn = std::make_unique<MockConnection>();
  MockConnection* mockConnPtr = mockConn.get();
  MockConnection& mockConnRef = *mockConnPtr;

  BoltImpl boltImpl(std::move(mockConnHandler));

  SECTION("test error page handler") {
    REQUIRE_CALL(mockConnHandlerRef, getRequest())
        .LR_RETURN(std::move(mockConn));

    REQUIRE_CALL(mockConnHandlerRef,
                 sendResponse(ANY(std::unique_ptr<HttpConnection>)))
        .WITH(_1.get() == mockConnPtr);

    std::unique_ptr<char[]> reqBuffer =
        std::make_unique<char[]>(HTML_REQUEST_STRING.size());
    memcpy(reqBuffer.get(), HTML_REQUEST_STRING.c_str(),
           HTML_REQUEST_STRING.size());

    REQUIRE_CALL(mockConnRef, getRawRequest())
        .LR_RETURN(reqBuffer);

    REQUIRE_CALL(mockConnRef, getRawRequestLength())
        .RETURN(HTML_REQUEST_STRING.size());

    REQUIRE_CALL(mockConnRef,
                 setRawResponse(ANY(std::unique_ptr<char[]>), ANY(int)))
        .WITH(memcmp(_1.get(), EXPECTED_RESPONSE_STRING.c_str(),
                     EXPECTED_RESPONSE_STRING.size()));

    boltImpl.serveNextRequest();
  }
}