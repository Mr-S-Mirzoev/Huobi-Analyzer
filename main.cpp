#include "snapshot.h"
#include <fstream>

int main () {
    std::ifstream infile("huobi.log");
    std::string line;
    SnapShot current;
    std::ofstream outfile("huobi-analysis.log");
    if (std::getline(infile, line))
        current.init(line);
    else {
        std::cout << "Illegal input data" << std::endl;
        exit(0);
    }
    while (std::getline(infile, line))
    {
        Update u(line);
        current.append(u);
        current.get_bests();
        outfile << current;
    }
    return 0;
}