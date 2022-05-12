#include "json.hpp"
#include "Candlestick.h"
#include "Trading.h"
#include "StocasticOscillator.h"
#include "Simulator.h"
#include "matplotlibcpp.h"
#include "Visualise.h"
#include<functional>

int main() {

    Trading t{}; Candlestick c{}; StocasticOscillator s{}; Visualise v{};
    std::vector<Trading> trades = Trading::parsejson(); //req 1&2
    std::vector<Candlestick> candles = c.createcandlesticks(trades); //req 3
    std::vector<double> stochasticoscillatorfast = s.computefastoscillator(candles); //req 4
    std::vector<double> stochasticoscillatorslow = s.computeslowoscillator(stochasticoscillatorfast); //req 4
    Simulator::simulatetrading(candles, stochasticoscillatorfast, stochasticoscillatorslow); //req 5
    Trading::sorttrades(trades); //req 6
    std::vector<double> price = v.createpricevector(candles); //req 10
    v.plot(stochasticoscillatorfast,stochasticoscillatorslow, price); //req 10

    return 0;
}
