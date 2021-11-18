#include <cmath>
#include <stdexcept>

#include <boost/test/unit_test.hpp>
#include "circle.hpp"

BOOST_AUTO_TEST_SUITE(CircleTest)

const double EPSILON = 0.000001;
const double RADIUS = 3.3;
const molchanova::point_t CENTER = {2.3, 4.5};
const double DX = 7.1;
const double DY = 2.5;
const double FACTOR = 2.0;
const molchanova::point_t NEWPOS = {11.1, 9.2};

BOOST_AUTO_TEST_CASE(CheckCorrectGettersWork)
{
  molchanova::Circle circle(RADIUS, CENTER);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI * RADIUS * RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circle.getCenter().x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(circle.getCenter().y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, RADIUS * 2, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, RADIUS * 2, EPSILON);
}

BOOST_AUTO_TEST_CASE(DataValidationAfterAxisOffset)
{
  molchanova::Circle circle(RADIUS, CENTER);
  circle.move(DX, DY);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI * RADIUS * RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(RADIUS, circle.getFrameRect().width / 2, EPSILON);
  BOOST_CHECK_CLOSE(RADIUS, circle.getFrameRect().height / 2, EPSILON);
  BOOST_CHECK_CLOSE(CENTER.x + DX, circle.getFrameRect().pos.x, EPSILON);
  BOOST_CHECK_CLOSE(CENTER.y + DY, circle.getFrameRect().pos.y, EPSILON);
  BOOST_CHECK_CLOSE(CENTER.x + DX, circle.getCenter().x, EPSILON);
  BOOST_CHECK_CLOSE(CENTER.y + DY, circle.getCenter().y, EPSILON);
}

BOOST_AUTO_TEST_CASE(DataValidationAfterOffsetToPoint)
{
  molchanova::Circle circle(RADIUS, CENTER);
  circle.move(NEWPOS);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI * RADIUS * RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(RADIUS, circle.getFrameRect().width / 2, EPSILON);
  BOOST_CHECK_CLOSE(RADIUS, circle.getFrameRect().height / 2, EPSILON);
  BOOST_CHECK_CLOSE(NEWPOS.x, circle.getFrameRect().pos.x, EPSILON);
  BOOST_CHECK_CLOSE(NEWPOS.y, circle.getFrameRect().pos.y, EPSILON);
  BOOST_CHECK_CLOSE(NEWPOS.x, circle.getCenter().x, EPSILON);
  BOOST_CHECK_CLOSE(NEWPOS.y, circle.getCenter().y, EPSILON);
}

BOOST_AUTO_TEST_CASE(DataValidationAfterScaling)
{
  molchanova::Circle circle(RADIUS, CENTER);
  circle.scale(FACTOR);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI * RADIUS * RADIUS * FACTOR * FACTOR, EPSILON);
  BOOST_CHECK_CLOSE(RADIUS * FACTOR, circle.getFrameRect().width / 2, EPSILON);
  BOOST_CHECK_CLOSE(RADIUS * FACTOR, circle.getFrameRect().height / 2, EPSILON);
  BOOST_CHECK_CLOSE(CENTER.x, circle.getFrameRect().pos.x, EPSILON);
  BOOST_CHECK_CLOSE(CENTER.y, circle.getFrameRect().pos.y, EPSILON);
  BOOST_CHECK_CLOSE(CENTER.x, circle.getCenter().x, EPSILON);
  BOOST_CHECK_CLOSE(CENTER.y, circle.getCenter().y, EPSILON);
}

BOOST_AUTO_TEST_CASE(InvalidArgumentInConstructor)
{
  BOOST_CHECK_THROW(molchanova::Circle circle(-RADIUS, CENTER), std::invalid_argument);
  BOOST_CHECK_THROW(molchanova::Circle circle(0.0, CENTER), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(InvalidFactor)
{
  molchanova::Circle circle(RADIUS, CENTER);
  BOOST_CHECK_THROW(circle.scale(-FACTOR), std::invalid_argument);
  BOOST_CHECK_THROW(circle.scale(0.0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
