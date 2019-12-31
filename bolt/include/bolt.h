#ifndef BOLT_BOLT_H
#define BOLT_BOLT_H

#include "html_page.h"

class BoltImpl;

class Bolt {
 public:
  Bolt();
  Bolt(Bolt &&other);
  Bolt & operator=(Bolt &&other);
  ~Bolt();

  void run();

  void registerHandler(std::string path, HtmlPage (*page)());

  void setDefaultPath(HtmlPage (*page)());

  Bolt(Bolt const &other) = delete;
  Bolt operator=(Bolt const &other) = delete;

 private:
  std::unique_ptr<BoltImpl> pImpl;
};
#endif  // BOLT_BOLT_H
