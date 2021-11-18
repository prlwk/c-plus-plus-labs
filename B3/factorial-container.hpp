#ifndef FACTORIALCONTAINER_HPP
#define FACTORIALCONTAINER_HPP

#include <iterator>
#include <cstdlib>
#include <iostream>

class FactorialContainer
{
public:
  class const_iterator: public std::iterator<std::bidirectional_iterator_tag,
      size_t, std::ptrdiff_t, size_t*, size_t>
  {
  public:
    reference operator*() const;
    const_iterator& operator++();
    const_iterator& operator--();
    const_iterator operator++(int);
    const_iterator operator--(int);
    bool operator!=(const const_iterator& iter) const;
    bool operator==(const const_iterator& iter) const;

  private:
    size_t value_;
    size_t index_;
    size_t maxIndex_;
    const_iterator(size_t index, size_t maxIndex, size_t factorial);
    friend FactorialContainer;
  };

  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  FactorialContainer(size_t size = 0);
  size_t size() const;
  const_iterator begin() const;
  const_iterator end() const;
  const_reverse_iterator rbegin() const;
  const_reverse_iterator rend() const;

private:
  const size_t maxNumber_;
  const size_t maxValue_;
};

size_t computeFactorial(size_t number);

#endif
