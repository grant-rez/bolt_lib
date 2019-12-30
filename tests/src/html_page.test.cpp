#include <catch.hpp>

#include "html_page.h"

TEST_CASE("simple HtmlPage test", "[html_page]") {
  HtmlPage page;
  page.loadFromString("<h1>Testing: [% myvar %]</h1>");
  page.setValue("myvar", "html_page");

  REQUIRE(page.getPageHtml() == "<h1>Testing: html_page</h1>");
}
