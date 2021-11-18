#include <memory>
#include <cmath>
#include <stdexcept>

#include <boost/test/unit_test.hpp>
#include "composite-shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"

BOOST_AUTO_TEST_SUITE(CompositeShapeTest)

const double EPSILON = 0.000001;
const double RADIUS = 2.5;
const molchanova::point_t CIRCLE_CENTER = {2.5, 2.5};
const double WIDTH = 5.7;
const double HEIGHT = 7.5;
const molchanova::point_t RECTANGLE_CENTER = {10.5, 2.1};
const molchanova::point_t NEWPOS = {5.0, 8.0};
const double DX = -0.7;
const double DY = 3.0;
const double FACTOR = 2.0;
const size_t INDEX = 5;
const size_t SIZE = 2;

struct fixture
{
  fixture() :
  shape0(std::make_shared <molchanova::Rectangle>(WIDTH, HEIGHT, RECTANGLE_CENTER)),
  shape1(std::make_shared <molchanova::Circle>(RADIUS, CIRCLE_CENTER))
  {
    shapes.add(shape0);
    shapes.add(shape1);
  }

  std::shared_ptr <molchanova::Shape> shape0;
  std::shared_ptr <molchanova::Shape> shape1;
  molchanova::CompositeShape shapes;
};

BOOST_FIXTURE_TEST_CASE(CheckCorrectGettersWork, fixture)
{
  BOOST_CHECK_CLOSE(shapes.getArea(), WIDTH * HEIGHT + M_PI * RADIUS * RADIUS, EPSILON);
  const double maxY = std::max(CIRCLE_CENTER.y + RADIUS, RECTANGLE_CENTER.y + HEIGHT / 2);
  const double minY = std::min(CIRCLE_CENTER.y - RADIUS, RECTANGLE_CENTER.y - HEIGHT / 2);
  const double maxX = std::max(CIRCLE_CENTER.x + RADIUS, RECTANGLE_CENTER.x + WIDTH / 2);
  const double minX = std::min(CIRCLE_CENTER.x - RADIUS, RECTANGLE_CENTER.x - WIDTH / 2);
  BOOST_CHECK_CLOSE(shapes.getCenter().x, (maxX + minX) / 2, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getCenter().y, (maxY + minY) / 2, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().pos.x, (maxX + minX) / 2, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().pos.y, (maxY + minY) / 2, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().width, (maxX - shapes.getCenter().x) * 2, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().height, (maxY - shapes.getCenter().y) * 2, EPSILON);
  BOOST_CHECK_EQUAL(shapes.getSize(), SIZE);
}

BOOST_FIXTURE_TEST_CASE(DataValidationAfterAxisOffset, fixture)
{
  const molchanova::point_t tempCenter = shapes.getCenter();
  const molchanova::rectangle_t tempRect = shapes.getFrameRect();
  const double tempArea = shapes.getArea();
  shapes.move(DX, DY);
  BOOST_CHECK_CLOSE(shapes.getCenter().x, tempCenter.x + DX, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getCenter().y, tempCenter.y + DY, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().pos.x, tempCenter.x + DX, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().pos.y, tempCenter.y + DY, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().width, tempRect.width, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().height, tempRect.height, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getArea(), tempArea, EPSILON);
  BOOST_CHECK_EQUAL(shapes.getSize(), SIZE);
  BOOST_CHECK(shapes[0] == shape0);
  BOOST_CHECK(shapes[1] == shape1);
}

BOOST_FIXTURE_TEST_CASE(DataValidationAfterOffsetToPoint, fixture)
{
  const molchanova::rectangle_t tempRect = shapes.getFrameRect();
  const double tempArea = shapes.getArea();
  shapes.move(NEWPOS);
  BOOST_CHECK_CLOSE(shapes.getCenter().x, NEWPOS.x, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getCenter().y, NEWPOS.y, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().pos.x, NEWPOS.x, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().pos.y, NEWPOS.y, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().width, tempRect.width, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().height, tempRect.height, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getArea(), tempArea, EPSILON);
  BOOST_CHECK_EQUAL(shapes.getSize(), SIZE);
  BOOST_CHECK(shapes[0] == shape0);
  BOOST_CHECK(shapes[1] == shape1);
}

BOOST_FIXTURE_TEST_CASE(DataValidationAfterScaling, fixture)
{
  const molchanova::rectangle_t tempRect = shapes.getFrameRect();
  const double tempArea = shapes.getArea();
  shapes.scale(FACTOR);
  BOOST_CHECK_CLOSE(shapes.getArea(), tempArea * FACTOR * FACTOR, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().pos.y, tempRect.pos.y, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().pos.x, tempRect.pos.x, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().width, tempRect.width * FACTOR, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().height, tempRect.height * FACTOR, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getCenter().y, tempRect.pos.y, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getCenter().x, tempRect.pos.x, EPSILON);
  BOOST_CHECK_EQUAL(shapes.getSize(), SIZE);
  BOOST_CHECK(shapes[0] == shape0);
  BOOST_CHECK(shapes[1] == shape1);
}

BOOST_FIXTURE_TEST_CASE(InvalidFactor, fixture)
{
  BOOST_CHECK_THROW(shapes.scale(-FACTOR), std::invalid_argument);
  BOOST_CHECK_THROW(shapes.scale(0.0), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(InvalidIndex, fixture)
{
  BOOST_CHECK_THROW(shapes[INDEX], std::out_of_range);
  BOOST_CHECK_THROW(shapes.remove(INDEX), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(CheckEmptyComposition)
{
  molchanova::CompositeShape shapes;
  BOOST_CHECK_THROW(shapes.getFrameRect(), std::logic_error);
  BOOST_CHECK_THROW(shapes.getCenter(), std::logic_error);
  BOOST_CHECK_THROW(shapes.scale(FACTOR), std::logic_error);
  BOOST_CHECK_THROW(shapes.move(DX, DY), std::logic_error);
  BOOST_CHECK_THROW(shapes.move(NEWPOS), std::logic_error);
  BOOST_CHECK_THROW(shapes.remove(INDEX), std::logic_error);
  BOOST_CHECK_EQUAL(shapes.getSize(), 0);
  BOOST_CHECK_THROW(shapes[INDEX], std::logic_error);

}

BOOST_FIXTURE_TEST_CASE(CheckingRightWorkingIndexing, fixture)
{
  molchanova::Circle crcl (RADIUS, CIRCLE_CENTER);
  molchanova::Rectangle rctngl (WIDTH, HEIGHT, RECTANGLE_CENTER);
  BOOST_CHECK_CLOSE(shapes[0]->getArea(), rctngl.getArea(), EPSILON);
  BOOST_CHECK_CLOSE(shapes[1]->getArea(), crcl.getArea(), EPSILON);
  BOOST_CHECK_CLOSE(shapes[0]->getCenter().x, rctngl.getCenter().x, EPSILON);
  BOOST_CHECK_CLOSE(shapes[0]->getCenter().y, rctngl.getCenter().y, EPSILON);
  BOOST_CHECK_CLOSE(shapes[1]->getCenter().x, crcl.getCenter().x, EPSILON);
  BOOST_CHECK_CLOSE(shapes[1]->getCenter().y, crcl.getCenter().y, EPSILON);
  BOOST_CHECK_CLOSE(shapes[0]->getFrameRect().height, rctngl.getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(shapes[0]->getFrameRect().width, rctngl.getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(shapes[1]->getFrameRect().height, crcl.getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(shapes[1]->getFrameRect().width, crcl.getFrameRect().width, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(CheckNewShapeBeforeAdding, fixture)
{
  molchanova::CompositeShape emptyShapes;
  std::shared_ptr< molchanova::Shape > circle = std::make_shared< molchanova::Circle >(RADIUS, CIRCLE_CENTER);
  BOOST_CHECK_THROW(emptyShapes.add(nullptr), std::logic_error);
  std::shared_ptr< molchanova::CompositeShape > csPtr = std::make_shared< molchanova::CompositeShape >();
  BOOST_CHECK_THROW(csPtr->add(csPtr), std::logic_error);
  BOOST_CHECK_THROW(shapes.add(shape0), std::logic_error);
  shapes.add(circle);
  BOOST_CHECK_EQUAL(shapes.getSize(), SIZE + 1);
  BOOST_CHECK(shapes[0] == shape0);
  BOOST_CHECK(shapes[1] == shape1);
  BOOST_CHECK(shapes[2] == circle);
}

BOOST_FIXTURE_TEST_CASE(TestCopyConstructur, fixture)
{
  molchanova::CompositeShape compositeShape(shapes);
  BOOST_CHECK(shapes[0] == compositeShape[0]);
  BOOST_CHECK(shapes[1] == compositeShape[1]);
  BOOST_CHECK(shapes.getArea() == compositeShape.getArea());
  BOOST_CHECK(shapes.getSize() == compositeShape.getSize());
  BOOST_CHECK_CLOSE(shapes.getFrameRect().width, compositeShape.getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().height, compositeShape.getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getCenter().x, compositeShape.getCenter().x, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getCenter().y, compositeShape.getCenter().y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(TestOperatorCopy, fixture)
{
  molchanova::CompositeShape compositeShape = shapes;
  BOOST_CHECK(shapes[0] == compositeShape[0]);
  BOOST_CHECK(shapes[1] == compositeShape[1]);
  BOOST_CHECK(shapes.getArea() == compositeShape.getArea());
  BOOST_CHECK(shapes.getSize() == compositeShape.getSize());
  BOOST_CHECK_CLOSE(shapes.getFrameRect().width, compositeShape.getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().height, compositeShape.getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getCenter().x, compositeShape.getCenter().x, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getCenter().y, compositeShape.getCenter().y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(TestRemoving, fixture)
{
  molchanova::CompositeShape compositeShape = shapes;
  shapes.remove(0);
  BOOST_CHECK(shapes[0] == compositeShape[1]);
  BOOST_CHECK_CLOSE(shapes.getArea(), compositeShape[1]->getArea(), EPSILON);
  BOOST_CHECK(shapes.getSize() == compositeShape.getSize() - 1);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().width, compositeShape[1]->getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().height, compositeShape[1]->getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getCenter().x, compositeShape[1]->getCenter().x, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getCenter().y, compositeShape[1]->getCenter().y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(TestMovementConstructur, fixture)
{
  molchanova::CompositeShape compositeShapes(std::move(shapes));
  BOOST_CHECK_EQUAL(shapes.getSize(), 0);
  BOOST_CHECK_EQUAL(compositeShapes.getSize(), SIZE);
  BOOST_CHECK(compositeShapes[0] == shape0);
  BOOST_CHECK(compositeShapes[1] == shape1);
  BOOST_CHECK(shape0->getArea() + shape1->getArea() == compositeShapes.getArea());
}

BOOST_FIXTURE_TEST_CASE(TestOperatorMovement, fixture)
{
  molchanova::CompositeShape compositeShapes = std::move(shapes);
  BOOST_CHECK_EQUAL(shapes.getSize(), 0);
  BOOST_CHECK_EQUAL(compositeShapes.getSize(), SIZE);
  BOOST_CHECK(compositeShapes[0] == shape0);
  BOOST_CHECK(compositeShapes[1] == shape1);
  BOOST_CHECK(shape0->getArea() + shape1->getArea() == compositeShapes.getArea());
}

BOOST_AUTO_TEST_SUITE_END()
