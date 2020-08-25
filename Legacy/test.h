#include "Deps/json.hpp"
#include <cstdio>
#include <string>

using nlohmann::json;

#include <iostream>
#include <fstream>

#define CURRENT_TIME_INDICATOR "current time:"
#define CURRENT_TIME_INDICATOR_LENGTH 14
#define MESSAGE_START_INDICATOR "message:"
#define MESSAGE_START_INDICATOR_LENGTH 9

class Update {
    json info;
    unsigned long timestamp;
    std::string timeHR;
    bool is_ping = false;
public:
    Update (const std::string &s);
    friend class SnapShot;    
};

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