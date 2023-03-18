#ifndef LOW_LEVEL_PROGRAMMING2_LIST_ELEMENT_H
#define LOW_LEVEL_PROGRAMMING2_LIST_ELEMENT_H

#include <cstdint>
#include <boost/serialization/access.hpp>

struct list_element {
private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & next;
        ar & element;
    }

public:
    list_element *next;
    int64_t element;

    explicit list_element(int64_t id);
    list_element();
};

#endif //LOW_LEVEL_PROGRAMMING2_LIST_ELEMENT_H
