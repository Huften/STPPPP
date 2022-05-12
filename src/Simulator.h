//
// Created by Johan on 12/05/2022.
//

#ifndef UNTITLED_SIMULATOR_H
#define UNTITLED_SIMULATOR_H
#include "Candlestick.h"

class Simulator {
public:
    double startmoney = 10000;
    double money{};
    bool buy{};
    bool sell{};
    int stocks{};
    static void simulatetrading (std::vector<Candlestick>& c, std::vector<double>& k, std::vector<double>& d);

};



#endif //UNTITLED_SIMULATOR_H
