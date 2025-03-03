#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <random>
#include <iostream>
#include <limits>
#include <list>
#include "cadmium/modeling/devs/atomic.hpp"

using namespace cadmium;

struct queue_State {
    double sigma;
    enum States {IDLE, OPEN, OCCUPIED};
    States currentState;
    int occupied;
    mutable std::list<int> elements;
    explicit queue_State(): sigma(1), occupied(0), currentState(States::OPEN){
    }
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const queue_State& state) {
    out  << "{" << state.sigma << state.currentState << "}";
    return out;
}
#endif

class Queue : public Atomic<queue_State> {
    public:
    Port<int> in;
    Port<int> stop;
    Port<int> done;
    Port<int> out;

    Queue(const std::string id) : Atomic<queue_State>(id, queue_State()) {
        state.elements.begin();
        in = addInPort<int>("in");
        stop = addInPort<int>("stop");
        done = addInPort<int>("done");
        out = addOutPort<int>("out");
    }

    void internalTransition(queue_State& state) const override {
        if(state.currentState == queue_State::States::OCCUPIED){
            state.occupied = 0;
            state.currentState = queue_State::States::OPEN;
        }
        else if(state.currentState == queue_State::States::OPEN){
            state.currentState = queue_State::States::IDLE;
        }
    }

    void externalTransition(queue_State& state, double e) const override {
        if(!in->empty()){
            state.elements.push_back(in->getBag().back());
            std::cout << "Queue: plane number: " << state.elements.front() << " received" << std::endl;
            if(state.occupied == 0){
                state.currentState = queue_State::States::OPEN;
            } else {
                state.currentState = queue_State::States::OCCUPIED;
            }
        }
        else if(!done->empty()){
            std::cout << "Queue: open" << std::endl;
            state.occupied = 0;
            state.currentState = queue_State::States::OPEN;
        }
        else if(!stop->empty()){
            std::cout << "Queue: occupied" << std::endl;
            state.occupied = 1;
            state.currentState = queue_State::States::OCCUPIED;
        }
    }
    
    void output(const queue_State& state) const override {
        if(state.currentState == queue_State::States::OPEN  && state.occupied == 0){
            if(state.elements.size() > 0){
                out->addMessage(state.elements.front());
                std::cout << "Queue: plane number: " << state.elements.front() << " sent to control tower" << std::endl;
                state.elements.pop_front();
            }
        }
    }

    [[nodiscard]] double timeAdvance(const queue_State& state) const override {     
        if(state.currentState == queue_State::States::IDLE){
            return std::numeric_limits<double>::infinity();
        }
        else if(state.currentState == queue_State::States::OCCUPIED){
            return std::numeric_limits<double>::infinity();
        }
        else if(state.currentState == queue_State::States::OPEN){
            return 1.0;
        }
    }
};
#endif
