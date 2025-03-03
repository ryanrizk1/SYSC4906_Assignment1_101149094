#ifndef CONTROL_TOWER_HPP
#define CONTROL_TOWER_HPP

#include <random>
#include <iostream>
#include "cadmium/modeling/devs/atomic.hpp"

using namespace cadmium;

struct controlTower_State {
    double sigma;
    enum States {IDLE, ACTIVE};
    States currentState;
    int planeNum;
    explicit controlTower_State(): sigma(1), currentState(States::IDLE){
    }
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const controlTower_State& state) {
    out  << "{" << state.sigma << "}";
    return out;
}
#endif

class Control_Tower : public Atomic<controlTower_State> {
    public:
    Port<int> in_a;
    Port<int> in_d;
    Port<int> done_a;
    Port<int> done_d;
    Port<int> stop_a;
    Port<int> stop_d;
    Port<int> arrival;
    Port<int> depart;

    atomic_model(const std::string id) : Atomic<controlTower_State>(id, controlTower_State()) {
        in_a = addInputPort<int>("in_a");
        in_d = addInputPort<int>("in_d");
        done_a = addOutputPort<int>("done_a");
        done_d = addOutputPort<int>("done_d");
        stop_a = addOutputPort<int>("stop_a");
        stop_d = addOutputPort<int>("stop_d");
        arrival = addOutputPort<int>("arrival");
        depart = addOutputPort<int>("depart");
    }

    void internalTransition(controlTower_State& state) const override {
        if(state.currentState == controlTower_State::States::ACTIVE){
            state.currentState = controlTower_State::States::IDLE;
        }
    }

    void externalTransition(controlTower_State& state, double e) const override {
        if(!in_a->empty()){
            state.planeNum = in_a->getBag().back();
            state.currentState = controlTower_State::States::ACTIVE;
        }
        if(!in_d->empty()){
            state.planeNum = in_d->getBag().back();
            state.currentState = controlTower_State::States::ACTIVE;
        }
    }
    
    void output(const controlTower_State& state) const override {

    }

    [[nodiscard]] double timeAdvance(const controlTower_State& state) const override {     
        return state.sigma;
    }
};

#endif