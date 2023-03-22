#ifndef LAB1_LOAD_H
#define LAB1_LOAD_H

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

#include "database.h"
#include "attributes.h"

using namespace std;

void quick_ld(const string &file, size_t n);

#endif
