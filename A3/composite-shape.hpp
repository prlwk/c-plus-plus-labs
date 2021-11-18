#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>

#include "shape.hpp"

namespace molchanova
{
  class CompositeShape: public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape& other);
    CompositeShape(CompositeShape&& other);
    ~CompositeShape() = default;
    std::shared_ptr<Shape> operator[](size_t index) const;
    CompositeShape& operator=(const CompositeShape& other);
    CompositeShape& operator=(CompositeShape&& other);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &point) override;
    void move(double dx, double dy) override;
    void print(std::ostream &out) const override;
    void scale(double factor) override;
    point_t getCenter() const override;
    size_t getSize() const;
    void add(const std::shared_ptr<Shape>& newShape);
    void remove(size_t index);

  private:
    size_t count_;
    std::unique_ptr<std::shared_ptr<Shape>[]> arrayShapes_;
  };
}
#endif
