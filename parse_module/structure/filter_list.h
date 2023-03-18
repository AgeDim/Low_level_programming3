#ifndef LOW_LEVEL_PROGRAMMING2_FILTER_LIST_H
#define LOW_LEVEL_PROGRAMMING2_FILTER_LIST_H
#include "filter.h"

struct filter_list {
private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & next;
        ar & value;
    }

public:
    filter_list *next;
    filter *value;

    filter_list();
};


#endif //LOW_LEVEL_PROGRAMMING2_FILTER_LIST_H
