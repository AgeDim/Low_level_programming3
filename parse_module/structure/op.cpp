#include "op.h"

op::op(uint64_t field, enum field_types type, tip value) {
    this->field = field;
    this->type = type;
    this->value = value;
}

op::op() = default;
