//
// Created by Johan on 10/05/2022.
//
#include "Trading.h"
#include "Candlestick.h"


double Candlestick::getstartingprice(Trading& x) {
    return *x.pricev.begin();
}

double Candlestick::getclosingprice(Trading& x) {
    return x.pricev.back();
}

double Candlestick::getmaxprice(Trading& x) {

    return *std::max_element(x.pricev.begin(), x.pricev.end());
}

double Candlestick::getminprice(Trading& x) {
    return *std::min_element(x.pricev.begin(), x.pricev.end());
}