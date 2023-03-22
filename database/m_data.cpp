#include "m_data.h"
#include <fstream>
#include <iostream>
#include <cinttypes>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cassert>

#include <cereal/archives/binary.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/unordered_set.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>


using namespace std;

m_data::m_data() {
    this->count = 0;
    this->child = unordered_map<int32_t, unordered_set<int32_t>>();
    this->free = vector<int32_t>();
    this->pos = unordered_map<string, int32_t>();
    this->path = unordered_map<int32_t, string>();
    child[0] = unordered_set<int32_t>();
    path[0] = "/root";
    pos["/root"] = 0;
}

void m_data::serialize(const std::string &file, std::ios::openmode mode) {
    std::ofstream fout(file, mode);
    fout.seekp(0);
    cereal::BinaryOutputArchive obin(fout);

    size_t start = fout.tellp();
    obin(count);
    obin(child);
    obin(free);
    obin(pos);
    obin(path);
    size_t end = fout.tellp();

    assert(end - start <= META);

    fout.close();
}

void m_data::deserialize(const std::string &file) {
    std::ifstream fin(file, BOI);
    fin.seekg(0);
    cereal::BinaryInputArchive ibin(fin);

    size_t start = fin.tellg();
    ibin(count);
    ibin(child);
    ibin(free);
    ibin(pos);
    ibin(path);
    size_t end = fin.tellg();

    assert(end - start <= META);

    fin.close();
}
