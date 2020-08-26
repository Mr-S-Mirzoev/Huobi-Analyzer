#include "snapshot.h"

void SnapShot::init (const std::string &s) {
    int pos, pos_end;

    pos = s.find('[') + 1;
    pos_end = s.find(']', pos) - 1;
    timeHR = s.substr(pos, pos_end);

    pos = s.find(CURRENT_TIME_INDICATOR) + CURRENT_TIME_INDICATOR_LENGTH;
    pos_end = s.find(',', pos);
    timestamp = std::stoul(s.substr(pos, pos_end));
    
    pos = s.find(MESSAGE_START_INDICATOR, pos_end) + MESSAGE_START_INDICATOR_LENGTH;
    json info = json::parse(s.substr(pos));
    
    for (auto it = info["tick"]["asks"].begin(); it != info["tick"]["asks"].end(); ++it) {
        //std::cout << (*it)[0] << ' ' << (*it)[1] << std::endl;
        if ((*it)[1] != 0) { // assuming there may occure case when init snapshot has illegal data such as [<price>, 0]
            asks.insert({std::stod((*it)[0].dump(0)), std::stoul((*it)[1].dump(1))});
        }
    }
    
    for (auto it = info["tick"]["bids"].begin(); it != info["tick"]["bids"].end(); ++it) {
        //std::cout << (*it)[0] << ' ' << (*it)[1] << std::endl;
        if ((*it)[1] != 0) { // assuming there may occure case when init snapshot has illegal data such as [<price>, 0]
            bids.insert({std::stod((*it)[0].dump(0)), std::stoul((*it)[1].dump(1))});
        }
    }
}

void SnapShot::append (const Update &u) {
    // Even if it's just ping we're up-to-date to the time when ping was sent.
    timeHR = u.timeHR;
    timestamp = u.timestamp;

    if (!u.is_ping) {
        //std::cout << u.info.dump(4) << ' ' << u.info["tick"]["asks"].empty() << std::endl;

        if (!(u.info["tick"]["asks"].empty())) {
            for (auto it = u.info["tick"]["asks"].begin(); it != u.info["tick"]["asks"].end(); ++it) {
                //std::cout << (*it)[0] << ' ' << (*it)[1] << std::endl;
                if ((*it)[1] != 0)
                    asks.insert({std::stod((*it)[0].dump(0)), std::stoul((*it)[1].dump(1))});
                else
                    asks.erase(std::stod((*it)[0].dump(0)));
            }
        }

        if (!(u.info["tick"]["bids"].empty())) {
            for (auto it = u.info["tick"]["bids"].begin(); it != u.info["tick"]["bids"].end(); ++it) {
                //std::cout << (*it)[0] << ' ' << (*it)[1] << std::endl;
                if ((*it)[1] != 0)
                    bids.insert({std::stod((*it)[0].dump(0)), std::stoul((*it)[1].dump(1))});
                else
                    bids.erase(std::stod((*it)[0].dump(0)));
            }
        }
    }
}

std::ostream& operator<<(std::ostream& os, const SnapShot& sh) {/*
    os << "Asks:" << std::endl;
    for (auto it = sh.asks.begin(); it != sh.asks.end(); ++it) {
        os << (*it).first << ' ' << (*it).second << std::endl;
    }
    os << "Bids:" << std::endl;
    for (auto it = sh.bids.begin(); it != sh.bids.end(); ++it) {
        os << (*it).first << ' ' << (*it).second << std::endl;
    }*/
    double best_ask_price = (*(sh.asks.rbegin())).first;
    double best_ask_amount = (*(sh.asks.rbegin())).second;
    double best_bid_price = (*(sh.bids.begin())).first;
    double best_bid_amount = (*(sh.bids.begin())).second;

    os << "[" << sh.timestamp << SEP << best_bid_price << ", " << best_bid_amount << SEP;
    os << best_ask_price << ", " << best_ask_amount << "]" << std::endl;
    return os;
}