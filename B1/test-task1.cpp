#include <stdexcept>
#include <string>
#include <boost/test/unit_test.hpp>
#include <boost/test/tools/output_test_stream.hpp>

#include "utility.hpp"
#include "structures-for-test.hpp"

const std::string INPUT = "9 0 2 -11\n";
const std::string OUTPUT_ASCENDING = "-11 0 2 9 \n-11 0 2 9 \n-11 0 2 9 ";
const std::string OUTPUT_DESCENDING= "9 2 0 -11 \n9 2 0 -11 \n9 2 0 -11 ";

BOOST_AUTO_TEST_SUITE(testTask1)

BOOST_FIXTURE_TEST_CASE(TestRightWorkingTask1WithAscending, Redirecting)
{
  inputStream.str(INPUT);
  executeTask1("ascending");
  restore();
  BOOST_CHECK_EQUAL(OUTPUT_ASCENDING, outputStream.str());
}

BOOST_FIXTURE_TEST_CASE(TestRightWorkingTask1WithDescending, Redirecting)
{
  inputStream.str(INPUT);
  executeTask1("descending");
  restore();
  BOOST_CHECK_EQUAL(OUTPUT_DESCENDING, outputStream.str());
}

BOOST_FIXTURE_TEST_CASE(TestWorkingTask1WithInvalidData, Redirecting)
{
  const char *invalidData1 = "1 2 a 4 5";
  const char *invalidData2 = "best array";
  const char *invalidData3 = "1 2 3 4 5.678";
  inputStream.str(invalidData1);
  std::cout.rdbuf(oldCout);
  BOOST_CHECK_THROW(executeTask1("ascending"), std::runtime_error);
  inputStream.str(invalidData2);
  std::cout.rdbuf(oldCout);
  BOOST_CHECK_THROW(executeTask1("ascending"), std::runtime_error);
  inputStream.str(invalidData3);
  std::cout.rdbuf(oldCout);
  BOOST_CHECK_THROW(executeTask1("ascending"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(TestInvalidOrder)
{
  BOOST_CHECK_THROW(executeTask1(nullptr), std::invalid_argument);
  BOOST_CHECK_THROW(executeTask1("Other order"), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
