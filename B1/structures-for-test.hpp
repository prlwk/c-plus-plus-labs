#ifndef STRUCTURES_FOR_TEST
#define STRUCTURES_FOR_TEST

#include <streambuf>
#include <iostream>
#include <sstream>

struct Redirecting
{
  Redirecting():
    oldCin(std::cin.rdbuf(inputStream.rdbuf())),
    oldCout(std::cout.rdbuf(outputStream.rdbuf()))
  {}

  void restore()
  {
    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);
  }

  std::istringstream inputStream;
  std::ostringstream outputStream;
  std::streambuf* oldCin;
  std::streambuf* oldCout;
};

#endif
