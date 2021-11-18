#include <stdexcept>
#include <sstream>
#include <boost/test/unit_test.hpp>

#include "data-struct.hpp"

const int invalidKey1 = 7;
const int invalidKey2 = -7;
const int validKey1 = -5;
const int validKey2 = 5;
const int validKey3 = 0;

const DataStruct firstDataStruct = {1, 2, "Nastia"};
const DataStruct secondDataStruct = {2, 2, "Nastia"};
const DataStruct thirdDataStruct = {1, 2, "Nastia1"};

const std::string str = "1, 2, Nastia";

BOOST_AUTO_TEST_SUITE(testDataStruct)

BOOST_AUTO_TEST_CASE(testIsValidKey)
{
  BOOST_CHECK(detail::isValidKey(invalidKey1) == false);
  BOOST_CHECK(detail::isValidKey(invalidKey2) == false);
  BOOST_CHECK(detail::isValidKey(validKey1) == true);
  BOOST_CHECK(detail::isValidKey(validKey2) == true);
  BOOST_CHECK(detail::isValidKey(validKey3) == true);
}

BOOST_AUTO_TEST_CASE(testInputOperator)
{
  DataStruct dataStruct;
  std::istringstream stream;
  stream.str(str);
  stream >> dataStruct;
  BOOST_CHECK(dataStruct.key1 == 1);
  BOOST_CHECK(dataStruct.key2 == 2);
  BOOST_CHECK(dataStruct.str == "Nastia");
}

BOOST_AUTO_TEST_CASE(testOutputOperator)
{
  std::ostringstream outputStream;
  outputStream << firstDataStruct;
  BOOST_CHECK_EQUAL(outputStream.str(), "1,2,Nastia");
  std::ostringstream outputStream2;
  outputStream2 << secondDataStruct;
  BOOST_CHECK_EQUAL(outputStream2.str(), "2,2,Nastia");
  std::ostringstream outputStream3;
  outputStream3 << thirdDataStruct;
  BOOST_CHECK_EQUAL(outputStream3.str(), "1,2,Nastia1");
}

BOOST_AUTO_TEST_SUITE_END()
