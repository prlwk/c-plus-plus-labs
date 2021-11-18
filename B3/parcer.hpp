#ifndef PARCER_HPP
#define PARCER_HPP

#include <functional>
#include <string>
#include <iostream>

#include "phonebook-interface.hpp"

using CommandType = std::function< void(PhoneBookInterface&, std::ostream&) >;

enum InsertPosition
{
  AFTER,
  BEFORE
};

struct Steps
{
  enum StepType
  {
    POSITIONAL,
    NUMERIC,
    INVALID
  };

  StepType stepCharacter;

  union
  {
    PhoneBookInterface::MovePosition position;
    int stepInt;
  };
};

struct Mark
{
  std::string markName;
};

struct Name
{
  std::string name;
};

struct Number
{
  std::string number;
};

std::istream& operator >>(std::istream& input, CommandType &command);
std::istream& operator >>(std::istream& input, Number& number);
std::istream& operator >>(std::istream& input, Name& name);
std::istream& operator >>(std::istream& input, Steps& steps);
std::istream& operator >>(std::istream& input, Mark& markName);
std::istream& operator >>(std::istream& input, InsertPosition& pos);

namespace detail
{
  CommandType parseAdd(std::istream& input);
  CommandType parseStore(std::istream& input);
  CommandType parseInsert(std::istream& input);
  CommandType parseDelete(std::istream& input);
  CommandType parseShow(std::istream& input);
  CommandType parseMove(std::istream& input);
  bool isNumberValid(const std::string& number);
  bool isMarkNameValid(const std::string& markName);
}

void printInvalidCommand(const PhoneBookInterface&, std::ostream &output);
void printInvalidStep(const PhoneBookInterface&, std::ostream &output);

#endif
