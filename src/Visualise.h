//
// Created by Johan on 12/05/2022.
//

#ifndef UNTITLED_VISUALISE_H
#define UNTITLED_VISUALISE_H
#include "vector"
#include "Candlestick.h"


class Visualise {
public:
    void plot(std::vector<double>& oscillator1, std::vector<double>& oscillator2, std::vector<double>& price);
    std::vector<double> createpricevector(std::vector<Candlestick> c);
};


#endif //UNTITLED_VISUALISE_H
