#ifndef LOW_LEVEL_PROGRAMMING2_FIELD_H
#define LOW_LEVEL_PROGRAMMING2_FIELD_H

#include <cstddef>
#include <boost/serialization/access.hpp>

struct field {
private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & size;
        ar & value;
    }

public:
    size_t size;
    char *value;

    field(size_t size, char *value);
    field();
};

#endif
