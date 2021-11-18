#include "functions-for-task2.hpp"

#include <algorithm>

size_t countShapes(const Shapes& shapes, const Shape::FigureType& figureType)
{
  return std::count_if(shapes.begin(), shapes.end(),
      [&](const Shape &shape)
      {
        if (figureType == Shape::RECTANGLE)
        {
          return (shape.type == Shape::FigureType::RECTANGLE) || (shape.type == Shape::FigureType::SQUARE);
        }
        return shape.type == figureType;
      });
}

size_t countVertices(const Shapes &shapes)
{
  size_t countVertices = 0;
  std::for_each(shapes.begin(), shapes.end(),
      [&](const Shape &shape)
      {
        countVertices += shape.points.size();
      });
  return countVertices;
}

void deletePentagons(Shapes& shapes)
{
  shapes.erase(std::remove_if(shapes.begin(), shapes.end(),
      [&](const Shape &shape)
      {
        return shape.type == Shape::FigureType::PENTAGON;
      }),
      shapes.end());
}

std::vector<Point> createVectorOfPoint(const Shapes& shapes)
{
  std::vector<Point> points(shapes.size());
  std::transform(shapes.begin(), shapes.end(), points.begin(),
      [](const Shape& shape)
      {
        return shape.points.front();
      });
  return points;
}
