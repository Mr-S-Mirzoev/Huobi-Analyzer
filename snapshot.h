#ifndef HUOBIANALISER_SNAPSHOT
#define HUOBIANALISER_SNAPSHOT

#include "update.h"
#include <string>
#define SEP "],\t\t["

class SnapShot {
    unsigned long long timestamp;
    std::string timeHR;
    std::map <double, unsigned long> asks, bids;
    double bb_price, ba_price; // bb = best bid; ba = best asks
    unsigned long bb_amount, ba_amount;
public:
    SnapShot() {};
    void init(const std::string &s);
    void append (const Update &u);
    void get_bests();
    friend std::ostream& operator<<(std::ostream& os, const SnapShot& sh);
};

#endif