#ifndef SAMPLE_TOP_HPP
#define SAMPLE_TOP_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "Airport.hpp"
#include "Generator.hpp"

using namespace cadmium;

struct top_coupled : public Coupled {
    top_coupled(const std::string& id) : Coupled(id) {
        auto airport = addComponent<Airport>("airport");
        auto generator = addComponent<Generator>("generator");

        addCoupling(generator->out, airport->in);
    }
};

#endif