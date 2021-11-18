#include "shape.hpp"

#include <algorithm>
#include <iterator>

#include "reading-utilities.hpp"

const char SEPARATOR = ' ';
const size_t POINTS_COUNT_OF_TRIANGLE = 3;
const size_t POINTS_COUNT_OF_RECTANGLE = 4;
const size_t POINTS_COUNT_OF_PENTAGON = 5;

std::istream& operator >>(std::istream& input, Shape& shape)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }

  GuardIstream guard(input);
  input >> std::noskipws;

  size_t pointsCount = 0;
  input >> std::ws >> pointsCount;
  if (!input)
  {
    return input;
  }
  std::vector<Point> tempShape;
  for (size_t i = 0; i < pointsCount; i++)
  {
    Point tempPoint;
    input >> tempPoint;
    if (!input)
    {
      return input;
    }
    tempShape.push_back(tempPoint);
  }

  input >> checkEnd;
  if (!input)
  {
    return input;
  }

  shape.points = std::move(tempShape);
  shape.type = detail::getFigureType(shape);
  return input;
}

std::ostream &operator<<(std::ostream &output, const Shape &shape)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  output << shape.points.size() << SEPARATOR;
  std::copy(shape.points.begin(), shape.points.end(), std::ostream_iterator<Point>(output, " "));
  return output;
}

bool detail::isTriangle(const Shape &shape)
{
  return shape.points.size() == POINTS_COUNT_OF_TRIANGLE;
}

bool detail::isSquare(const Shape &shape)
{
  if (detail::isRectangle(shape))
  {
    const size_t firstSideSquared = detail::getSquaredDistance(shape.points[0], shape.points[1]);
    const size_t secondSideSquared = detail::getSquaredDistance(shape.points[1], shape.points[2]);
    return firstSideSquared == secondSideSquared;
  }
  return false;
}

bool detail::isRectangle(const Shape &shape)
{
  if (shape.points.size() != POINTS_COUNT_OF_RECTANGLE)
  {
    return false;
  }

  const size_t firstSideSquared = detail::getSquaredDistance(shape.points[0], shape.points[1]);
  const size_t secondSideSquared = detail::getSquaredDistance(shape.points[1], shape.points[2]);
  const size_t thirdSideSquared = detail::getSquaredDistance(shape.points[2], shape.points[3]);
  const size_t fourthSideSquared = detail::getSquaredDistance(shape.points[3], shape.points[0]);
  const size_t firstDiagonalSquared = detail::getSquaredDistance(shape.points[0], shape.points[2]);
  const size_t secondDiagonalSquared = detail::getSquaredDistance(shape.points[1], shape.points[3]);

  return ((firstSideSquared == thirdSideSquared)
      && (secondSideSquared == fourthSideSquared) && (firstDiagonalSquared == secondDiagonalSquared));
}

bool detail::isPentagon(const Shape &shape)
{
  return shape.points.size() == POINTS_COUNT_OF_PENTAGON;
}

size_t detail::getSquaredDistance(const Point &firstPoint, const Point &secondPoint)
{
  return (secondPoint.x - firstPoint.x) * (secondPoint.x - firstPoint.x)
      + (secondPoint.y - firstPoint.y) * (secondPoint.y - firstPoint.y);
}

Shape::FigureType detail::getFigureType(const Shape &shape)
{
  if (detail::isTriangle(shape))
  {
    return Shape::FigureType::TRIANGLE;
  }
  if (detail::isSquare(shape))
  {
    return Shape::FigureType::SQUARE;
  }
  if (detail::isRectangle(shape))
  {
    return Shape::FigureType::RECTANGLE;
  }
  if (detail::isPentagon(shape))
  {
    return Shape::FigureType::PENTAGON;
  }
  return Shape::FigureType::OTHER;
}

bool ShapeComparator::operator()(const Shape& firstShape, const Shape& secondShape)
{
  return firstShape.type < secondShape.type;
}
