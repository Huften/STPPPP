#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "json.hpp"
#include "Candlestick.h"
#include "Trading.h"
#include "StocasticOscillator.h"
#include "Simulator.h"
#include "matplotlibcpp.h"
#include<functional>

using json = nlohmann::json;
namespace plt = matplotlibcpp;

//Requirement 1 & 2
std::vector<Trading> parsejson() {
    // read a JSON file
    std::ifstream i("C:/Users/Johan/CLionProjects/untitled/json-2y/ALKB.json");
    json j;
    i >> j;
    auto &x = j.at("trades");

    //Initializing new trading object
    Trading t;

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

//Requirement 3
std::vector<Candlestick> createcandlesticks(std::vector<Trading>& t){

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

//Requirement 4
std::vector<double> computefastoscillator(std::vector<Candlestick>& c) {

    //Instantiate class objects and variables
    StocasticOscillator s;

    //Defining local variables
    int h = 0;
    std::vector<double> oscillator;
    std::vector<double> tempvector;

    //Iterate over candles
    while (h < c.size()) {
        //Instantiate a stochastic oscillator once every loop
        s = StocasticOscillator{};
        //Calculating C (closing price)
        s.closingprice = c.at(h).closingprice;

        //Calculating L (lowest price)
        for (int i = 0; i < s.x; i++) {
            if (h < s.x) {
                tempvector.push_back(0);
            } else {
                tempvector.push_back(c.at(h-i).minprice);
            }
        }
        s.lowestprice = *std::min_element(tempvector.begin(), tempvector.end());
        tempvector.clear();

        //Calculating H (highest price)
        for (int i = 0; i < s.x; i++) {
            if (h < s.x) {
                tempvector.push_back(0);
            } else {
                tempvector.push_back(c.at(h-i).maxprice);
            }
        }
        s.highestprice = *std::max_element(tempvector.begin(), tempvector.end());
        tempvector.clear();

        //Calculating K (stochastic oscillator)
        if (s.lowestprice == s.highestprice) {
            s.stochasticindicator = 0; // K = 0 if H and L is equal. To avoid dividing with 0
        } else {
            s.stochasticindicator = ((s.closingprice - s.lowestprice) / (s.highestprice - s.lowestprice) * 100);

        }
        oscillator.push_back(s.stochasticindicator);
        h++;
    }
    return oscillator;
}

//Requirement 4
std::vector<double> computeslowoscillator(std::vector<double>& k){
    //Instantiate class objects and variables
    StocasticOscillator s;

    //Define local variables
    double tempk;
    std::vector<double> oscillator;
    std::vector<double> tempvector;
    int h = 0;

    //Iterate over k
    while (h < k.size()){
        tempk=0;
        //Fill first y days with 0's
        if(h < s.y){
            oscillator.push_back(0);
        }
        //Calculate moving average
        else{
            for (int i = 0; i < s.y; i++) {
                tempk = tempk + k.at(h-i);
            }
            oscillator.push_back(tempk/s.y);
        }
        h++;
    }
    return oscillator;
}

//Requirement 5
void simulatetrading (std::vector<Candlestick>& c, std::vector<double>& k, std::vector<double>& d){

    //Instantiate class objects and initialize variables
    Simulator s;
    s.money = s.startmoney;

    //Defining local variables
    std::vector<double> tradevalue;
    std::vector<std::string> tradestring;
    std::vector<std::string> timestring;
    int stocksbought = 0;
    double totalstocksbought = 0;
    int stockssold = 0;
    double totalstockssold = 0;

    for (int i = 0; i < c.size(); i++) {

        // Buy opportunity
        if(k.at(i) <= 20 && d.at(i) <= 20){
            if(k.at(i) > d.at(i)){
                s.buy = true;
            }
            else{
                s.buy = false;
            }
        }

        //Sell opportunity
        else if(k.at(i) >= 80 && d.at(i) >= 80){
            if(k.at(i) < d.at(i)){
                s.sell = true;
            }
            else{
                s.sell = false;
            }
        }
        else{
            s.buy = false;
            s.sell = false;
        }

        // Buy
        if(s.buy && s.money > c.at(i+1).startingprice){
            totalstocksbought = totalstocksbought - c.at(i+1).startingprice;
            stocksbought++;

            s.stocks = s.stocks + 1;
            s.money = s.money - c.at(i+1).startingprice;
            tradevalue.push_back(c.at(i+1).startingprice);
            tradestring.emplace_back("stock bought for: ");
            timestring.push_back(c.at(i).date);
        }

        // Sell
        else if(s.sell && s.stocks > 0){
            totalstockssold = totalstockssold + c.at(i+1).startingprice;
            stockssold++;

            s.stocks = s.stocks - 1;
            s.money = s.money + c.at(i+1).startingprice;
            tradevalue.push_back(c.at(i+1).startingprice);
            tradestring.emplace_back("stock sold for: ");
            timestring.push_back(c.at(i).date);
        }
    }
    //Sell remaining stocks if any
    while(s.stocks > 0){
        stockssold++;
        totalstockssold = totalstockssold + c.back().closingprice;
        s.stocks = s.stocks - 1;
        s.money = s.money + c.back().closingprice;
        tradevalue.push_back(c.back().closingprice);
        tradestring.emplace_back("stock sold for: ");
        timestring.push_back(c.back().date);
    }
    //Print result
    for (int i = 0; i < tradevalue.size(); i++) {
        std::cout << tradestring.at(i) << tradevalue.at(i) << " on:" << timestring.at(i) << std::endl;
    }
    std::cout << "Final summary " << std::endl <<
    "Money gained: " << s.money - s.startmoney << std::endl <<
    "Stocks bought: " << stocksbought  << " " <<  " Money difference: " << totalstocksbought << std::endl <<
    "Stocks sold:  " << stockssold << " " <<  " Money difference: " << totalstockssold << std::endl <<
    "Total money: " << s.money << std::endl;
}

//Requirement 6
void sorttrades(std::vector<Trading> t){
    std::sort(t.begin(), t.end(),
              [](const Trading& a, const Trading& b)
              {return a.pricev.front() > b.pricev.front();});

    std::cout << "Sorted price for all trades: " << std::endl;
    for(const auto& item : t){
        std::cout << item.pricev.front() << " ";
    }
}

//Requirement 10
void plot(std::vector<double>& oscillator1, std::vector<double>& oscillator2, std::vector<double>& price){
    plt::subplot2grid(2,1,0,0);
    plt::plot({price}, "yellow");
    plt::subplot2grid(2,1,1,0);
    plt::plot({oscillator1}, "blue");
    plt::plot({oscillator2}, "red");
    plt::tight_layout();
    plt::save("../plot.png");
}

std::vector<double> createpricevector(std::vector<Candlestick> c) {
    std::vector<double> price;
    int h = 0;
    while (h < c.size()) {
        price.push_back(c.at(h).closingprice);
        h++;
    }
    return price;
}

int main() {

    std::vector<Trading> trades = parsejson(); //req 1&2
    std::vector<Candlestick> candles = createcandlesticks(trades); //req 3
    std::vector<double> stochasticoscillatorfast = computefastoscillator(candles); //req 4
    std::vector<double> stochasticoscillatorslow = computeslowoscillator(stochasticoscillatorfast); //req 4
    simulatetrading(candles, stochasticoscillatorfast, stochasticoscillatorslow); //req 5
    sorttrades(trades); //req 6
    std::vector<double> price = createpricevector(candles); //req 10
    plot(stochasticoscillatorfast,stochasticoscillatorslow, price); //req 10

    return 0;
}
