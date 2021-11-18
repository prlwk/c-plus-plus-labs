#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>

struct point_t;
struct rectangle_t;

class Shape
{
public:
  virtual ~Shape() = default;
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(const point_t &point) = 0;
  virtual void move(double x, double y) = 0;
  virtual void print(std::ostream& out) const = 0;
};
#endif
