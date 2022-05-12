//
// Created by Johan on 10/05/2022.
//
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include "Trading.h"

#ifndef UNTITLED_CANDLESTICK_H
#define UNTITLED_CANDLESTICK_H


class Candlestick {
    double seq{};
public:
    double startingprice{};
    double closingprice{};
    double maxprice{};
    double minprice{};
    double getstartingprice(Trading& x);
    double getclosingprice(Trading& x);
    double getmaxprice(Trading& x);
    double getminprice(Trading& x);
    std::string date{};
};


#endif //UNTITLED_CANDLESTICK_H
