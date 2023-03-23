#ifndef LAB1_NODE_H
#define LAB1_NODE_H

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

#include "util.h"
#include "attributes.h"

using namespace std;

struct node {
    int64_t id{};
    string name;
    unordered_map<string, attributes> attribute;

    node();

    explicit node(const string &name);

    void add(string key, attributes value);

    unordered_map<string, attributes> getAttr();
    void setAttr(unordered_map<string, attributes> attr);

    void serialize(const string &file, int64_t position);

    void deserialize(const string &file, int64_t position);
};


#endif
