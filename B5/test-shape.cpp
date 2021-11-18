#include <sstream>
#include <string>
#include <cmath>
#include <boost/test/unit_test.hpp>

#include "shape.hpp"

BOOST_AUTO_TEST_SUITE(testShape)

const std::string str = " 3   (   5;   6   )  (9;9)       (  0;0)    ";
const std::string str2 = " 3   (   5;   6   )  (9;9)";
const std::string str3 = " 3   (   5;   6   )  (9;9)   (0;0) ferevrvgreve";
const std::string str4 = " frvirmivm 3   (   5;   6   )  (9;9)   (0;0)    ";

const Shape degenerateTriangle = {Shape::FigureType::TRIANGLE, {{5,6}, {5,6}, {5,6}}};
const Shape degenerateSquare = {Shape::FigureType::SQUARE, {{0,0}, {0,0}, {0,0}, {0,0}}};

struct Fixture
{
  Fixture()
  {
    triangle = {Shape::FigureType::TRIANGLE, {{5,6}, {9,9}, {0,0}}};
    rectangle = {Shape::FigureType::RECTANGLE, {{-5,0}, {5,0}, {-5,4}, {5,4}}};
    square = {Shape::FigureType::SQUARE, {{-5,0}, {5,0}, {5,10}, {-5,10}}};
    pentagon = {Shape::FigureType::PENTAGON, {{7,6}, {5,6}, {5,9}, {0,6}, {3,6}}};
  }

  Shape triangle, square, rectangle, pentagon;
};

BOOST_AUTO_TEST_CASE(testInputAndOutputOperator)
{
  Shape shape;
  std::istringstream stream;
  stream.str(str);
  stream >> shape;
  BOOST_CHECK(shape.points.size() == 3);
  BOOST_CHECK(shape.points[0].x == 5);
  BOOST_CHECK(shape.points[0].y == 6);
  BOOST_CHECK(shape.points[1].x == 9);
  BOOST_CHECK(shape.points[1].y == 9);
  BOOST_CHECK(shape.points[2].x == 0);
  BOOST_CHECK(shape.points[2].y == 0);
  BOOST_CHECK(shape.type == Shape::FigureType::TRIANGLE);

  std::ostringstream outputStream;
  outputStream << shape;
  BOOST_CHECK_EQUAL(outputStream.str(), "3 (5; 6) (9; 9) (0; 0) ");

  Shape shape2;
  std::istringstream stream2;
  stream2.str(str2);
  stream2 >> shape2;
  BOOST_CHECK(!stream2);

  Shape shape3;
  std::istringstream stream3;
  stream3.str(str3);
  stream3 >> shape3;
  BOOST_CHECK(!stream3);

  Shape shape4;
  std::istringstream stream4;
  stream4.str(str4);
  stream4 >> shape4;
  BOOST_CHECK(!stream4);
}

BOOST_FIXTURE_TEST_CASE(testIsTriangleAndIsSquareAndIsRectangle, Fixture)
{
  BOOST_CHECK(detail::isTriangle(triangle) == true);
  BOOST_CHECK(detail::isSquare(square) == true);
  BOOST_CHECK(detail::isRectangle(square) == true);

  BOOST_CHECK(detail::isSquare(rectangle) == false);
  BOOST_CHECK(detail::isTriangle(square) == false);
  BOOST_CHECK(detail::isRectangle(triangle) == false);
  BOOST_CHECK(detail::isTriangle(degenerateTriangle) == true);
  BOOST_CHECK(detail::isSquare(degenerateSquare) == true);
  BOOST_CHECK(detail::isRectangle(degenerateSquare) == true);

  BOOST_CHECK(detail::isPentagon(rectangle) == false);
  BOOST_CHECK(detail::isPentagon(square) == false);
  BOOST_CHECK(detail::isPentagon(triangle) == false);
  BOOST_CHECK(detail::isPentagon(pentagon) == true);
}

BOOST_FIXTURE_TEST_CASE(testGetFigureType, Fixture)
{
  BOOST_CHECK(detail::getFigureType(triangle) == Shape::FigureType::TRIANGLE);
  BOOST_CHECK(detail::getFigureType(square) == Shape::FigureType::SQUARE);
  BOOST_CHECK(detail::getFigureType(rectangle) == Shape::FigureType::RECTANGLE);
  BOOST_CHECK(detail::getFigureType(pentagon) == Shape::FigureType::PENTAGON);
}

BOOST_FIXTURE_TEST_CASE(testShapeComparator, Fixture)
{
  BOOST_CHECK(ShapeComparator()(triangle, square) == true);
  BOOST_CHECK(ShapeComparator()(triangle, rectangle) == true);
  BOOST_CHECK(ShapeComparator()(square, rectangle) == true);
  BOOST_CHECK(ShapeComparator()(square, triangle) == false);
  BOOST_CHECK(ShapeComparator()(rectangle, triangle) == false);
  BOOST_CHECK(ShapeComparator()(rectangle, square) == false);
}

BOOST_FIXTURE_TEST_CASE(testGetDistanceBetweenPoints, Fixture)
{
  BOOST_CHECK(detail::getSquaredDistance(triangle.points[0], triangle.points[1])
      == std::pow((triangle.points[1].x - triangle.points[0].x), 2) + std::pow((triangle.points[1].y - triangle.points[0].y), 2));
  BOOST_CHECK(detail::getSquaredDistance(rectangle.points[0], rectangle.points[1])
      == std::pow((rectangle.points[1].x - rectangle.points[0].x), 2) + std::pow((rectangle.points[1].y - rectangle.points[0].y), 2));
  BOOST_CHECK(detail::getSquaredDistance(square.points[0], square.points[1])
      == std::pow((square.points[1].x - square.points[0].x), 2) + std::pow((square.points[1].y - square.points[0].y), 2));
}

BOOST_AUTO_TEST_SUITE_END()
