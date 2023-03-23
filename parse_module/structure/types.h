#ifndef LOW_LEVEL_PROGRAMMING3_TYPES_H
#define LOW_LEVEL_PROGRAMMING3_TYPES_H

#include <cstdint>
#include "field.h"

union types {
    field *string;
    int64_t integer;
    int64_t boolean;
    double real;

};

#endif //LOW_LEVEL_PROGRAMMING3_TYPES_H
