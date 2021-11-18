#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <string>
#include <iostream>
#include <map>

#include "phonebook.hpp"

class PhoneBookInterface
{
public:
  enum MovePosition
  {
    FIRST,
    LAST
  };

  PhoneBookInterface();

  void add(const std::string& name, const std::string& number);
  void store(const std::string& markName, const std::string& newMarkName, std::ostream& output);
  void insertBefore(const std::string& markName, const std::string& name, const std::string& number, std::ostream& output);
  void insertAfter(const std::string& markName, const std::string& name, const std::string& number, std::ostream& output);
  void remove(const std::string& markName, std::ostream& output);
  void show(const std::string& markName, std::ostream& output);
  void move(const std::string& markName, int steps, std::ostream& output);
  void moveToPosition(const std::string& markName, const MovePosition& position, std::ostream& output);

private:
  PhoneBook phoneBook_;
  std::map< std::string, PhoneBook::iterator > marks_;
  void moveMarks();
};

#endif
