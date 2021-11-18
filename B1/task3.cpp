#include <iostream>
#include <vector>
#include <stdexcept>

#include "utility.hpp"

void executeTask3()
{
  int number = -1;
  std::vector<int> vector;

  while (std::cin >> number)
  {
    if (number == 0)
    {
      break;
    }
    vector.push_back(number);
  }

  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Incorrect input");
  }

  if (!vector.empty())
  {
    if (number != 0)
    {
      throw std::runtime_error("Array must end with 0");
    }

    auto iterator = vector.begin();

    if (vector.back() == 1)
    {
      while (iterator != vector.end())
      {
        if (*iterator % 2 == 0)
        {
          iterator = vector.erase(iterator);
        }
        else
        {
          iterator++;
        }
      }
    }

    if (vector.back() == 2)
    {
      while (iterator != vector.end())
      {
        if (*iterator % 3 == 0)
        {
          iterator = vector.insert(iterator + 1, 3, 1) + 3;
        }
        else
        {
          iterator++;
        }
      }
    }

    print(vector, std::cout);
  }
}
