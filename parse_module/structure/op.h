#ifndef LOW_LEVEL_PROGRAMMING2_OP_H
#define LOW_LEVEL_PROGRAMMING2_OP_H

#include "form.h"
#include "field_types.h"
#include "types.h"
#include <cstdint>

struct op {
private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & type;
        ar & value;
    }

public:
    uint8_t field;
    field_types type;
    types value;

    op(uint8_t field, enum field_types type, union types value);
    op();
};


#endif //LOW_LEVEL_PROGRAMMING2_OP_H
