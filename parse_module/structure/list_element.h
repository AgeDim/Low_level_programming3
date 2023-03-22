#ifndef LOW_LEVEL_PROGRAMMING2_LIST_ELEMENT_H
#define LOW_LEVEL_PROGRAMMING2_LIST_ELEMENT_H

#include <cstdint>
#include <string>

struct list_element {
    list_element *next;
    std::string element;

    explicit list_element(std::string);
};

#endif //LOW_LEVEL_PROGRAMMING2_LIST_ELEMENT_H
