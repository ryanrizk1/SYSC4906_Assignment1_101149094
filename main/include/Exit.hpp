#ifndef EXIT_HPP
#define EXIT_HPP

#include <random>
#include <iostream>
#include <list>
#include "cadmium/modeling/devs/atomic.hpp"

using namespace cadmium;

struct exit_State {
    double sigma;
    enum States {IDLE, ACTIVE};
    States currentState;
    mutable std::list<int> elements;
    explicit exit_State(): sigma(1), currentState(States::IDLE){
    }
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const exit_State& state) {
    out  << "{" << state.sigma << state.currentState << "}";
    return out;
}
#endif

class Exit : public Atomic<exit_State> {
    public:
    Port<int> in1;
    Port<int> in2;
    Port<int> in3;
    Port<int> in4;
    Port<int> out;

    Exit(const std::string id) : Atomic<exit_State>(id, exit_State()) {
        state.elements.begin();
        in1 = addInPort<int>("in1");
        in2 = addInPort<int>("in2");
        in3 = addInPort<int>("in3");
        in4 = addInPort<int>("in4");
        out = addOutPort<int>("out");
    }

    void internalTransition(exit_State& state) const override {
        if(state.currentState == exit_State::States::ACTIVE){
            state.currentState = exit_State::States::IDLE;
        }
    }

    void externalTransition(exit_State& state, double e) const override {
        if(!in1->empty()){
            state.elements.push_back(in1->getBag().back());
            state.currentState = exit_State::States::ACTIVE;
        }
        else if(!in2->empty()){
            state.elements.push_back(in2->getBag().back());
            state.currentState = exit_State::States::ACTIVE;
        }
        else if(!in3->empty()){
            state.elements.push_back(in3->getBag().back());
            state.currentState = exit_State::States::ACTIVE;
        }
        else if(!in4->empty()){
            state.elements.push_back(in4->getBag().back());
            state.currentState = exit_State::States::ACTIVE;
        }
    }
    
    void output(const exit_State& state) const override {
        if(state.currentState == exit_State::States::ACTIVE){
            if(state.elements.size() > 0){
                out->addMessage(state.elements.front());
                std::cout << "Exit: plane number: " << state.elements.front() << " sent to departure queue" << std::endl;
                state.elements.pop_front();
            }
        }        
    }

    [[nodiscard]] double timeAdvance(const exit_State& state) const override {     
        if(state.currentState == exit_State::States::IDLE){
            return std::numeric_limits<double>::infinity();
        }
        else if(state.currentState == exit_State::States::ACTIVE){
            return 1.0;
        }
    }
};

#endif