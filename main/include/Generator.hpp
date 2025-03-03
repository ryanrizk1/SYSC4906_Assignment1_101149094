#ifndef JOB_GENERATOR_MODEL_HPP
#define JOB_GENERATOR_MODEL_HPP

#include <iostream>
#include <list>
#include "cadmium/modeling/devs/atomic.hpp"

using namespace cadmium;

struct Job_generator_modelState {
    double sigma;                     
    enum states {IDLE, SENDING};
    std::vector<int> jobQueue;   
    size_t currentJobIndex;           

    Job_generator_modelState() : sigma(1.0), currentJobIndex(0) {jobQueue = {21, 273, 304, 429};
    }
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const Job_generator_modelState& state) {
    out << "{" << state.sigma << "}";
    return out;
}
#endif

class Generator : public Atomic<Job_generator_modelState> {
public:
    Port<int> out; 

    Generator(const std::string id) : Atomic<Job_generator_modelState>(id, Job_generator_modelState()) {
        out = addOutPort<int>("out");
    }

    void internalTransition(Job_generator_modelState& state) const override {
        //state.sigma = std::numeric_limits<double>::infinity();
        state.sigma = 6.0;    
        state.currentJobIndex += 1;
    }

    void externalTransition(Job_generator_modelState& state, double e) const override {

    }

    void output(const Job_generator_modelState& state) const override {
        if (state.currentJobIndex < state.jobQueue.size()) {
            int nextJob = state.jobQueue[state.currentJobIndex];
            std::cout << "Generator: new arriving plane number: " << nextJob << std::endl;
            out->addMessage(nextJob);
        }
    }

    [[nodiscard]] double timeAdvance(const Job_generator_modelState& state) const override {
        return state.sigma;
    }
};
#endif