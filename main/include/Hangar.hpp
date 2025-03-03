#ifndef HANGAR_HPP
#define HANGAR_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "Selector.hpp"
#include "Storage.hpp"
#include "Exit.hpp"

using namespace cadmium;

struct Hangar : public Coupled {
    Port<int> in;
    Port<int> out;
    Hangar(const std::string& id) : Coupled(id) {
        in = addInPort<int>("in");
        out = addOutPort<int>("out");
        
        auto selector = addComponent<Selector>("selector");
        auto storage1 = addComponent<Storage>("storage1");
        auto storage2 = addComponent<Storage>("storage2");
        auto storage3 = addComponent<Storage>("storage3");
        auto storage4 = addComponent<Storage>("storage4");
        auto exit = addComponent<Exit>("exit");

        addCoupling(selector->out1, storage1->in);
        addCoupling(selector->out2, storage2->in);
        addCoupling(selector->out3, storage3->in);
        addCoupling(selector->out4, storage4->in);

        addCoupling(storage1->out, exit->in1);
        addCoupling(storage2->out, exit->in2);
        addCoupling(storage3->out, exit->in3);
        addCoupling(storage4->out, exit->in4);

        addCoupling(this->in, selector->in);
        addCoupling(exit->out, this->out);
    }
};

#endif
