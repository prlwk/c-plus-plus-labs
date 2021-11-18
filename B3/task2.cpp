#include "tasks.hpp"

#include <iostream>
#include <iterator>

#include "factorial-container.hpp"

void executeTask2(std::ostream& output)
{
  FactorialContainer cont(10);
  std::copy(cont.begin(), cont.end(), std::ostream_iterator<size_t>(output, " "));
  output << "\n";

  std::copy(cont.rbegin(), cont.rend(), std::ostream_iterator<size_t>(output, " "));
  output << "\n";
}
