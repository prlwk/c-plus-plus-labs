#include <iostream>
#include "rectangle.hpp"
#include "base-types.hpp"
#include "circle.hpp"
#include "shape.hpp"

int main()
{
  const point_t rectangle_center = {346.987,99.32};
  const double rectangle_width = 5.1;
  const double rectangle_height = 4.8;
  Rectangle rectangle_one(rectangle_width,rectangle_height,rectangle_center);
  std::cout << "Area: "<< rectangle_one.getArea() << "\n";
  const double dx = 7.5;
  const double dy = 8.99;
  rectangle_one.move(dx, dy);
  rectangle_one.print(std::cout);
  rectangle_t rectangle_two;
  rectangle_two = rectangle_one.getFrameRect();
  std::cout << "\n" << "Width of the rectangle that surrounds: " << rectangle_two.width
            << "\n" << "Height of the rectangle that surrounds: " << rectangle_two.height
            << "\n" <<"Center coordinates: (" << rectangle_two.pos.x << "; " << rectangle_two.pos.y<< ")" << "\n"<< "\n";
  const point_t point_one = {36.87,9.2};
  rectangle_one.move(point_one);
  rectangle_one.print(std::cout);

  Shape* ptr_rectangle = &rectangle_one;
  std::cout << "\n";
  ptr_rectangle->print(std::cout);
  std::cout << "\n" << "Area: " << ptr_rectangle->getArea() << "\n";
  ptr_rectangle->move(dx, dy);
  ptr_rectangle->print(std::cout);
  rectangle_two = ptr_rectangle->getFrameRect();
  std::cout << "\n" << "Width of the rectangle that surrounds: " << rectangle_two.width
            << "\n" << "Height of the rectangle that surrounds: " << rectangle_two.height
            << "\n" << "Center coordinates: (" << rectangle_two.pos.x << "; " << rectangle_two.pos.y << ")" << "\n" << "\n";
  ptr_rectangle->move(point_one);
  ptr_rectangle->print(std::cout);

  const double circle_radius = 65;
  const point_t circle_center = {-36.87,-69.2};
  Circle circle(circle_radius, circle_center);
  Shape* ptr_circle = &circle;
  std::cout << "\n";
  ptr_circle->print(std::cout);
  std::cout << "\n" << "Area: " << ptr_circle->getArea() << "\n";
  ptr_circle->move(dx, dy);
  ptr_circle->print(std::cout);
  rectangle_two = ptr_circle->getFrameRect();
  std::cout << "\n" << "Width of the rectangle that surrounds: " << rectangle_two.width
            << "\n" << "Height of the rectangle that surrounds: " << rectangle_two.height
            << "\n"<< "Center coordinates: (" << rectangle_two.pos.x << "; " << rectangle_two.pos.y << ")" << "\n" << "\n";
  const point_t point_two = {32.9, 0.76};
  ptr_circle->move(point_two);
  ptr_circle->print(std::cout);

  return 0;
}
