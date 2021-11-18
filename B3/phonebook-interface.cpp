#include "phonebook-interface.hpp"

#include <iostream>
#include <string>
#include <cmath>

void printEmpty(std::ostream &out)
{
  out << "<EMPTY>\n";
}

void printInvalidBookmark(std::ostream &out)
{
  out << "<INVALID BOOKMARK>\n";
}

PhoneBookInterface::PhoneBookInterface()
{
  marks_["current"] = phoneBook_.end();
}

void PhoneBookInterface::add(const std::string &name, const std::string &number)
{
  phoneBook_.pushBack(name, number);
  moveMarks();
}

void PhoneBookInterface::store(const std::string &markName, const std::string &newMarkName, std::ostream &output)
{
  auto bookMark = marks_.find(markName);
  if (bookMark == marks_.end())
  {
    printInvalidBookmark(output);
    return;
  }
  marks_[newMarkName] = bookMark->second;
}

void PhoneBookInterface::insertBefore(const std::string &markName, const std::string &name,
    const std::string &number, std::ostream &output)
{
  if (marks_.find(markName) == marks_.end())
  {
    printInvalidBookmark(output);
    return;
  }
  phoneBook_.insertBefore(marks_[markName], name, number);
  moveMarks();
}

void PhoneBookInterface::insertAfter(const std::string &markName, const std::string &name,
    const std::string &number, std::ostream &output)
{
  if (marks_.find(markName) == marks_.end())
  {
    printInvalidBookmark(output);
    return;
  }
  phoneBook_.insertAfter(marks_[markName], name, number);
  moveMarks();
}

void PhoneBookInterface::remove(const std::string &markName, std::ostream &output)
{
  if (marks_.find(markName) == marks_.end())
  {
    printInvalidBookmark(output);
    return;
  }
  if (marks_[markName] == phoneBook_.end())
  {
    printEmpty(output);
    return;
  }

  auto iter = marks_[markName];
  for (auto &mark : marks_)
  {
    if (mark.second == iter)
    {
      if ((std::next(mark.second) != phoneBook_.end()) || (mark.second == phoneBook_.begin()))
      {
        mark.second++;
      }
      else
      {
        mark.second--;
      }
    }
  }
  phoneBook_.remove(iter);
}

void PhoneBookInterface::show(const std::string &markName, std::ostream &output)
{
  if (marks_.find(markName) == marks_.end())
  {
    printInvalidBookmark(output);
    return;
  }
  if (phoneBook_.empty())
  {
    printEmpty(output);
    return;
  }
  phoneBook_.show(marks_[markName], output);
}

void PhoneBookInterface::move(const std::string &markName, int steps, std::ostream &output)
{
  if (phoneBook_.empty())
  {
    printEmpty(output);
    return;
  }
  auto mark = marks_.find(markName);
  if (mark == marks_.end())
  {
    printInvalidBookmark(output);
    return;
  }
  if (steps > 0)
  {
    if (std::distance(mark->second, --phoneBook_.end()) < steps)
    {
      mark->second = --phoneBook_.end();
    }
    else
    {
      mark->second = std::next(mark->second, steps);
    }
  }
  else if (steps < 0)
  {
    if (std::distance(mark->second, phoneBook_.begin()) < std::abs(steps))
    {
      mark->second = phoneBook_.begin();
    }
    else
    {
      mark->second = std::prev(mark->second, std::abs(steps));
    }
  }
}

void PhoneBookInterface::moveToPosition(const std::string &markName, const MovePosition &position, std::ostream &output)
{
  if (marks_.find(markName) == marks_.end())
  {
    printInvalidBookmark(output);
    return;
  }
  if (phoneBook_.empty())
  {
    printEmpty(output);
    return;
  }

  if (position == FIRST)
  {
    marks_[markName] = phoneBook_.begin();
  }
  if (position == LAST)
  {
    marks_[markName] = --phoneBook_.end();
  }
}

void PhoneBookInterface::moveMarks()
{
  if (phoneBook_.empty())
  {
    return;
  }

  for (auto &mark : marks_)
  {
    if (mark.second == phoneBook_.end())
    {
      mark.second--;
    }
  }
}
