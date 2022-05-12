//
// Created by Johan on 12/05/2022.
//

#include "Simulator.h"
#include "Candlestick.h"

//Requirement 5
void Simulator::simulatetrading (std::vector<Candlestick>& c, std::vector<double>& k, std::vector<double>& d){

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