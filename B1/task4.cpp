#include <vector>
#include <string>
#include <stdexcept>

#include "utility.hpp"
#include "policy.hpp"

void executeTask4(const char *order, size_t size)
{
  details::SortType sortType = getSortType(order);

  if (size == 0)
  {
    throw std::invalid_argument("Size must be >0");
  }

  std::vector<double> vector(size);
  details::fillRandom(vector.data(), size);
  print(vector, std::cout);
  std::cout << '\n';
  details::bubbleSort<BracketsPolicy>(vector, sortType);
  print(vector, std::cout);
}
