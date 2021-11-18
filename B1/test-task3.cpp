#include <stdexcept>
#include <iostream>
#include <string>
#include <boost/test/unit_test.hpp>

#include "utility.hpp"
#include "structures-for-test.hpp"

const char *INPUT1 = "9 4 5 7 6 10 8 2 1 0";
const char *INPUT2 = "9 3 5 99 7 6 10 8 1 2 2 0";
const char *INPUT3 = "9 3 5 99 7 6 10 8 1 2 3 0";
const char *OUTPUT1 = "9 5 7 1 ";
const char *OUTPUT2 = "9 1 1 1 3 1 1 1 5 99 1 1 1 7 6 1 1 1 10 8 1 2 2 ";
const char *OUTPUT3 = "9 3 5 99 7 6 10 8 1 2 3 ";
const std::string invalidData1 = "1 2 3 4 5";
const std::string invalidData2 = "best array 0";
const std::string invalidData3 = "1 2 3 4 5.678 0";

BOOST_AUTO_TEST_SUITE(testTask3)

BOOST_FIXTURE_TEST_CASE(TestRightWorkingTask3WithInputEnding1, Redirecting)
{
  inputStream.str(INPUT1);
  executeTask3();
  restore();
  BOOST_CHECK_EQUAL(OUTPUT1, outputStream.str());
}

BOOST_FIXTURE_TEST_CASE(TestRightWorkingTask3WithInputEnding2, Redirecting)
{
  inputStream.str(INPUT2);
  executeTask3();
  restore();
  BOOST_CHECK_EQUAL(OUTPUT2, outputStream.str());
}

BOOST_FIXTURE_TEST_CASE(TestRightWorkingTask3WithInputEndingOtherNumber, Redirecting)
{
  inputStream.str(INPUT3);
  executeTask3();
  restore();
  BOOST_CHECK_EQUAL(OUTPUT3, outputStream.str());
}

BOOST_FIXTURE_TEST_CASE(TestWorkingTask1WithInvalidDataWithout0, Redirecting)
{
  inputStream.str(invalidData1);
  std::cout.rdbuf(oldCout);
  BOOST_CHECK_THROW(executeTask3(), std::runtime_error);
  restore();
}

BOOST_FIXTURE_TEST_CASE(TestWorkingTask1WithInvalidWordsData, Redirecting)
{
  inputStream.str(invalidData2);
  std::cout.rdbuf(oldCout);
  BOOST_CHECK_THROW(executeTask3(), std::runtime_error);
   restore();
}

BOOST_FIXTURE_TEST_CASE(TestWorkingTask1WithInvalidDoubleData, Redirecting)
{
  inputStream.str(invalidData3);
  std::cout.rdbuf(oldCout);
  BOOST_CHECK_THROW(executeTask3(), std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()
