#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <iostream>
#include "shape.hpp"
#include "base-types.hpp"

class Circle: public Shape
{
public:
  Circle(double radius, const point_t &center);
  double getArea() const;
  rectangle_t getFrameRect()const;
  void move(const point_t &point);
  void move(double dx, double dy);
  void print (std::ostream& out) const;
private:
  double radius_;
  point_t center_;
};
#endif
