#ifndef B4_GREATER_FOR_DATA_STRUCT
#define B4_GREATER_FOR_DATA_STRUCT

#include "data-struct.hpp"

struct GreaterForDatastruct
{
  bool operator()(const DataStruct& firstDataStruct, const DataStruct& secondDataStruct) const;
};
#endif
