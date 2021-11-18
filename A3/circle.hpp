#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace molchanova
{
  class Circle: public Shape
  {
  public:
    Circle(double radius, const point_t &center);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &point) override;
    void move(double dx, double dy) override;
    void print(std::ostream &out) const override;
    void scale(double factor) override;
    point_t getCenter() const override;

  private:
    double radius_;
    point_t center_;
  };
}
#endif
