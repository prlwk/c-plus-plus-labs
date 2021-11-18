#include "rectangle.hpp"

#include <cassert>

Rectangle::Rectangle(double width, double height, const point_t& center) :
  width_(width),
  height_(height),
  center_(center)
{
  assert((width_ > 0.0) && (height > 0.0));
}

double Rectangle:: getArea()const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect()const
{
  return {height_, width_, center_};
}

void Rectangle::move(const point_t &point)
{
  center_ = point;
}

void Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Rectangle::print(std::ostream& out) const
{
  out << "width: " << width_ << "\n"
      << "height: " << height_ << "\n"
      << "Center coordinates: (" << center_.x << "; " << center_.y << ")" << "\n";
}
