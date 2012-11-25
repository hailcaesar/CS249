/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#ifndef _STATS_H_
#define _STATS_H_

#include "Network.h"
#include <iostream>
#include "Defines.h"

namespace Shipping {
    class Network;
    class Stats : public Network::Notifiee {
        public:
	    typedef Fwk::Ptr<Stats const> PtrConst; 
	    typedef Fwk::Ptr<Stats> Ptr; 
            
	    static Stats::Ptr statsNew(const std::string & _name, Fwk::Ptr<Network> _network);
	   
	    /* Overriding virtual functions from Notifiee */
	    void onLocationNew(Location::PtrConst loc);
	    void onSegmentNew ( Segment::PtrConst );
	    void onLocationDel( Location::PtrConst );
	    void onSegmentDel ( Segment::PtrConst );
	    void onSegmentExpeditedSupportRemoval( Segment::PtrConst);
	    void onSegmentExpeditedSupportAddition( Segment::PtrConst);
	    
	    /* Accessors */
	    unsigned int truckSegments() const { return truckSegments_; } 
	    unsigned int boatSegments() const {return boatSegments_;}
	    unsigned int planeSegments() const {return planeSegments_; }

	    unsigned int expeditedSegments() const {return expeditedSegments_;}
	    unsigned int totalSegments() const {return totalSegments_; }
	    double expeditePercent() const; 
	    
	    unsigned int ports() const {return ports_;}
	    unsigned int customerLocations () const {return customerLocations_; }
	    unsigned int truckTerminals() const {return truckTerminals_ ; }
	    unsigned int boatTerminals ()const {return boatTerminals_; }
	    unsigned int planeTerminals() const {return planeTerminals_; }
	    
	private: 
	    ~Stats(){} 
	    Stats(); 
	    Stats(const Stats &);
	    Stats(const std::string &_name, Network::Ptr _network); 

	    unsigned int truckSegments_;
	    unsigned int boatSegments_;
	    unsigned int planeSegments_;

	    unsigned int expeditedSegments_;
	    unsigned int totalSegments_; 

	    unsigned int ports_; 
	    unsigned int customerLocations_; 
	    unsigned int truckTerminals_;
	    unsigned int boatTerminals_;
	    unsigned int planeTerminals_;
    };
}

#endif
