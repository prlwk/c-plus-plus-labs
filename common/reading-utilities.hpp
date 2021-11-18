#ifndef READING_UTILITIES_HPP
#define READING_UTILITIES_HPP

#include <istream>

class GuardIstream
{
public:
  GuardIstream(std::istream& stream);
  ~GuardIstream();

private:
  std::istream &stream_;
  std::istream::fmtflags flags_;
};

std::istream& skipWS(std::istream& input);
std::istream& checkEnd(std::istream& input);

#endif
