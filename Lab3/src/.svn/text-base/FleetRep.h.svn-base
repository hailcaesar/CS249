/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#ifndef _FLEETREP_H
#define _FLEETREP_H

#include "Instance.h"
#include "Network.h"
#include "Fleet.h"

namespace Shipping {
    class FleetRep : public Instance {
	public:
	    FleetRep(const string& _name, Ptr<Network> _network);
    	    string attribute(const string& _attr);
    	    void attributeIs(const string& _attr, const string& _v);
    	protected:
    	    FleetRep();
    	    FleetRep(const FleetRep &);
	    Ptr<Network> network_; 
    	    struct FleetAttribute{
    	        Fleet::Type type_;
    	        string prop_;
    	    };
    	    FleetAttribute parseFleetAttribute(const string & _attr);
    };
}

#endif 
