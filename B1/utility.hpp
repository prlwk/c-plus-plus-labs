#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

namespace details
{
  enum SortType
  {
    ASCENDING,
    DESCENDING
  };

  void fillRandom(double *array, size_t size);

  template<template<typename> class Policy, typename Container>
  void bubbleSort(Container &container, const SortType &SortType)
  {
    if (!container.empty())
    {
      auto begin = Policy <Container>::begin(container);
      auto end = Policy <Container>::end(container);

      for (auto i = begin; i != end; i++)
      {
        for (auto j = i; j != end; j++)
        {
          if (SortType == ASCENDING ? (Policy <Container>::get(container, i) > Policy <Container>::get(container, j))
                                    : (Policy <Container>::get(container, i) < Policy <Container>::get(container, j)))
          {
            std::swap(Policy <Container>::get(container, i), Policy <Container>::get(container, j));
          }
        }
      }
    }
  }
}

template<typename Container>
void print(const Container &container, std::ostream &out, const char *sep = " ")
{
  if (!sep)
  {
    throw std::invalid_argument("Empty separator");
  }

  for (auto i = container.begin(); i != container.end(); ++i)
  {
    out << *i << sep;
  }
}

details::SortType getSortType(const char *order);

void executeTask1(const char *order);

void executeTask2(const char *name);

void executeTask3();

void executeTask4(const char *order, size_t size);

#endif
