#ifndef LOW_LEVEL_PROGRAMMING2_FILTER_H
#define LOW_LEVEL_PROGRAMMING2_FILTER_H


#include <cstdint>
#include "comparator_list.h"

struct filter {
private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & negative;
        ar & comparators;
    }

public:
    uint8_t negative;
    comparator_list *comparators;

    explicit filter(uint8_t negative);
    filter();
};

#endif //LOW_LEVEL_PROGRAMMING2_FILTER_H
