#ifndef HUOBIANALISER_UPDATE
#define HUOBIANALISER_UPDATE

#include "Deps/json.hpp"
#include <string>

#define CURRENT_TIME_INDICATOR "current time:"
#define CURRENT_TIME_INDICATOR_LENGTH 14
#define MESSAGE_START_INDICATOR "message:"
#define MESSAGE_START_INDICATOR_LENGTH 9

using nlohmann::json;

class Update {
    json info;
    unsigned long long timestamp;
    std::string timeHR;
    bool is_ping = false;
public:
    Update (const std::string &s);
    friend class SnapShot;    
};

#endif