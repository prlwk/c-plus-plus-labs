#include "point.hpp"

#include "reading-utilities.hpp"

const char OPEN_BRACKET = '(';
const char CLOSE_BRACKET = ')';
const char SEMICOLON = ';';
const char SEPARATOR = ' ';

std::istream& operator >>(std::istream& input, Point& point)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }

  GuardIstream guard(input);
  input >> std::noskipws;

  char symbol;
  input >> skipWS >> symbol;
  if (!input)
  {
    return input;
  }
  if (symbol != OPEN_BRACKET)
  {
    input.setstate(std::ios::failbit);
  }

  input >> skipWS >> point.x >> skipWS >> symbol;
  if (!input)
  {
    return input;
  }
  if (symbol != SEMICOLON)
  {
    input.setstate(std::ios::failbit);
  }

  input >> skipWS >> point.y >> skipWS >> symbol;
  if (!input)
  {
    return input;
  }
  if (symbol != CLOSE_BRACKET)
  {
    input.setstate(std::ios::failbit);
  }

  return input;
}

std::ostream& operator <<(std::ostream& output, const Point& point)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  output << OPEN_BRACKET << point.x << SEMICOLON << SEPARATOR << point.y << CLOSE_BRACKET;
  return output;
}
