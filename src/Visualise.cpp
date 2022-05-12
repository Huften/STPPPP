//
// Created by Johan on 12/05/2022.
//

#include "Visualise.h"
#include "vector"
#include "matplotlibcpp.h"
#include "Candlestick.h"

namespace plt = matplotlibcpp;

//Requirement 10
void Visualise::plot(std::vector<double>& oscillator1, std::vector<double>& oscillator2, std::vector<double>& price){
    plt::subplot2grid(2,1,0,0);
    plt::plot({price}, "yellow");
    plt::subplot2grid(2,1,1,0);
    plt::plot({oscillator1}, "blue");
    plt::plot({oscillator2}, "red");
    plt::tight_layout();
    plt::save("../plot.png");
}

std::vector<double> Visualise::createpricevector(std::vector<Candlestick> c) {
    std::vector<double> price;
    int h = 0;
    while (h < c.size()) {
        price.push_back(c.at(h).closingprice);
        h++;
    }
    return price;
}