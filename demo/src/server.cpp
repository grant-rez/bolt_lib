#include "bolt.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>

std::vector<std::string> carNames;

HtmlPage home() {
  HtmlPage page;
  page.loadFromString("Hello World!");
  return page;
}

HtmlPage cars() {
  
  HtmlPage page;
  page.loadFromString("<h1>Cars [% car %]!</h1>");
  page.setValue("car", carNames[rand() % carNames.size()]);
  return page;
}

HtmlPage defaultPath() {
  HtmlPage page;
  page.loadFromString("<h1>Page is not found!</h1>");
  return page;
}

void setupCarNames() {
  std::ifstream file;
  file.open("assets/cars.txt");
  std::string carName;
  while(file >> carName) {
    carNames.push_back(carName);
  }
}

int main() {
  setupCarNames();

  Bolt bolt;
  bolt.registerHandler("/", home);
  bolt.registerHandler("/cars", cars);

  bolt.run();
}