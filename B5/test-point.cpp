#include <sstream>
#include <string>
#include <boost/test/unit_test.hpp>

#include "point.hpp"

BOOST_AUTO_TEST_SUITE(testPoint)

const std::string str = "    (   5;   6   )   ";
const std::string str2 = "(-5555    ;   0   )   ";
const std::string str3 = "       5;   6   )   ";
const std::string str4 = "    (   ;   6   )   ";
const std::string str5 = "    (   5,   6   )   ";

const Point point = {2, 3};
const Point point2 = {-88, 0};

BOOST_AUTO_TEST_CASE(testInputOperator)
{
  Point point;
  std::istringstream stream;
  stream.str(str);
  stream >> point;
  BOOST_CHECK(point.x == 5);
  BOOST_CHECK(point.y == 6);

  Point point2;
  std::istringstream stream2;
  stream2.str(str2);
  stream2 >> point2;
  BOOST_CHECK(point2.x == -5555);
  BOOST_CHECK(point2.y == 0);

  Point point3;
  std::istringstream stream3;
  stream3.str(str3);
  stream3 >> point3;
  BOOST_CHECK(!stream3);

  Point point4;
  std::istringstream stream4;
  stream4.str(str4);
  stream4 >> point4;
  BOOST_CHECK(!stream4);

  Point point5;
  std::istringstream stream5;
  stream5.str(str5);
  stream5 >> point5;
  BOOST_CHECK(!stream5);
}

BOOST_AUTO_TEST_CASE(testOutputOperator)
{
  std::ostringstream stream;
  stream << point;
  BOOST_CHECK_EQUAL(stream.str(), "(2; 3)");
  std::ostringstream stream2;
  stream2 << point2;
  BOOST_CHECK_EQUAL(stream2.str(), "(-88; 0)");
}
BOOST_AUTO_TEST_SUITE_END()
