#ifndef BOLT_BUFFERED_READER_H
#define BOLT_BUFFERED_READER_H

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

class BufferedReader {
 public:
  explicit BufferedReader(const char *buf, int len);
  explicit BufferedReader(const std::unique_ptr<char[]> &buf, int len);

  std::string nextLine();

  std::string nextWord();

  bool pastEnd();

  void skipLine();

  void resetHead();

 private:
  void makeSureBufferHeadIsInBuffer();

  void movePastWhitespace();

  void moveToNextLetter();

  void moveToNewLine();

  void setStartOfOutput();

  void moveToNextWhitespace();

  std::string createOutputString();

  const char *front;
  const char *current;
  const int length;

  const char *stringStart;
};

#endif  // BOLT_BUFFERED_READER_H
