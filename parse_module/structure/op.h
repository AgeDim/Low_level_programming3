#ifndef LOW_LEVEL_PROGRAMMING2_OP_H
#define LOW_LEVEL_PROGRAMMING2_OP_H

#include "form.h"
#include "field_types.h"
#include "tip.h"
#include <cstdint>

struct op {
    uint64_t field;
    field_types type;
    tip value;

    op(uint64_t field, enum field_types type, tip value);
    op();
};


#endif //LOW_LEVEL_PROGRAMMING2_OP_H
