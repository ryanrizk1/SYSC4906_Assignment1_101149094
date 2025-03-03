#ifndef AIRPORT_HPP
#define AIRPORT_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "Control.hpp"
#include "Runway.hpp"
#include "Queue.hpp"
#include "Hangar.hpp"

using namespace cadmium;

struct Airport : public Coupled {
    Port<int> in;
    Port<int> out;
    Airport(const std::string& id) : Coupled(id) {
        in = addInPort<int>("in");
        out = addOutPort<int>("out");

        auto control = addComponent<Control_Tower>("control");
        auto runway = addComponent<Runway>("runway");
        auto departQueue = addComponent<Queue>("departQueue");
        auto arrivalQueue = addComponent<Queue>("arrivalQueue");
        auto hangar = addComponent<Hangar>("hangar");

        addCoupling(control->done_a, arrivalQueue->done);
        addCoupling(control->stop_a, arrivalQueue->stop);
        addCoupling(control->done_d, departQueue->done);
        addCoupling(control->stop_d, departQueue->stop);
        addCoupling(control->arrival, runway->arrival);
        addCoupling(control->depart, runway->depart);

        addCoupling(runway->exitA, hangar->in);
        addCoupling(runway->exitD, this->out);

        addCoupling(hangar->out, departQueue->in);

        addCoupling(arrivalQueue->out, control->in_a);
        addCoupling(departQueue->out, control->in_d);

        addCoupling(this->in, arrivalQueue->in);
    }
};

#endif
