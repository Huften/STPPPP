//
// Created by Johan on 11/05/2022.
//

#include "StocasticOscillator.h"
#include "Candlestick.h"


//Requirement 4
std::vector<double> StocasticOscillator::computefastoscillator(std::vector<Candlestick>& c) {

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
std::vector<double> StocasticOscillator::computeslowoscillator(std::vector<double>& k){
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