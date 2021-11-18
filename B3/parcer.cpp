#include "parcer.hpp"

#include <string>
#include <functional>
#include <map>
#include <sstream>

#include "reading-utilities.hpp"

void printInvalidCommand(const PhoneBookInterface&, std::ostream &output)
{
  output << "<INVALID COMMAND>\n";
}

void printInvalidStep(const PhoneBookInterface&, std::ostream &output)
{
  output << "<INVALID STEP>\n";
}

CommandType detail::parseAdd(std::istream& input)
{
  Number number;
  input >> number;
  if (!input)
  {
    return &printInvalidCommand;
  }

  Name name;
  input >> name;
  if (!input)
  {
    return &printInvalidCommand;
  }

  input >> checkEnd;
  if(!input)
  {
    return &printInvalidCommand;
  }

  return std::bind(&PhoneBookInterface::add, std::placeholders::_1, name.name, number.number);
}

CommandType detail::parseStore(std::istream& input)
{
  Mark mark;
  input >> mark;

  if (!input)
  {
    return &printInvalidCommand;
  }

  Mark newMark;
  input >> newMark;
  if (!input)
  {
    return &printInvalidCommand;
  }

  input >> checkEnd;
  if(!input)
  {
    return &printInvalidCommand;
  }

  return std::bind(&PhoneBookInterface::store, std::placeholders::_1, mark.markName, newMark.markName, std::placeholders::_2);
}

CommandType detail::parseInsert(std::istream& input)
{
  InsertPosition pos;
  input >> pos;
  if (!input)
  {
    return &printInvalidCommand;
  }

  Mark mark;
  input >> mark;
  if (!input)
  {
    return &printInvalidCommand;
  }

  Number number;
  input >> number;
  if (!input)
  {
    return &printInvalidCommand;
  }

  Name name;
  input >> name;
  if (!input)
  {
    return &printInvalidCommand;
  }

  input >> checkEnd;
  if(!input)
  {
    return &printInvalidCommand;
  }

  if (pos == AFTER)
  {
    return std::bind(&PhoneBookInterface::insertAfter, std::placeholders::_1, mark.markName,
        name.name, number.number, std::placeholders::_2);
  }
  else
  {
    return std::bind(&PhoneBookInterface::insertBefore, std::placeholders::_1, mark.markName, name.name,
        number.number, std::placeholders::_2);
  }
}

CommandType detail::parseDelete(std::istream& input)
{
  Mark mark;
  input >> mark;
  if (!input)
  {
    return &printInvalidCommand;
  }

  input >> checkEnd;
  if(!input)
  {
    return &printInvalidCommand;
  }

  return std::bind(&PhoneBookInterface::remove, std::placeholders::_1, mark.markName, std::placeholders::_2);
}

CommandType detail::parseShow(std::istream& input)
{
  Mark mark;
  input >> mark;
  if (!input)
  {
    return &printInvalidCommand;
  }

  input >> checkEnd;
  if(!input)
  {
    return &printInvalidCommand;
  }

  return std::bind(&PhoneBookInterface::show, std::placeholders::_1, mark.markName, std::placeholders::_2);
}

CommandType detail::parseMove(std::istream& input)
{
  Mark mark;
  input >> mark;
  if (!input)
  {
    return &printInvalidCommand;
  }

  Steps steps;
  input >> steps;
  if (!input)
  {
    return &printInvalidStep;
  }

  input >> checkEnd;
  if(!input)
  {
    return &printInvalidCommand;
  }

  if (steps.stepCharacter == Steps::INVALID)
  {
    return &printInvalidStep;
  }
  else if (steps.stepCharacter == Steps::POSITIONAL)
  {
    return std::bind(&PhoneBookInterface::moveToPosition, std::placeholders::_1, mark.markName,
        steps.position, std::placeholders::_2);
  }
  else
  {
    return std::bind(&PhoneBookInterface::move, std::placeholders::_1, mark.markName, steps.stepInt, std::placeholders::_2);
  }
}

bool detail::isNumberValid(const std::string &number)
{
  for (auto &symbol: number)
  {
    if (!std::isdigit(symbol))
    {
      return false;
    }
  }
  return !number.empty();
}

bool detail::isMarkNameValid(const std::string &markName)
{
  for (auto &symbol: markName)
  {
    if ((!isalnum(symbol)) && (symbol != '-'))
    {
      return false;
    }
  }
  return !markName.empty();
}

std::istream& operator >>(std::istream& input, CommandType &command)
{
  std::map <std::string, std::function <CommandType(std::istream &)> > commandMap
      = {
          {"add",    &detail::parseAdd},
          {"store",  &detail::parseStore},
          {"insert", &detail::parseInsert},
          {"delete", &detail::parseDelete},
          {"show",   &detail::parseShow},
          {"move",   &detail::parseMove}
        };

  GuardIstream guard(input);
  std::string commandStr;
  input >> std::noskipws >> std::ws >> commandStr;
  const auto tmpCommand = commandMap.find(commandStr);
  if (tmpCommand != commandMap.end())
  {
    command = tmpCommand->second(input);
    if (input.fail() && !input.eof())
    {
      input.clear();
      input >> checkEnd;
      if(!input)
      {
         command = &printInvalidCommand;
         input.clear();
      }
    }
    if (input.bad() && !input.eof())
    {
      throw std::runtime_error("Read fail");
    }
  }
  else
  {
    command = &printInvalidCommand;
  }
  return input;
}

std::istream &operator>>(std::istream &input, Number& number)
{
  GuardIstream guard(input);
  input >> skipWS >> number.number;
  if (!input)
  {
    throw std::runtime_error("Read number error");
  }
  if (!detail::isNumberValid(number.number))
  {
    input.setstate(std::ios_base::failbit);
    return input;
  }
  return input;
}

std::istream &operator>>(std::istream &input, Steps &steps)
{
  GuardIstream guard(input);
  std::string step;
  input >> skipWS >> step;
  if (!input)
  {
    throw std::runtime_error("Read step error");
  }
  if (step == "first")
  {
    steps.position = PhoneBookInterface::FIRST;
    steps.stepCharacter = Steps::POSITIONAL;
  }
  else if (step == "last")
  {
    steps.position = PhoneBookInterface::LAST;
    steps.stepCharacter = Steps::POSITIONAL;
  }
  else
  {
    std::istringstream stringStream(step);
    int stepInt = 0;
    stringStream >> stepInt;
    if (!stringStream.eof())
    {
      input.setstate(std::ios_base::failbit);
      steps.stepCharacter = Steps::INVALID;
    }
    else
    {
      steps.stepInt = stepInt;
      steps.stepCharacter = Steps::NUMERIC;
    }
  }
  return input;
}

std::istream &operator>>(std::istream &input, Mark &markName)
{
  GuardIstream guard(input);
  input >> skipWS >> markName.markName;
  if (!input)
  {
    throw std::runtime_error("Read mark name error");
  }
  if (!detail::isMarkNameValid(markName.markName))
  {
    input.setstate(std::ios_base::failbit);
  }
  return input;
}

std::istream &operator>>(std::istream &input, InsertPosition &pos)
{
  GuardIstream guard(input);
  std::string position;
  input >> skipWS >> position;
  if (!input)
  {
    throw std::runtime_error("Read insert position error");
  }
  if (position == "after")
  {
    pos = AFTER;
  }
  else if (position == "before")
  {
    pos = BEFORE;
  }
  else
  {
    input.setstate(std::ios_base::failbit);
  }
  return input;
}

std::istream &operator>>(std::istream &input, Name &name)
{
  GuardIstream guard(input);
  input >> skipWS;
  if (input.get() != '\"')
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  char symbol;
  size_t count = 0;
  while ((input >> symbol) && (symbol != '\n'))
  {
    if ((symbol == '\"') && (name.name.back() != '\\'))
    {
      break;
    }
    if (symbol == '\\')
    {
      count++;
    }
    if ((name.name.back() == '\\') && (symbol == '\\') && (count % 2 == 0))
    {
      name.name.pop_back();
    }
    if ((name.name.back() == '\\') && (symbol == '\"'))
    {
      name.name.pop_back();
    }
    name.name.push_back(symbol);
  }
  if (symbol != '\"')
  {
    input.unget();
    input.setstate(std::ios::failbit);
  }
  return input;
}
