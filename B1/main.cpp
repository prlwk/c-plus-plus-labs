#include <iostream>
#include <stdexcept>
#include <ctime>
#include <sstream>

#include "utility.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if ((argc < 2) || (argc > 4))
    {
      std::cerr << "Incorrect input arguments";
      return 1;
    }

    int number = 0;
    std::stringstream sstream(argv[1]);
    sstream >> number;

    if (!sstream.eof()) {
      std::cerr << "Error reading number of task!";
      return 1;
    }

    switch (number)
    {
      case 1:
      {
        if (argc != 3)
        {
          std::cerr << "Incorrect count of arguments";
          return 1;
        }

        try
        {
          executeTask1(argv[2]);
        }
        catch (const std::runtime_error& error)
        {
          std::cerr << error.what();
          return 2;
        }
        catch (const std::invalid_argument& error)
        {
          std::cerr << error.what();
          return 1;
        }

        break;
      }

      case 2:
      {
        if (argc != 3)
        {
          std::cerr << "Incorrect count of arguments";
          return 1;
        }

        try
        {
          executeTask2(argv[2]);
        }
        catch (const std::bad_alloc& error)
        {
          std::cerr << error.what();
          return 1;
        }
        catch (const std::runtime_error& error)
        {
          std::cerr << error.what();
          return 2;
        }
        break;
      }

      case 3:
      {
        if (argc != 2)
        {
          std::cerr << "Incorrect count of arguments";
          return 1;
        }

        try
        {
          executeTask3();
        }
        catch (const std::runtime_error& error)
        {
          std::cerr << error.what();
          return 2;
        }
        break;
      }

      case 4:
      {
        if (argc != 4)
        {
          std::cerr << "Incorrect count of arguments";
          return 1;
        }

        std::stringstream sizeStream(argv[3]);
        int count = 0;
        sizeStream >> count;

        if (!sizeStream.eof())
        {
          std::cerr << "Wrong size of array";
          return 1;
        }

        std::srand(time(0));
        try
        {
          executeTask4(argv[2], count);
        }
        catch (const std::invalid_argument& error)
        {
          std::cerr << error.what();
          return 1;
        }
        break;
      }

      default:
      {
        std::cerr << "Invalid task number";
        return 2;
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
