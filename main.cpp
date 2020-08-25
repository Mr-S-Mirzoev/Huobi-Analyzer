#include "snapshot.h"
#include <fstream>

int main () {
    std::ifstream infile("huobi.log");
    std::string line;
    SnapShot current;
    if (std::getline(infile, line))
        current.init(line);
    else {
        std::cout << "Illegal input data" << std::endl;
        exit(0);
    }
    while (std::getline(infile, line))
    {
        //try {
            Update u(line);
            current.append(u);
            std::cout << current;
        //    break;
        //} catch (std::domain_error &e) {
        //    std::cout << e.what() << std::endl;
        //}
    }
    return 0;
}