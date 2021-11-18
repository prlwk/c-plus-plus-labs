#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unordered_set>
#include <string>
#include <iterator>
#include <algorithm>

#include "functions-for-task2.hpp"

void executeTask1(std::istream& input, std::ostream& output);
void executeTask2(std::istream& input, std::ostream& output);

int main(int argc, char *argv[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("Input arguments must be 2");
    }
    int taskNumber;
    std::istringstream stream(argv[1]);
    stream >> taskNumber;
    if (!stream.eof())
    {
      std::cerr << "Incorrect number of task";
      return 1;
    }
    switch (taskNumber)
    {
      case 1:
      {
        try
        {
          executeTask1(std::cin, std::cout);
        }
        catch (const std::runtime_error &error)
        {
          std::cerr << error.what();
          return 2;
        }
        break;
      }

      case 2:
      {
        try
        {
          executeTask2(std::cin, std::cout);
        }
        catch (const std::runtime_error &error)
        {
          std::cerr << error.what();
          return 2;
        }
        break;
      }

      default:
      {
        std::cerr << "Incorrect number of task";
        return 1;
      }
    }
  }
  catch (const std::exception& error)
  {
    std::cerr << error.what();
    return 2;
  }

  return 0;
}

void executeTask1(std::istream& input, std::ostream& output)
{
  std::unordered_set<std::string> words((std::istream_iterator<std::string>(input)), std::istream_iterator<std::string>());
  if (!input.eof())
  {
    throw std::runtime_error("Read error");
  }
  std::copy(words.begin(), words.end(), std::ostream_iterator<std::string>(output, "\n"));
}

void executeTask2(std::istream &input, std::ostream &output)
{
  Shapes shapes((std::istream_iterator<Shape>(input)), std::istream_iterator<Shape>());

  if (!input.eof())
  {
    throw std::runtime_error("Read error");
  }

  output << "Vertices: " << countVertices(shapes) << '\n';
  output << "Triangles: " << countShapes(shapes, Shape::FigureType::TRIANGLE) << '\n';
  output << "Squares: " << countShapes(shapes, Shape::FigureType::SQUARE) << '\n';
  output << "Rectangles: " << countShapes(shapes, Shape::FigureType::RECTANGLE) << '\n';
  deletePentagons(shapes);
  std::vector<Point> points = createVectorOfPoint(shapes);
  output << "Points: ";
  std::copy(points.begin(), points.end(), std::ostream_iterator<Point>(output, " "));
  std::sort(shapes.begin(), shapes.end(), ShapeComparator());
  output << '\n' << "Shapes: " << '\n';
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape>(output, "\n"));
}
