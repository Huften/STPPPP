//
// Created by Johan on 11/05/2022.
//

#ifndef UNTITLED_STOCASTICOSCILLATOR_H
#define UNTITLED_STOCASTICOSCILLATOR_H
#include "vector"
#include "Candlestick.h"


class StocasticOscillator {
public:
    int x = 14;
    int y = 3;
    double closingprice{};
    double lowestprice{};
    double highestprice{};
    double stochasticindicator{};
    std::vector<double> computefastoscillator(std::vector<Candlestick>& c);
    std::vector<double> computeslowoscillator(std::vector<double>& k);
};


#endif //UNTITLED_STOCASTICOSCILLATOR_H
