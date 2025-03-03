#ifndef CONTROL_TOWER_HPP
#define CONTROL_TOWER_HPP

#include <random>
#include <iostream>
#include "cadmium/modeling/devs/atomic.hpp"

using namespace cadmium;

struct controlTower_State {
    double sigma;
    enum States {IDLE, ACTIVE_ARRIVAL, ACTIVE_DEPART, DELAY, DONE};
    States currentState;
    int planeNum;
    bool occupied;
    explicit controlTower_State(): sigma(1), currentState(States::IDLE), occupied(false){
    }
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const controlTower_State& state) {
    out  << "{" << state.sigma << state.currentState << "}";
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

    Control_Tower(const std::string id) : Atomic<controlTower_State>(id, controlTower_State()) {
        in_a = addInPort<int>("in_a");
        in_d = addInPort<int>("in_d");
        done_a = addOutPort<int>("done_a");
        done_d = addOutPort<int>("done_d");
        stop_a = addOutPort<int>("stop_a");
        stop_d = addOutPort<int>("stop_d");
        arrival = addOutPort<int>("arrival");
        depart = addOutPort<int>("depart");
    }

    void internalTransition(controlTower_State& state) const override {
        if(state.currentState == controlTower_State::States::ACTIVE_ARRIVAL){
            state.currentState = controlTower_State::States::DELAY;
        }
        else if(state.currentState == controlTower_State::States::ACTIVE_DEPART){
            state.currentState = controlTower_State::States::DELAY;
        }
        else if(state.currentState == controlTower_State::States::DELAY){
            std::cout << "Control: Runway open again" << std::endl;
            state.occupied = false;
            state.currentState = controlTower_State::States::DONE;
        }
        else if(state.currentState == controlTower_State::States::DONE){
            state.currentState = controlTower_State::States::IDLE;
        }
    }

    void externalTransition(controlTower_State& state, double e) const override {
        if(!in_a->empty() && state.occupied == false){
            state.planeNum = in_a->getBag().back();
            state.occupied = true;
            std::cout << "Control: Plane number: " << state.planeNum << " going to arrivals" << std::endl;
            state.currentState = controlTower_State::States::ACTIVE_ARRIVAL;
        }
        else if(!in_d->empty() && state.occupied == false){
            state.planeNum = in_d->getBag().back();
            state.occupied = true;
            std::cout << "Control: Plane number: " << state.planeNum << " at departures" << std::endl;
            state.currentState = controlTower_State::States::ACTIVE_DEPART;
        }
    }
    
    void output(const controlTower_State& state) const override {
        if(state.currentState == controlTower_State::States::ACTIVE_ARRIVAL){
            std::cout << "Control: Plane number: " << state.planeNum << " sent to runway" << std::endl;
            stop_a->addMessage(1);
            stop_d->addMessage(1);
            arrival->addMessage(state.planeNum);
        }
        else if(state.currentState == controlTower_State::States::ACTIVE_DEPART){
            stop_a->addMessage(1);
            stop_d->addMessage(1);
            depart->addMessage(state.planeNum);
            std::cout << "Control: Plane number: " << state.planeNum << " sent to runway" << std::endl;
        }
        else if(state.currentState == controlTower_State::States::DONE){
            done_a->addMessage(1);
            done_d->addMessage(1);
            //std::cout << "Control: queue open" << std::endl;
        }
    }

    [[nodiscard]] double timeAdvance(const controlTower_State& state) const override {     
        if(state.currentState == controlTower_State::States::IDLE){
            return std::numeric_limits<double>::infinity();
        }
        else if(state.currentState == controlTower_State::States::ACTIVE_ARRIVAL){
            return 1.0;
        }
        else if(state.currentState == controlTower_State::States::ACTIVE_DEPART){
            return 1.0;
        }
        else if(state.currentState == controlTower_State::States::DELAY){
            return 6.0;
        }
        else if(state.currentState == controlTower_State::States::DONE){
            return 1.0;
        }
    }
};
#endif
