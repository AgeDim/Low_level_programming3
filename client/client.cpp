#include "../parse_module/XPathparser.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <fstream>
#include <iostream>

using namespace std;


int main(int argc, char *argv[]) {
    form form = *parse();
    std::ofstream ofs("filename");
        // save data to archive
    {
        boost::archive::text_oarchive oa(ofs);
        // write class instance to archive
        oa << form;
        // archive and stream closed when destructors are called
    }
    auto *new1 = new struct form(static_cast<crud>('+'));
    std::ifstream ifs("filename");
    boost::archive::text_iarchive ia(ifs);
    // read class state from archive
    ia >> new1;
    std::cout << new1->crud_operation << endl;
    return 0;
}
