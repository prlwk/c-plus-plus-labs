#ifndef POLICY_HPP
#define POLICY_HPP

#include <stdexcept>

template <typename Container>
struct BracketsPolicy
{
  using iterator = size_t;
  using value_type = typename Container::value_type;

  static iterator begin(const Container &)
  {
    return 0;
  }

  static iterator end(const Container & container)
  {
    return container.size();
  }

  static value_type& get(Container &container, size_t index)
  {
    if (index >= container.size())
    {
      throw std::out_of_range("Index out of range");
    }
    return container[index];
  }
};

template <typename Container>
struct AtPolicy
{
  using iterator = size_t;
  using value_type = typename Container::value_type;

  static iterator begin(const Container&)
  {
    return 0;
  }

  static iterator end(const Container& container)
  {
    return container.size();
  }

  static value_type& get(Container &container, size_t index)
  {
    if (index >= container.size())
    {
      throw std::out_of_range("Index out of range");
    }
    return container.at(index);
  }
};

template <typename Container>
struct ItPolicy
{
  using iterator = typename Container::iterator;
  using value_type = typename Container::value_type;

  static iterator begin(Container& container)
  {
    return container.begin();
  }

  static iterator end(Container& container)
  {
    return container.end();
  }

  static value_type& get(Container&, iterator& iterator)
  {
    return *iterator;
  }
};

#endif
