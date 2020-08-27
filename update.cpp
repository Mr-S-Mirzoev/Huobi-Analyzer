#include "update.h"

Update::Update (const std::string &s) {
    int pos, pos_end;

    pos = s.find('[') + 1;
    pos_end = s.find(']', pos) - 1;
    timeHR = s.substr(pos, pos_end);

    pos = s.find(CURRENT_TIME_INDICATOR) + CURRENT_TIME_INDICATOR_LENGTH;
    pos_end = s.find(',', pos);
    timestamp = std::stoull(s.substr(pos, pos_end));
    
    pos = s.find(MESSAGE_START_INDICATOR, pos_end) + MESSAGE_START_INDICATOR_LENGTH;
    info = json::parse(s.substr(pos));
    is_ping = (info.find("ping") != info.end());
    //std::cout << info.dump(4) << ' ' << timestamp << std::endl;
}