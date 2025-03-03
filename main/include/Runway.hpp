#ifndef RUNWAY_HPP
#define RUNWAY_HPP

#include <random>
#include <iostream>
#include "cadmium/modeling/devs/atomic.hpp"

using namespace cadmium;

struct runway_State {
    double sigma;
    bool occupied;
    enum States {IDLE, ARRIVAL, DEPART};
    States currentState;
    int planeNum;
    explicit runway_State(): sigma(1), currentState(States::IDLE){
    }
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const runway_State& state) {
    out  << "{" << state.sigma << state.currentState << "}";
    return out;
}
#endif

class Runway : public Atomic<runway_State> {
    public:
    Port<int> exitA;
    Port<int> exitD;
    Port<int> arrival;
    Port<int> depart;

    Runway(const std::string id) : Atomic<runway_State>(id, runway_State()) {
        exitA = addOutPort<int>("exitA");
        exitD = addOutPort<int>("exitD");
        arrival = addInPort<int>("arrival");
        depart = addInPort<int>("depart");
    }

    void internalTransition(runway_State& state) const override {
        if(state.currentState == runway_State::States::ARRIVAL){
            state.currentState = runway_State::States::IDLE;
        }
        else if(state.currentState == runway_State::States::DEPART){
            state.currentState = runway_State::States::IDLE;
        }
    }

    void externalTransition(runway_State& state, double e) const override {
        if(!arrival->empty()){
            state.occupied = true;
            state.planeNum = arrival->getBag().back();
            std::cout << "Runway: plane number: " << state.planeNum << " arriving" << std::endl;
            state.currentState = runway_State::States::ARRIVAL;
        }
        else if(!depart->empty()){
            state.occupied = true;
            state.planeNum = depart->getBag().back();
            std::cout << "Runway: plane number: " << state.planeNum << " taking off" << std::endl;
            state.currentState = runway_State::States::DEPART;
        }
    }
    
    void output(const runway_State& state) const override {
        if(state.currentState == runway_State::States::ARRIVAL){
            exitA->addMessage(state.planeNum);
            std::cout << "Runway: plane number: " << state.planeNum << " sent to hangar" << std::endl;
        }
        else if(state.currentState == runway_State::States::DEPART){
            exitD->addMessage(state.planeNum);
            std::cout << "Runway: plane number: " << state.planeNum << " taken off" << std::endl;
        }
    }

    [[nodiscard]] double timeAdvance(const runway_State& state) const override {     
        if(state.currentState == runway_State::States::IDLE){
            return std::numeric_limits<double>::infinity();
        }
        else if(state.currentState == runway_State::States::ARRIVAL){
            return 5.0;
        }
        else if(state.currentState == runway_State::States::DEPART){
            return 5.0;
        }
    }
};
#endif
