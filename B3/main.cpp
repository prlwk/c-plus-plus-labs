#include <iostream>
#include <stdexcept>
#include <sstream>

#include "tasks.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Input arguments must be 2";
      return 1;
    }

    int taskNumber = 0;
    std::istringstream stream(argv[1]);
    stream >> taskNumber;
    if (!stream.eof())
    {
      std::cerr << "Incorrect number of task";
      return 1;
    }

    switch (taskNumber)
    {
      case 1:
      {
        try
        {
          executeTask1(std::cin, std::cout);
        }
        catch (const std::runtime_error &error)
        {
          std::cerr << error.what();
          return 2;
        }
        catch (const std::invalid_argument &error)
        {
          std::cerr << error.what();
          return 1;
        }
        break;
      }

      case 2:
      {
        try
        {
          executeTask2(std::cout);
        }
        catch (const std::out_of_range &error)
        {
          std::cerr << error.what();
          return 2;
        }
        catch (const std::overflow_error &error)
        {
          std::cerr << error.what();
          return 1;
        }
        break;
      }

      default:
      {
        std::cerr << "Incorrect number of task";
        return 1;
      }
    }
  }
  catch (const std::exception& error)
  {
    std::cerr << error.what();
    return 2;
  }

  return 0;
}
