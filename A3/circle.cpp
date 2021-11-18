#include "circle.hpp"

#include <cmath>
#include <stdexcept>

molchanova::Circle::Circle(double radius, const point_t &center) :
  radius_(radius),
  center_(center)
{
  if (radius <= 0.0)
  {
    throw std::invalid_argument("Radius must be > 0");
  }
}

double molchanova::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

molchanova::rectangle_t molchanova::Circle::getFrameRect() const
{
  return {radius_ * 2, radius_ * 2, center_};
}

void molchanova::Circle::move(const point_t &point)
{
  center_ = point;
}

void molchanova::Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void molchanova::Circle::print(std::ostream &out) const
{
  out << "radius: " << radius_ << "\n"
      << "Center coordinates: (" << center_.x << "; " << center_.y << ")" << "\n";
}

void molchanova::Circle::scale(double factor)
{
  if (factor <= 0.0)
  {
    throw std::invalid_argument("Factor must be > 0");
  }
  radius_ *= factor;
}

molchanova::point_t molchanova::Circle::getCenter() const
{
  return center_;
}
