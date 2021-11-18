#ifndef FUNCTIONS_FOR_TASK2_HPP
#define FUNCTIONS_FOR_TASK2_HPP

#include <map>

#include "shape.hpp"

size_t countShapes(const Shapes& shapes, const Shape::FigureType& figureType);
size_t countVertices(const Shapes& shapes);
void deletePentagons(Shapes& shapes);
std::vector<Point> createVectorOfPoint(const Shapes& shapes);

#endif
