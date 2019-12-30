#include <catch.hpp>

#include <string>

#include "buffered_reader.h"

TEST_CASE("simple nextWord test", "[buffered_reader]") {
  std::string str("simple test");
  BufferedReader reader(str.c_str(), str.length());
  REQUIRE(reader.nextWord() == std::string("simple"));
  REQUIRE(reader.nextWord() == std::string("test"));
}

TEST_CASE("test new line and multiple spaces with nextWord",
          "[buffered_reader]") {
  std::string str("new testcase  for \n multiple lines");
  BufferedReader reader(str.c_str(), str.length());
  REQUIRE(reader.nextWord() == std::string("new"));
  REQUIRE(reader.nextWord() == std::string("testcase"));
  REQUIRE(reader.nextWord() == std::string("for"));
  REQUIRE(reader.nextWord() == std::string("multiple"));
  REQUIRE(reader.nextWord() == std::string("lines"));
}

TEST_CASE("simple nextLine test", "[buffered_reader]") {
  std::string str("simple\ntest case!\nends here");
  BufferedReader reader(str.c_str(), str.length());
  REQUIRE(reader.nextLine() == std::string("simple"));
  REQUIRE(reader.nextLine() == std::string("test case!"));
  REQUIRE(reader.nextLine() == std::string("ends here"));
}

TEST_CASE("emptyline nextLine test", "[buffered_reader]") {
  std::string str("line\n\n\nanother line\n \nlast");
  BufferedReader reader(str.c_str(), str.length());
  REQUIRE(reader.nextLine() == std::string("line"));
  REQUIRE(reader.nextLine() == std::string(""));
  REQUIRE(reader.nextLine() == std::string(""));
  REQUIRE(reader.nextLine() == std::string("another line"));
  REQUIRE(reader.nextLine() == std::string(""));
  REQUIRE(reader.nextLine() == std::string("last"));
}
