//
// Created by Johan on 11/05/2022.
//

#include "Trading.h"
#include "json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;
//Requirement 1 & 2
    std::vector<Trading> Trading::parsejson() {
    // read a JSON file
    std::ifstream i("C:/Users/Johan/CLionProjects/untitled/json-2y/ALKB.json");
    json j;
    i >> j;
    auto &x = j.at("trades");

    //Instantiate new trading object
    Trading t{};

    //Defining local variables
    int h = 0;
    std::vector<Trading> trade{};

    //Iterate over all trades in the selected dataset
    while(h < x.size()){
        auto& y = x.at(h);
        if (y.at("seq") == 1) {
            if(h != 0)
                trade.push_back(t);
            t = Trading{};
        }
        //Save selected fields from the trade object in vectors
        t.datev.push_back(y.at("time"));
        t.pricev.push_back(y.at("price"));
        t.seqv.push_back(y.at("seq"));
        h++;
    }
    return trade;
}

//Requirement 6
void Trading::sorttrades(std::vector<Trading> t){
    std::sort(t.begin(), t.end(),
              [](const Trading& a, const Trading& b)
              {return a.pricev.front() > b.pricev.front();});

    std::cout << "Sorted price for all trades: " << std::endl;
    for(const auto& item : t){
        std::cout << item.pricev.front() << " ";
    }
}

