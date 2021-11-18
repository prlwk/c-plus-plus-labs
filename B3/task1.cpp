#include "tasks.hpp"

#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>

#include "phonebook-interface.hpp"
#include "parcer.hpp"

void executeTask1(std::istream& input, std::ostream& output)
{
  PhoneBookInterface interface;
  std::for_each(std::istream_iterator<CommandType>(input), std::istream_iterator<CommandType>(),
      [&](const CommandType& command)
      {
        command(interface, output);
      });
}
