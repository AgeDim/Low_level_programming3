#ifndef LOW_LEVEL_PROGRAMMING2_COMPARATOR_H
#define LOW_LEVEL_PROGRAMMING2_COMPARATOR_H

#include <cstdint>
#include <boost/serialization/access.hpp>
#include "form.h"
#include "op.h"
#include "compare.h"

struct comparator {
private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & negative;
        ar & true_flag;
        ar & operation;
        ar & op1;
        ar & op2;
    }

public:
    uint8_t negative;
    uint8_t true_flag;
    compare operation;
    op *op1;
    op *op2;

    comparator();
};


#endif //LOW_LEVEL_PROGRAMMING2_COMPARATOR_H
