#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <vector>
#include <iosfwd>

#include "point.hpp"

struct Shape
{
  enum FigureType
  {
    TRIANGLE,
    SQUARE,
    RECTANGLE,
    PENTAGON,
    OTHER
  };

  FigureType type;
  std::vector<Point> points;
};
using Shapes = std::vector<Shape>;

std::istream& operator >>(std::istream& input, Shape& shape);
std::ostream& operator <<(std::ostream& output, const Shape& shape);

namespace detail
{
  Shape::FigureType getFigureType(const Shape& shape);
  size_t getSquaredDistance(const Point& firstPoint, const Point& secondPoint);
  bool isTriangle(const Shape &shape);
  bool isSquare(const Shape &shape);
  bool isRectangle(const Shape &shape);
  bool isPentagon(const Shape &shape);
}

struct ShapeComparator
{
  bool operator()(const Shape& firstShape, const Shape& secondShape);
};

#endif
