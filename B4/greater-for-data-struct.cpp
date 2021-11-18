#include "greater-for-data-struct.hpp"

bool GreaterForDatastruct::operator()(const DataStruct &firstDataStruct, const DataStruct &secondDataStruct) const
{
  if (firstDataStruct.key1 != secondDataStruct.key1)
  {
    return firstDataStruct.key1 < secondDataStruct.key1;
  }
  if (firstDataStruct.key2 != secondDataStruct.key2)
  {
    return firstDataStruct.key2 < secondDataStruct.key2;
  }
  return firstDataStruct.str.size() < secondDataStruct.str.size();
}
