//
// Created by Johan on 11/05/2022.
//

#ifndef UNTITLED_TRADING_H
#define UNTITLED_TRADING_H
#include "json.hpp"

class Trading {
    double seq{};
    double price{};
public:
    static std::vector<Trading> parsejson();
    static void sorttrades(std::vector<Trading> t);
    std::vector<double> seqv {};
    std::vector<double> pricev {};
    std::vector<std::string> datev{};

};


#endif //UNTITLED_TRADING_H
