#include "factorial-container.hpp"

#include <cstdlib>
#include <stdexcept>
#include <cassert>

FactorialContainer::FactorialContainer(size_t size) :
  maxNumber_(size + 1),
  maxValue_(computeFactorial(size + 1))
{}

size_t FactorialContainer::size() const
{
  return maxNumber_ - 1;
}

FactorialContainer::const_iterator FactorialContainer::begin() const
{
  return const_iterator(1, maxNumber_, 1);
}

FactorialContainer::const_iterator FactorialContainer::end() const
{
  return FactorialContainer::const_iterator(maxNumber_, maxNumber_, maxValue_);
}

FactorialContainer::const_reverse_iterator FactorialContainer::rbegin() const
{
  return std::reverse_iterator< FactorialContainer::const_iterator >(end());
}

FactorialContainer::const_reverse_iterator FactorialContainer::rend() const
{
  return std::reverse_iterator< FactorialContainer::const_iterator >(begin());
}

FactorialContainer::const_iterator::const_iterator(size_t index, size_t maxIndex, size_t factorial) :
  value_(factorial),
  index_(index),
  maxIndex_(maxIndex)
{
  assert(index_ <= maxIndex_);
}

FactorialContainer::const_iterator::reference FactorialContainer::const_iterator::operator*() const
{
  return value_;
}

FactorialContainer::const_iterator &FactorialContainer::const_iterator::operator++()
{
  if (index_ >= maxIndex_)
  {
    throw std::out_of_range("Going outside the container");
  }
  value_ *= (++index_);
  return *this;
}

FactorialContainer::const_iterator &FactorialContainer::const_iterator::operator--()
{
  if (index_ <= 1)
  {
    throw std::out_of_range("Going outside the container");
  }
  value_ /= (index_--);
  return *this;
}

FactorialContainer::const_iterator FactorialContainer::const_iterator::operator++(int)
{
  FactorialContainer::const_iterator iterator = *this;
  ++(*this);
  return iterator;
}

FactorialContainer::const_iterator FactorialContainer::const_iterator::operator--(int)
{
  FactorialContainer::const_iterator iterator = *this;
  --(*this);
  return iterator;
}

bool FactorialContainer::const_iterator::operator!=(const FactorialContainer::const_iterator &iter) const
{
  return !(iter == *this);
}

bool FactorialContainer::const_iterator::operator==(const FactorialContainer::const_iterator &iter) const
{
  return index_ == iter.index_;
}

size_t computeFactorial(size_t number)
{
  size_t factorial = number;
  for (size_t i = 1; i < number; i++)
  {
    if (factorial > SIZE_MAX / i)
    {
      throw std::overflow_error("Factorial value became overflow");
    }
    factorial *= i;
  }
  return factorial;
}
