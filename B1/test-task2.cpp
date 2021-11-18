#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>
#include <boost/test/unit_test.hpp>

#include "utility.hpp"

BOOST_AUTO_TEST_SUITE(testTask2)

  struct RedirectingCout
  {
    RedirectingCout() :
      oldCout(std::cout.rdbuf(outputStream.rdbuf()))
    {}

    void restore()
    {
      std::cout.rdbuf(oldCout);
    }

    std::streambuf* oldCout;
    std::ostringstream outputStream;
  };

BOOST_FIXTURE_TEST_CASE(TestRightWorkingTask2, RedirectingCout)
{
  const std::string info = "Hello";
  std::ofstream out;
  out.open("input.txt");
  out << info;
  out.close();
  executeTask2("input.txt");
  restore();
  BOOST_CHECK_EQUAL(outputStream.str(), info);
}

BOOST_AUTO_TEST_CASE(TestWorkingTask2WithInvalidFilesName)
{
  const char *nameFile = "non-existent file";
  BOOST_CHECK_THROW(executeTask2(nameFile), std::runtime_error);
  BOOST_CHECK_THROW(executeTask2(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
