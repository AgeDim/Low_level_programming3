#ifndef LOW_LEVEL_PROGRAMMING3_TIP_H
#define LOW_LEVEL_PROGRAMMING3_TIP_H

#include <cstdint>
#include <cstring>
#include <string>
#include "field.h"

struct tip {
    std::string string;
    int64_t integer;
    int64_t boolean;
    double real;

    tip();
};

#endif //LOW_LEVEL_PROGRAMMING3_TIP_H
