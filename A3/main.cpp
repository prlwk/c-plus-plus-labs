#include <iostream>
#include <memory>
#include <stdexcept>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

void testShapeMethods(const std::shared_ptr<molchanova::Shape>& shape);

int main()
{
  const molchanova::point_t rectangle_center = {346.987, 99.32};
  const double rectangle_width = 5.1;
  const double rectangle_height = 4.8;
  std::cout << "Working with a rectangle: \n";
  try
  {
    molchanova::Rectangle rectangle(rectangle_width, rectangle_height, rectangle_center);
    std::shared_ptr< molchanova::Shape > rctngl = std::make_shared< molchanova::Rectangle >(rectangle);
    testShapeMethods(rctngl);
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what() << '\n';
    return 1;
  }

  std::cout << "Working with a circle: \n";
  const double circle_radius = 65;
  const molchanova::point_t circle_center = {-36.87, -69.2};
  try
  {
    molchanova::Circle circle(circle_radius, circle_center);
    std::shared_ptr< molchanova::Shape > crcl = std::make_shared< molchanova::Circle >(circle);
    testShapeMethods(crcl);
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what() << '\n';
    return 1;
  }

  std::cout << "Working with a composite shapes: \n";
  std::shared_ptr< molchanova::Shape > crcl;
  std::shared_ptr< molchanova::Shape > rctngl;

  try
  {
    crcl = std::make_shared< molchanova::Circle >(circle_radius, circle_center);
    rctngl = std::make_shared< molchanova::Rectangle >(rectangle_width, rectangle_height, rectangle_center);
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what() << '\n';
    return 1;
  }

  molchanova::CompositeShape shapes;

  try
  {
    shapes.add(rctngl);
    shapes.add(crcl);
    std::shared_ptr< molchanova::Shape > shps = std::make_shared< molchanova::CompositeShape >(shapes);
    testShapeMethods(shps);
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what() << '\n';
    return 1;
  }
  catch (const std::logic_error &error)
  {
    std::cerr << error.what() << '\n';
    return 1;
  }

  try
  {
    std::cout << "Size of CompositeShape: " << shapes.getSize() << "\n"
              << "Center coordinates: (" << shapes.getCenter().x << "; " << shapes.getCenter().y << ")" << "\n"
              << "Working with indexing:\n";
  }
  catch (const std::logic_error &error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }

  try
  {
    testShapeMethods(shapes[0]);
  }
  catch(const std::out_of_range &error)
  {
    std::cerr << error.what();
    return 1;
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what() << '\n';
    return 1;
  }
  catch (const std::logic_error &error)
  {
    std::cerr << error.what() << '\n';
    return 1;
  }

  try
  {
    shapes.remove(0);
  }
  catch(const std::out_of_range &error)
  {
    std::cerr << error.what();
    return 1;
  }
  catch (const std::logic_error &error)
  {
    std::cerr << error.what() << '\n';
    return 1;
  }

  return 0;
}

void testShapeMethods(const std::shared_ptr<molchanova::Shape>& shape)
{
  const double dx = 7.5;
  const double dy = 8.99;
  const double factor = 2.5;
  const molchanova::point_t point = {36.87, 9.2};
  std::cout << "Area: " << shape->getArea() << "\n";
  shape->print(std::cout);
  shape->move(dx, dy);
  shape->print(std::cout);
  molchanova::rectangle_t rectangle = shape->getFrameRect();
  std::cout << "\n" << "Width of the rectangle that surrounds: " << rectangle.width
            << "\n" << "Height of the rectangle that surrounds: " << rectangle.height
            << "\n" << "Center coordinates: (" << rectangle.pos.x << "; " << rectangle.pos.y << ")" << "\n" << "\n";
  shape->move(point);
  shape->print(std::cout);
  shape->scale(factor);
  std::cout << "\n" << "Shape after scaling: " << "\n";
  shape->print(std::cout);
}
