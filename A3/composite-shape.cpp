#include "composite-shape.hpp"

#include <memory>
#include <stdexcept>

#include "base-types.hpp"

molchanova::CompositeShape::CompositeShape() :
  count_(0)
{}

double molchanova::CompositeShape::getArea() const
{
  double tempArea = 0.0;
  for (size_t i = 0; i < count_; i++)
  {
    tempArea += arrayShapes_[i]->getArea();
  }
  return tempArea;
}

molchanova::rectangle_t molchanova::CompositeShape::getFrameRect() const
{
  if (count_ == 0)
  {
    throw std::logic_error("Shape composition is empty");
  }
  double maxX = arrayShapes_[0]->getCenter().x + arrayShapes_[0]->getFrameRect().width / 2.0;
  double maxY = arrayShapes_[0]->getCenter().y + arrayShapes_[0]->getFrameRect().height / 2.0;
  double minX = arrayShapes_[0]->getCenter().x - arrayShapes_[0]->getFrameRect().width / 2.0;
  double minY = arrayShapes_[0]->getCenter().y - arrayShapes_[0]->getFrameRect().height / 2.0;
  for (size_t i = 1; i < count_; i++)
  {
    maxX = std::max(arrayShapes_[i]->getCenter().x +
                     arrayShapes_[i]->getFrameRect().width / 2.0, maxX);
    minX = std::min(arrayShapes_[i]->getCenter().x -
                     arrayShapes_[i]->getFrameRect().width / 2.0, minX);
    maxY = std::max(arrayShapes_[i]->getCenter().y +
                     arrayShapes_[i]->getFrameRect().height / 2.0, maxY);
    minY = std::min(arrayShapes_[i]->getCenter().y -
                     arrayShapes_[i]->getFrameRect().height / 2.0, minY);
  }
  return {(maxX - minX), (maxY - minY), {(maxX + minX) / 2.0, (maxY + minY) / 2.0}};
}

void molchanova::CompositeShape::move(const molchanova::point_t &point)
{
  const rectangle_t tmpRectangle = getFrameRect();
  move(point.x - tmpRectangle.pos.x, point.y - tmpRectangle.pos.y);
}

void molchanova::CompositeShape::move(double dx, double dy)
{
  if (count_ == 0)
  {
    throw std::logic_error("Shape composition is empty");
  }
  for (size_t i = 0; i < count_; i++)
  {
    arrayShapes_[i]->move(dx, dy);
  }
}

void molchanova::CompositeShape::print(std::ostream &out) const
{
  for (size_t i = 0; i < count_; i++)
  {
    out << "Figure " << i + 1 << ":\n";
    arrayShapes_[i]->print(out);
  }
}

void molchanova::CompositeShape::scale(double factor)
{
  if (factor <= 0.0)
  {
    throw std::invalid_argument("Factor must be > 0");
  }
  const point_t tempCenter = getCenter();
  for (size_t i = 0; i < count_; i++)
  {
    arrayShapes_[i]->scale(factor);
    arrayShapes_[i]->move((arrayShapes_[i]->getCenter().x - tempCenter.x) * (factor - 1),
                          (arrayShapes_[i]->getCenter().y - tempCenter.y) * (factor - 1));
  }
}

molchanova::point_t molchanova::CompositeShape::getCenter() const
{
  return getFrameRect().pos;
}

void molchanova::CompositeShape::add(const std::shared_ptr <Shape> &newShape)
{
  if (newShape == nullptr)
  {
    throw std::invalid_argument("Incorrect shape");
  }
  if (newShape.get() == this)
  {
    throw std::logic_error("Shape composition cannot be added to itself");
  }
  for (size_t i = 0; i < count_; i++)
  {
    if (arrayShapes_[i] == newShape)
    {
      throw std::logic_error("This figure is already in the composition");
    }
  }
  std::unique_ptr<std::shared_ptr<Shape>[]> tempArrayShapes =
      std::make_unique<std::shared_ptr<Shape>[]>(count_ + 1);
  for (size_t i = 0; i < count_; i++)
  {
    tempArrayShapes[i] = arrayShapes_[i];
  }
  arrayShapes_ = std::move(tempArrayShapes);
  arrayShapes_[count_] = newShape;
  count_++;
}

molchanova::CompositeShape::CompositeShape(const molchanova::CompositeShape &other) :
  count_(other.count_)
{
  if(other.count_ != 0)
  {
    arrayShapes_ = std::make_unique< std::shared_ptr< molchanova::Shape >[] >(other.count_);
    for (size_t i = 0; i < count_; i++)
    {
      arrayShapes_[i] = other.arrayShapes_[i];
    }
  }
}

molchanova::CompositeShape::CompositeShape(molchanova::CompositeShape &&other) :
  count_(other.count_),
  arrayShapes_(std::move(other.arrayShapes_))
{
  other.count_ = 0;
}

molchanova::CompositeShape &molchanova::CompositeShape::operator=(const molchanova::CompositeShape &other)
{
  if (this != &other)
  {
    if (other.count_ != 0)
    {
      arrayShapes_ = std::make_unique< std::shared_ptr< molchanova::Shape >[] >(other.count_);
      count_ = other.count_;
      for (size_t i = 0; i < count_; i++)
      {
        arrayShapes_[i] = other.arrayShapes_[i];
      }
    }
    else
    {
      arrayShapes_ = nullptr;
      count_ = 0;
    }
  }
  return *this;
}

molchanova::CompositeShape &molchanova::CompositeShape::operator=(molchanova::CompositeShape &&other)
{
  if (&other == this)
  {
    return *this;
  }
  count_ = other.count_;
  arrayShapes_ = std::move(other.arrayShapes_);
  other.count_ = 0;
  return *this;
}

std::shared_ptr <molchanova::Shape> molchanova::CompositeShape::operator[](size_t index) const
{
  if (index >= count_)
  {
    throw std::out_of_range("Index must be less");
  }
  return arrayShapes_[index];
}

void molchanova::CompositeShape::remove(size_t index)
{
  if (!arrayShapes_)
  {
    throw std::logic_error("CompositeShape is empty");
  }
  if (index >= count_)
  {
    throw std::out_of_range("Index is out of array");
  }
  for (size_t i = index; i < count_ - 1; i++)
  {
    arrayShapes_[i] = arrayShapes_[i + 1];
  }
  arrayShapes_[--count_].reset();
}

size_t molchanova::CompositeShape::getSize() const
{
  return count_;
}
