#ifndef LOW_LEVEL_PROGRAMMING2_LIST_LEVEL_H
#define LOW_LEVEL_PROGRAMMING2_LIST_LEVEL_H

#include <cstdint>
#include "form.h"
#include "list_element.h"
#include "filter_list.h"
#include "parent.h"

struct list_level {
private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & negative;
        ar & any;
        ar & next;
        ar & value;
        ar & filters;
    }

public:
    uint8_t negative;
    uint8_t any;
    parent place;
    list_level *next = nullptr;
    list_element value = list_element(0);
    filter_list *filters = nullptr;

    list_level(uint8_t negative, uint8_t any, parent parent);
    list_level();
};

#endif //LOW_LEVEL_PROGRAMMING2_LIST_LEVEL_H
