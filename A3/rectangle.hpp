#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace molchanova
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(double width, double height, const point_t &center);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &point) override;
    void move(double dx, double dy) override;
    void print(std::ostream &out) const override;
    void scale(double factor) override;
    point_t getCenter() const override;

  private:
    double width_;
    double height_;
    point_t center_;
  };
}
#endif
