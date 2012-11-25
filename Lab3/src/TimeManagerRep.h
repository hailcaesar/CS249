/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#ifndef _TIMEMANAGERREP_H
#define _TIMEMANAGERREP_H

#include "Instance.h"

namespace Shipping {
    class Network;
    class TimeManagerRep : public Instance {
    public:
        TimeManagerRep(const std::string& _name, Fwk::Ptr<Network> network);
        std::string attribute(const std::string& _attr);
        void attributeIs(const std::string& _attr, const std::string& _v);
        ~TimeManagerRep() {}
    private:
        TimeManagerRep();
        TimeManagerRep(const TimeManagerRep &);

        Fwk::Ptr<Network> network_;
    };
}

#endif
