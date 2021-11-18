#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <istream>
#include <ostream>

struct DataStruct
{
  int key1;
  int key2;
  std::string str;
};

std::istream& operator >>(std::istream& input, DataStruct& dataStruct);
std::ostream& operator <<(std::ostream& output, const DataStruct& dataStruct);
namespace detail
{
  bool isValidKey(int key);
}

#endif
