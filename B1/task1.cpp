#include <iostream>
#include <vector>
#include <forward_list>
#include <stdexcept>

#include "utility.hpp"
#include "policy.hpp"

void executeTask1(const char *order)
{
  details::SortType sortType = getSortType(order);

  std::vector<int> vectorForFirstSort;

  int number = 0;

  while (std::cin >> number)
  {
    vectorForFirstSort.push_back(number);
  }

  if (!std::cin.eof())
  {
    throw std::runtime_error("Incorrect input");
  }

  if (vectorForFirstSort.empty())
  {
    return;
  }

  std::vector<int> vectorForSecondSort(vectorForFirstSort);
  std::forward_list<int> list(vectorForFirstSort.begin(), vectorForFirstSort.end());

  details::bubbleSort<BracketsPolicy>(vectorForFirstSort, sortType);
  details::bubbleSort<AtPolicy>(vectorForSecondSort, sortType);
  details::bubbleSort<ItPolicy>(list, sortType);

  print(vectorForSecondSort, std::cout);
  std::cout << '\n';
  print(vectorForFirstSort, std::cout);
  std::cout << '\n';
  print(list, std::cout);
}
