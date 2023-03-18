#ifndef LOW_LEVEL_PROGRAMMING2_COMPARATOR_LIST_H
#define LOW_LEVEL_PROGRAMMING2_COMPARATOR_LIST_H

#include "comparator.h"

struct comparator_list {
private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & next;
        ar & value;
    }

public:
    comparator_list *next;
    comparator *value;

    comparator_list();
};

#endif //LOW_LEVEL_PROGRAMMING2_COMPARATOR_LIST_H
