#include <boost/test/unit_test.hpp>

#include "greater-for-data-struct.hpp"

const DataStruct firstDataStruct = {1, 2, "Nastia"};
const DataStruct secondDataStruct = {2, 2, "Nastia"};
const DataStruct thirdDataStruct = {1, 2, "Nastia1"};

BOOST_AUTO_TEST_SUITE(testGreaterForDataStruct)
BOOST_AUTO_TEST_CASE(testGreater)
{
  BOOST_CHECK(GreaterForDatastruct()(firstDataStruct, secondDataStruct) == true);
  BOOST_CHECK(GreaterForDatastruct()(secondDataStruct, firstDataStruct) == false);
  BOOST_CHECK(GreaterForDatastruct()(firstDataStruct, thirdDataStruct) == true);
  BOOST_CHECK(GreaterForDatastruct()(thirdDataStruct, firstDataStruct) == false);
  BOOST_CHECK(GreaterForDatastruct()(thirdDataStruct, secondDataStruct) == true);
  BOOST_CHECK(GreaterForDatastruct()(secondDataStruct, thirdDataStruct) == false);
}
BOOST_AUTO_TEST_SUITE_END()
