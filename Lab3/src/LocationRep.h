/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#ifndef _LOCATIONREP_H_
#define _LOCATIONREP_H_

#include "Instance.h"
#include "Network.h"

namespace Shipping {
    class LocationRep : public Instance {
	public:
	LocationRep(const string& _name, Ptr<Network> _network) :
        Instance(_name), network_(_network){}
    	    
        // Accessor
        string attribute(const string& _attr);
    	    
        // Mutator
        void attributeIs(const string& _attr, const string& _v);
	    
	virtual ~LocationRep(){}

    protected:
        Ptr<Network> network_;
        static const string segmentStr;
        static const int segmentStrlen; 
        int segmentNumber(const string& attr);
    	
    };
    
    class CustomerRep : public LocationRep {
    public:
        CustomerRep(const string &, Ptr<Network>);
        ~CustomerRep(); 
    protected:
        CustomerRep();
        CustomerRep(const CustomerRep &);
    };
    
    class PortRep : public LocationRep {
    public:
        PortRep(const string& name, Ptr<Network>);
        ~PortRep();
    protected:
        PortRep();
        PortRep(const PortRep &);
    };
    
    class TruckTerminalRep : public LocationRep {
    public:
        TruckTerminalRep(const string& name, Ptr<Network>);
        ~TruckTerminalRep();
    protected:
        TruckTerminalRep();
        TruckTerminalRep(const TruckTerminalRep &);
    };
    
    class BoatTerminalRep : public LocationRep {
    public:
        BoatTerminalRep(const string& name, Ptr<Network>);
        ~BoatTerminalRep();
    protected:
        BoatTerminalRep();
        BoatTerminalRep(const BoatTerminalRep &);
    };
    
    class PlaneTerminalRep : public LocationRep {
    public:
        PlaneTerminalRep(const string& name, Ptr<Network>);
        ~PlaneTerminalRep();
    protected:
        PlaneTerminalRep();
        PlaneTerminalRep(const PlaneTerminalRep &);
    };

}

#endif
