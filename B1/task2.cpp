#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include <stdexcept>
#include <cstdlib>

#include "utility.hpp"

void executeTask2(const char *name)
{
  if (name == nullptr)
  {
    throw std::invalid_argument("The name must not be empty");
  }

  std::ifstream fin(name);
  if (!fin)
  {
    throw std::runtime_error("File not open");
  }

  size_t size = 0;
  size_t maxSize = 512;

  std::unique_ptr<char[], decltype(&free)> array(static_cast<char*>(malloc(maxSize)), free);

  if (!array)
  {
    throw std::bad_alloc();
  }

  while (fin)
  {
    fin.read(&array[size], maxSize - size);
    size += fin.gcount();
    if (size == maxSize)
    {
      maxSize *= 2;
      std::unique_ptr<char[], decltype(&free)> tempArray(static_cast<char*>(realloc(array.get(), maxSize)), &free);
      if (!tempArray)
      {
        throw std::bad_alloc();
      }
      array.release();
      array = std::move(tempArray);
    }
  }
  std::vector<char> vector(array.get(), array.get() + size);
  print(vector, std::cout, "");
}
