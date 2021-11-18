#include "utility.hpp"

#include <stdexcept>
#include <cstdlib>
#include <cstring>

details::SortType getSortType(const char *order)
{
  if (order == nullptr)
  {
    throw std::invalid_argument("The order must not be empty");
  }

  if (std::strcmp("ascending", order) == 0)
  {
    return details::SortType::ASCENDING;
  }

  if (std::strcmp("descending", order) == 0)
  {
    return details::SortType::DESCENDING;
  }

  throw std::invalid_argument("This is not a sort type");
}

void details::fillRandom(double* array, size_t size)
{
  if (!array)
  {
    throw std::invalid_argument("The array must contain something");
  }

  for (size_t i = 0; i < size; i++)
  {
    array[i] = -1 + static_cast<double>(std::rand()) / RAND_MAX * 2;
  }
}
