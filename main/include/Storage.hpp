#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <random>
#include <iostream>
#include <list>
#include "cadmium/modeling/devs/atomic.hpp"

using namespace cadmium;

struct storage_State {
    double sigma;
    enum States {IDLE, ACTIVE};
    States currentState;
    mutable std::list<int> elements;
    double delay;
    explicit storage_State(): sigma(1), currentState(States::IDLE), delay(0){
    }
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const storage_State& state) {
    out  << "{" << state.sigma << state.currentState << "}";
    return out;
}
#endif

class Storage : public Atomic<storage_State> {
    public:
    Port<int> in;
    Port<int> out;

    Storage(const std::string id) : Atomic<storage_State>(id, storage_State()) {
        state.elements.begin();
        in = addInPort<int>("in");
        out = addOutPort<int>("out");
    }

    void internalTransition(storage_State& state) const override {
        if(state.currentState == storage_State::States::ACTIVE){
            if(state.elements.empty()){
                state.currentState = storage_State::States::IDLE;
            } else {
                state.delay = (state.elements.front() / 20);
                state.currentState = storage_State::States::ACTIVE;
            }
        }
    }

    void externalTransition(storage_State& state, double e) const override {
        if(!in->empty()){
            state.elements.push_back(in->getBag().back());
            state.delay = (state.elements.front() / 20);
            std::cout << "Storage: plane number: " << state.elements.front() << " stored" << std::endl;
            state.currentState = storage_State::States::ACTIVE;
        }
    }

    void output(const storage_State& state) const override {
        if(state.currentState == storage_State::States::ACTIVE){
            std::cout << "Storage: plane number" << state.elements.front() << " sent to exit" << std::endl;
            out->addMessage(state.elements.front());
            state.elements.pop_front();
        }
    }

    [[nodiscard]] double timeAdvance(const storage_State& state) const override {     
        if(state.currentState == storage_State::States::IDLE){
            return std::numeric_limits<double>::infinity();
        }
        else if(state.currentState == storage_State::States::ACTIVE){
            return state.delay;
        }
    }
};

#endif
