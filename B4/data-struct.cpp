#include "data-struct.hpp"

#include <stdexcept>

#include "reading-utilities.hpp"

const int MAX_VALUE_FOR_KEY = 5;
const int MIN_VALUE_FOR_KEY = -5;
const char SEPARATOR = ',';

inline bool detail::isValidKey(int key)
{
  return (key <= MAX_VALUE_FOR_KEY) && (key >= MIN_VALUE_FOR_KEY);
}

std::istream& operator>>(std::istream& input, DataStruct& dataStruct)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  GuardIstream guard(input);
  input >> std::noskipws;
  int key1;
  input >> std::ws >> key1;
  if (!input)
  {
    return input;
  }
  if (!detail::isValidKey(key1))
  {
    input.setstate(std::ios_base::failbit);
    return input;
  }

  char symbol;
  input >> symbol;
  if (!input)
  {
    return input;
  }
  if (symbol != SEPARATOR)
  {
    input.setstate(std::ios_base::failbit);
    return input;
  }

  int key2;
  input >> skipWS >> key2;
  if (!input)
  {
    return input;
  }
  if (!detail::isValidKey(key2))
  {
    input.setstate(std::ios_base::failbit);
    return input;
  }

  input >> symbol;
  if (!input)
  {
    return input;
  }
  if (symbol != SEPARATOR)
  {
    input.setstate(std::ios_base::failbit);
    return input;
  }

  std::string str;
  std::getline(input >> skipWS, str);
  if (!input)
  {
    return input;
  }

  dataStruct.key1 = key1;
  dataStruct.key2 = key2;
  dataStruct.str = str;
  return input;
}

std::ostream& operator<<(std::ostream& output, const DataStruct& dataStruct)
{
  std::ostream::sentry sentry(output);
  if (sentry)
  {
    output << dataStruct.key1 << SEPARATOR << dataStruct.key2 << SEPARATOR << dataStruct.str;
  }
  return output;
}
