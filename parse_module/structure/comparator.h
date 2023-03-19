#ifndef LOW_LEVEL_PROGRAMMING2_COMPARATOR_H
#define LOW_LEVEL_PROGRAMMING2_COMPARATOR_H

#include <cstdint>
#include <boost/serialization/access.hpp>
#include "form.h"
#include "op.h"
#include "compare.h"

struct comparator {
    uint8_t negative;
    uint8_t true_flag;
    compare operation;
    op *op1;
    op *op2;

    comparator();
};


#endif //LOW_LEVEL_PROGRAMMING2_COMPARATOR_H
