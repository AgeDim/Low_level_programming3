#ifndef LAB1_ATTR_H
#define LAB1_ATTR_H

#include <fstream>
#include <iostream>
#include <cinttypes>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cassert>

#include "cereal/archives/binary.hpp"
#include "cereal/types/unordered_map.hpp"
#include "cereal/types/unordered_set.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/types/string.hpp"

using namespace std;

struct attributes {
    enum type {
        INT,
        BOOL,
        FLOAT,
        STR
    };

private:
    type label;
    int64_t i;
    bool b{};
    float f{};
    string s;

public:
    attributes();

    attributes(int64_t v);

    attributes(bool v);

    attributes(float v);

    attributes(const char *v);

    type get_type();

    int32_t get_int();

    bool get_bool();

    float get_float();

    string get_string();

    string get_value();

    template<class Archive>
    void load(Archive &ar) {
        ar(label);
        switch (label) {
            case INT:
                ar(i);
            case BOOL:
                ar(b);
            case FLOAT:
                ar(f);
            case STR:
                ar(s);
        }
    }

    template<class Archive>
    void save(Archive &ar) const {
        ar(label);
        switch (label) {
            case INT:
                ar(i);
            case BOOL:
                ar(b);
            case FLOAT:
                ar(f);
            case STR:
                ar(s);
        }
    }

    template<>
    void save<cereal::BinaryOutputArchive>(cereal::BinaryOutputArchive &ar) const {
        ar(label);
        switch (label) {
            case INT:
                ar(i);
            case BOOL:
                ar(b);
            case FLOAT:
                ar(f);
            case STR:
                ar(s);
        }
    }

    template<>
    void load<cereal::BinaryInputArchive>(cereal::BinaryInputArchive &ar) {
        ar(label);
        switch (label) {
            case INT:
                ar(i);
            case BOOL:
                ar(b);
            case FLOAT:
                ar(f);
            case STR:
                ar(s);
        }
    }

};


#endif
