#ifndef HUOBIANALISER_SNAPSHOT
#define HUOBIANALISER_SNAPSHOT

#include "update.h"
#include <string>
#define SEP "],\t\t["

class SnapShot {
    unsigned timestamp;
    std::string timeHR;
    std::map <double, unsigned long> asks, bids;
public:
    SnapShot() {};
    void init(const std::string &s);
    void append (const Update &u);
    friend std::ostream& operator<<(std::ostream& os, const SnapShot& sh);
};

#endif