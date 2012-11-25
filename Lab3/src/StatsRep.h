/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#ifndef _STATSREP_H_
#define _STATSREP_H_

#include "Instance.h"
#include "Network.h"
#include "Stats.h"

namespace Shipping {
    class StatsRep : public Instance {
	public:
    	    StatsRep(const string& _name, Ptr<Network> _network);
    	    string attribute(const string& _attr);
    	    void attributeIs(const string& _name, const string& _v);
    	protected:
	    StatsRep(); 
	    StatsRep(const StatsRep &);
    	    Ptr<Stats> stats_;  
    };
}

#endif 
