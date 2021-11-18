#include "phonebook.hpp"

#include <iostream>
#include <stdexcept>
#include <iterator>

void PhoneBook::insertBefore(PhoneBook::iterator iterator, const std::string &name, const std::string &number)
{
  if (name.empty())
  {
    throw std::invalid_argument("The name must be at least 1 character");
  }

  if (number.empty())
  {
    throw std::invalid_argument("The number must be at least 1 character");
  }

  phoneBook_.insert(iterator, {name, number});
}

void PhoneBook::insertAfter(PhoneBook::iterator iterator, const std::string &name, const std::string &number)
{
  if (name.empty())
  {
    throw std::invalid_argument("The name must be at least 1 character");
  }

  if (number.empty())
  {
    throw std::invalid_argument("The number must be at least 1 character");
  }

  if ((phoneBook_.empty()) || (iterator == phoneBook_.end()))
  {
    phoneBook_.push_back({name, number});
  }
  else
  {
    phoneBook_.insert(std::next(iterator), {name, number});
  }

}

PhoneBook::iterator PhoneBook::begin()
{
  return phoneBook_.begin();
}

PhoneBook::iterator PhoneBook::end()
{
  return phoneBook_.end();
}

PhoneBook::const_iterator PhoneBook::begin() const
{
  return phoneBook_.cbegin();
}

PhoneBook::const_iterator PhoneBook::end() const
{
  return phoneBook_.cend();
}

void PhoneBook::pushBack(const std::string &name, const std::string &number)
{
  if (name.empty())
  {
    throw std::invalid_argument("The name must be at least 1 character");
  }

  if (number.empty())
  {
    throw std::invalid_argument("The number must be at least 1 character");
  }

  phoneBook_.push_back({name, number});
}

void PhoneBook::changeRecording(PhoneBook::iterator iterator, const std::string &name, const std::string &number)
{
  if (name.empty())
  {
    throw std::invalid_argument("The name must be at least 1 character");
  }

  if (number.empty())
  {
    throw std::invalid_argument("The number must be at least 1 character");
  }

  iterator->name = name;
  iterator->number = number;
}

void PhoneBook::remove(PhoneBook::iterator iterator)
{
  phoneBook_.erase(iterator);
}

void PhoneBook::show(const iterator& iter, std::ostream &out) const
{
  out << iter->number << " " << iter->name << "\n";
}

bool PhoneBook::empty() const
{
  return phoneBook_.empty();
}
