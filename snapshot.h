#ifndef HUOBIANALISER_SNAPSHOT
#define HUOBIANALISER_SNAPSHOT

#include "update.h"
#include <string>
#define SEP "],\t\t["

class SnapShot {
    unsigned timestamp;
    std::string timeHR;
    std::map <double, unsigned long> asks, bids;
    double bb_price, bb_amount, ba_price, ba_amount; // bb = best bid; ba = best asks
public:
    SnapShot() {};
    void init(const std::string &s);
    void append (const Update &u);
    void get_bests();
    friend std::ostream& operator<<(std::ostream& os, const SnapShot& sh);
};

#endif