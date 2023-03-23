#ifndef LAB1_META_H
#define LAB1_META_H

#include <fstream>
#include <iostream>
#include <cinttypes>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cassert>

#include "util.h"

using namespace std;

struct m_data {
    int32_t count;
    unordered_map<string, int64_t> pos;
    unordered_map<int64_t, string> path;
    unordered_map<int64_t, unordered_set<int64_t>> child;
    vector<int64_t> free;

    m_data();

    void serialize(const std::string &file, std::ios::openmode mode);

    void deserialize(const std::string &file);

};

#endif
