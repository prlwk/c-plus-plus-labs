#include "rectangle.hpp"

#include <stdexcept>

molchanova::Rectangle::Rectangle(double width, double height, const point_t &center) :
  width_(width),
  height_(height),
  center_(center)
{
  if (height <= 0.0)
  {
    throw std::invalid_argument("Height must be > 0");
  }
  if (width <= 0.0)
  {
    throw std::invalid_argument("Width must be > 0");
  }
}

double molchanova::Rectangle::getArea() const
{
  return width_ * height_;
}

molchanova::rectangle_t molchanova::Rectangle::getFrameRect() const
{
  return {width_, height_, center_};
}

void molchanova::Rectangle::move(const point_t &point)
{
  center_ = point;
}

void molchanova::Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void molchanova::Rectangle::print(std::ostream &out) const
{
  out << "width: " << width_ << "\n"
      << "height: " << height_ << "\n"
      << "Center coordinates: (" << center_.x << "; " << center_.y << ")" << "\n";
}

void molchanova::Rectangle::scale(double factor)
{
  if (factor <= 0.0)
  {
    throw std::invalid_argument("Factor must be > 0");
  }
  width_ *= factor;
  height_ *= factor;
}

molchanova::point_t molchanova::Rectangle::getCenter() const
{
  return center_;
}
