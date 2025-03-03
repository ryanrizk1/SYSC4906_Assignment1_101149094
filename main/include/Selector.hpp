#ifndef SELECTOR_HPP
#define SELECTOR_HPP

#include <random>
#include <iostream>
#include "cadmium/modeling/devs/atomic.hpp"

using namespace cadmium;

struct selector_State {
    double sigma;
    enum States {IDLE, ACTIVE};
    States currentState;
    int id;
    explicit selector_State(): sigma(1), currentState(States::IDLE), id(0){
    }
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const selector_State& state) {
    out  << "{" << state.sigma << state.currentState << "}";
    return out;
}
#endif

class Selector : public Atomic<selector_State> {
    public:
    Port<int> in;
    Port<int> out1;
    Port<int> out2;
    Port<int> out3;
    Port<int> out4;

    Selector(const std::string id) : Atomic<selector_State>(id, selector_State()) {
        in = addInPort<int>("in");
        out1 = addOutPort<int>("out1");
        out2 = addOutPort<int>("out2");
        out3 = addOutPort<int>("out3");
        out4 = addOutPort<int>("out4");
    }

    void internalTransition(selector_State& state) const override {
        if(state.currentState == selector_State::States::ACTIVE){
            state.currentState = selector_State::States::IDLE;
        }
    }

    void externalTransition(selector_State& state, double e) const override {
        if(!in->empty()){
            state.id = in->getBag().back();
            state.currentState = selector_State::States::ACTIVE;
        }
    }
    
    void output(const selector_State& state) const override {
        if(state.id <= 254){
            out1->addMessage(state.id);
            std::cout << "Selector: sent to plane number: " << state.id << " to storage 1" << std::endl;
        }
        else if(state.id > 254 && state.id <= 499){
            out2->addMessage(state.id);
            std::cout << "Selector: sent to plane number: " << state.id << " to storage 2" << std::endl;
        }
        else if(state.id > 499 && state.id <= 754){
            out3->addMessage(state.id);
            std::cout << "Selector: sent to plane number: " << state.id << " to storage 3" << std::endl;
        }
        else if(state.id > 754 && state.id <= 1000){
            out4->addMessage(state.id);
            std::cout << "Selector: sent to plane number: " << state.id << " to storage 4" << std::endl;
        }
    }

    [[nodiscard]] double timeAdvance(const selector_State& state) const override {     
        if(state.currentState == selector_State::States::IDLE){
            return std::numeric_limits<double>::infinity(); 
        }
        else if(state.currentState == selector_State::States::ACTIVE){
            return 1.0;
        }
    }
};

#endif