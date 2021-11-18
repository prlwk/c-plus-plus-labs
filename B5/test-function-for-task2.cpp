#include <boost/test/unit_test.hpp>

#include "functions-for-task2.hpp"

BOOST_AUTO_TEST_SUITE(testFunctionForTask2)

const std::string str = " 3   (   5;   6   )  (9;9)       (  0;0)    ";
const std::string str2 = "     4 (-5    ;   0   )   (5;   0) (  5;  4) (  -5;4    )   ";
const std::string str3 = "     4 (-5    ;   0   )   (5;   0) (  5   ;  10 ) (  -5;10    )   ";
const std::string str4 = " 5   (   5;   6   )  (5;60)       (  85;6)  (45;9) (1;2)  ";


struct Fixture
{
  Fixture()
  {
    triangle = {Shape::FigureType::TRIANGLE, {{5,6}, {9,9}, {0,0}}};
    rectangle = {Shape::FigureType::RECTANGLE, {{-5,0}, {5,0}, {-5,4}, {5,4}}};
    square = {Shape::FigureType::SQUARE, {{-5,0}, {5,0}, {5,10}, {-5,10}}};
    pentagon = {Shape::FigureType::PENTAGON, {{5,6}, {5,60}, {85,6}, {45,9}, {1,2}}};
    shapes = {rectangle, triangle, square, pentagon};
  }

  Shape triangle, square, rectangle, pentagon;
  Shapes shapes;
};

BOOST_FIXTURE_TEST_CASE(testCountShapes, Fixture)
{
  BOOST_CHECK(countShapes(shapes, Shape::FigureType::TRIANGLE) == 1);
  BOOST_CHECK(countShapes(shapes, Shape::FigureType::SQUARE) == 1);
  BOOST_CHECK(countShapes(shapes, Shape::FigureType::RECTANGLE) == 2);
  BOOST_CHECK(countShapes(shapes, Shape::FigureType::PENTAGON) == 1);
  BOOST_CHECK(countShapes(shapes, Shape::FigureType::OTHER) == 0);
}

BOOST_FIXTURE_TEST_CASE(testCountVertices, Fixture)
{
  BOOST_CHECK(countVertices(shapes)
      == triangle.points.size() + square.points.size() + rectangle.points.size() + pentagon.points.size());
}

BOOST_FIXTURE_TEST_CASE(testDeletePentagons, Fixture)
{
  size_t countPentagons = 0;
  for (size_t i = 0; i < shapes.size(); i++)
  {
    if (shapes[i].type == Shape::FigureType::PENTAGON)
    {
      countPentagons++;
    }
  }
  BOOST_CHECK(countPentagons == 1);
  deletePentagons(shapes);
  countPentagons = 0;
  for (size_t i = 0; i < shapes.size(); i++)
  {
    if (shapes[i].type == Shape::FigureType::PENTAGON)
    {
      countPentagons++;
    }
  }
  BOOST_CHECK(countPentagons == 0);
}

BOOST_FIXTURE_TEST_CASE(testCreateVectorOfPoints, Fixture)
{
  std::vector<Point> points = createVectorOfPoint(shapes);
  BOOST_CHECK(points.size() == shapes.size());
  BOOST_CHECK(points[0].x == -5);
  BOOST_CHECK(points[0].y == 0);
  BOOST_CHECK(points[3].x == 5);
  BOOST_CHECK(points[3].y == 6);
}

BOOST_AUTO_TEST_SUITE_END()
