#include <stdexcept>
#include <string>
#include <algorithm>
#include <sstream>
#include <boost/test/unit_test.hpp>

#include "utility.hpp"
#include "structures-for-test.hpp"
#include "policy.hpp"

BOOST_AUTO_TEST_SUITE(testTask4)

const size_t SIZE = 10;

BOOST_AUTO_TEST_CASE(TeestInvalidSize)
{
  BOOST_CHECK_THROW(executeTask4("ascending", 0), std::invalid_argument);
}
BOOST_FIXTURE_TEST_CASE(TeestRightWorkingTask4, Redirecting)
{
  executeTask4("ascending", SIZE);
  std::string output = outputStream.str();
  std::vector <double> unsortedArray;
  std::vector <double> sortedArray;
  double tmpNumber = 0.0;
  std::stringstream str;
  for(size_t i = 0; i < SIZE; i++)
  {
    str << output;
    str >> tmpNumber;
    unsortedArray.push_back(tmpNumber);
    str.clear();
  }
  for(size_t i = 0; i < SIZE; i++)
  {
    str << output;
    str >> tmpNumber;
    sortedArray.push_back(tmpNumber);
    str.clear();
  }
  restore();
  for(size_t i = 0; i < SIZE; i++)
  {
    BOOST_CHECK(sortedArray[i] < 1.0);
    BOOST_CHECK(sortedArray[i] > -1.0);
  }
  details::bubbleSort<BracketsPolicy>(unsortedArray, details::SortType::ASCENDING);
  BOOST_CHECK(unsortedArray == sortedArray);
}

BOOST_AUTO_TEST_SUITE_END()
