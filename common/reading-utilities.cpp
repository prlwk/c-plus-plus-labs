#include "reading-utilities.hpp"

std::istream& skipWS(std::istream& input)
{
  while (isblank(input.peek()))
  {
    input.get();
  }
  return input;
}

std::istream &checkEnd(std::istream &input)
{
  if (input.eof())
  {
    return input;
  }

  input >> skipWS;
  if (input.eof())
  {
    return input;
  }
  std::string line;
  std::getline(input, line);
  if (line.empty())
  {
    return input;
  }
  input.setstate(std::ios::failbit);
  return input;
}

GuardIstream::GuardIstream(std::istream &stream) :
  stream_(stream),
  flags_(stream.flags())
{}

GuardIstream::~GuardIstream()
{
  stream_.setf(flags_);
}
