#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <iostream>

#include "shape.hpp"
#include "base-types.hpp"

class Rectangle: public Shape
{
public:
  Rectangle(double width, double height, const point_t &center);
  double getArea() const;
  rectangle_t getFrameRect()const;
  void move(const point_t &point);
  void move(double dx, double dy);
  void print (std::ostream& out) const;
private:
  double width_;
  double height_;
  point_t center_;
};
#endif
