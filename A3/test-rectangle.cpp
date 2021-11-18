#include <stdexcept>

#include <boost/test/unit_test.hpp>
#include "rectangle.hpp"

BOOST_AUTO_TEST_SUITE(RectangleTest)

const double EPSILON = 0.000001;
const double WIDTH = 3.3;
const double HEIGHT = 9.9;
const molchanova::point_t CENTER = {2.3, 4.5};
const double DX = 7.1;
const double DY = 2.5;
const double FACTOR = 2.0;
const molchanova::point_t NEWPOS = {11.1, 9.2};

BOOST_AUTO_TEST_CASE(CheckCorrectGettersWork)
{
  molchanova::Rectangle rectangle(WIDTH, HEIGHT, CENTER);
  BOOST_CHECK_CLOSE(rectangle.getArea(), WIDTH * HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getCenter().x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getCenter().y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, HEIGHT, EPSILON);
}

BOOST_AUTO_TEST_CASE(DataValidationAfterAxisOffset)
{
  molchanova::Rectangle rectangle(WIDTH, HEIGHT, CENTER);
  rectangle.move(DX, DY);
  BOOST_CHECK_CLOSE(rectangle.getArea(), WIDTH * HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(WIDTH, rectangle.getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(HEIGHT, rectangle.getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(CENTER.x + DX, rectangle.getFrameRect().pos.x, EPSILON);
  BOOST_CHECK_CLOSE(CENTER.y + DY, rectangle.getFrameRect().pos.y, EPSILON);
  BOOST_CHECK_CLOSE(CENTER.x + DX, rectangle.getCenter().x, EPSILON);
  BOOST_CHECK_CLOSE(CENTER.y + DY, rectangle.getCenter().y, EPSILON);
}

BOOST_AUTO_TEST_CASE(DataValidationAfterOffsetToPoint)
{
  molchanova::Rectangle rectangle(WIDTH, HEIGHT, CENTER);
  rectangle.move(NEWPOS);
  BOOST_CHECK_CLOSE(rectangle.getArea(), WIDTH * HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(WIDTH, rectangle.getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(HEIGHT, rectangle.getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(NEWPOS.x, rectangle.getFrameRect().pos.x, EPSILON);
  BOOST_CHECK_CLOSE(NEWPOS.y, rectangle.getFrameRect().pos.y, EPSILON);
  BOOST_CHECK_CLOSE(NEWPOS.x, rectangle.getCenter().x, EPSILON);
  BOOST_CHECK_CLOSE(NEWPOS.y, rectangle.getCenter().y, EPSILON);
}

BOOST_AUTO_TEST_CASE(DataValidationAfterScaling)
{
  molchanova::Rectangle rectangle(WIDTH, HEIGHT, CENTER);
  rectangle.scale(FACTOR);
  BOOST_CHECK_CLOSE(rectangle.getArea(), WIDTH * HEIGHT * FACTOR * FACTOR, EPSILON);
  BOOST_CHECK_CLOSE(WIDTH * FACTOR, rectangle.getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(HEIGHT * FACTOR, rectangle.getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(CENTER.x, rectangle.getFrameRect().pos.x, EPSILON);
  BOOST_CHECK_CLOSE(CENTER.y, rectangle.getFrameRect().pos.y, EPSILON);
  BOOST_CHECK_CLOSE(CENTER.x, rectangle.getCenter().x, EPSILON);
  BOOST_CHECK_CLOSE(CENTER.y, rectangle.getCenter().y, EPSILON);
}

BOOST_AUTO_TEST_CASE(InvalidArgumentsInConstructor)
{
  BOOST_CHECK_THROW(molchanova::Rectangle rectangle(-WIDTH, HEIGHT, CENTER), std::invalid_argument);
  BOOST_CHECK_THROW(molchanova::Rectangle rectangle(WIDTH, -HEIGHT, CENTER), std::invalid_argument);
  BOOST_CHECK_THROW(molchanova::Rectangle rectangle(0.0, HEIGHT, CENTER), std::invalid_argument);
  BOOST_CHECK_THROW(molchanova::Rectangle rectangle(WIDTH, 0.0, CENTER), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(InvalidFactor)
{
  molchanova::Rectangle rectangle(WIDTH, HEIGHT, CENTER);
  BOOST_CHECK_THROW(rectangle.scale(-FACTOR), std::invalid_argument);
  BOOST_CHECK_THROW(rectangle.scale(0.0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
