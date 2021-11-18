#include <iostream>
#include <stdexcept>
#include <vector>
#include <iterator>
#include <algorithm>

#include "data-struct.hpp"
#include "greater-for-data-struct.hpp"

void executeTask(std::istream& input, std::ostream& output);

int main()
{
  try
  {
    executeTask(std::cin, std::cout);
  }
  catch (std::runtime_error& error)
  {
    std::cerr << error.what();
    return 2;
  }
  return 0;
}

void executeTask(std::istream& input, std::ostream& output)
{
  std::vector<DataStruct> vector((std::istream_iterator<DataStruct>(input)), std::istream_iterator<DataStruct>());
  if (!input.eof())
  {
    throw std::runtime_error("Read error");
  }
  std::sort(vector.begin(), vector.end(), GreaterForDatastruct());
  std::copy(vector.begin(), vector.end(), std::ostream_iterator<DataStruct>(output, "\n"));
}
