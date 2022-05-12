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

//Requirement 3
std::vector<Candlestick> Candlestick::createcandlesticks(std::vector<Trading>& t){

    //Instantiate class objects and variables
    Candlestick c;

    //Defining local variables
    int h = 0;
    std::vector<Candlestick> candle{};

    //Iterate over all trades
    while(h < t.size()){
        c = Candlestick{}; //Instantiate a new candle object every loop

        //Call candle methods to calc the 4 parameters of a candle
        c.startingprice =  c.getstartingprice(t.at(h));
        c.closingprice =  c.getclosingprice(t.at(h));
        c.maxprice =  c.getmaxprice(t.at(h));
        c.minprice =  c.getminprice(t.at(h));
        c.date = t.at(h).datev.at(0);
        candle.push_back(c);
        h++;
    }
    std::reverse(candle.begin(), candle.end());
    return candle;
}