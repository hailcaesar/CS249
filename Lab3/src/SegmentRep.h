/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#ifndef _SEGMENTREP_H_
#define _SEGMENTREP_H_

#include "Network.h"
#include "Segment.h"

namespace Shipping {
    class SegmentRep : public Instance {
	public:
	    SegmentRep(const string &_name, Ptr<Network> _network): Instance(_name), network_(_network){}
            string attribute(const string &_attr);
            void attributeIs(const string& _attr, const string& _v);
	    virtual ~SegmentRep(){}
	protected:
	    SegmentRep();
	    SegmentRep(const SegmentRep &);
	    Ptr<Network> network_;
    };

    class TruckSegmentRep : public SegmentRep {
	public:
	    TruckSegmentRep(const string &_name, Ptr<Network> _network);
	    ~TruckSegmentRep(); 
	protected:
	    TruckSegmentRep();
	    TruckSegmentRep(const TruckSegment &);
    };

    class BoatSegmentRep : public SegmentRep {
	public:
	    BoatSegmentRep(const string &_name, Ptr<Network> _network);
	    ~BoatSegmentRep();
	protected:
	    BoatSegmentRep();
	    BoatSegmentRep(const BoatSegment &);
    };

    class PlaneSegmentRep : public SegmentRep {
	public:
	    PlaneSegmentRep(const string &_name, Ptr<Network> _network);
	    ~PlaneSegmentRep(); 
	protected:
	    PlaneSegmentRep();
	    PlaneSegmentRep(const PlaneSegmentRep &);
    };
}

#endif
