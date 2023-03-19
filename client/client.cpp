#include <iostream>
#include "../parse_module/XPathparser.h"
#include "../common/form.hxx"
#include "response_filling.h"

using namespace std;


int main(int argc, char *argv[]) {
    form *tree = parse();
    view_t result = fill_response(tree);
    return 0;
}
