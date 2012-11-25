/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <iostream>
#include "Segment.h"
#include "Location.h"
#include "Fleet.h"
#include "ShippingValueTypes.h"
#include "Conn.h"
#include "fwk/NamedInterface.h"
#include "fwk/BaseNotifiee.h"
#include "fwk/Ptr.h"
#include "fwk/PtrInterface.h"
#include <map>
#include "RealTimeActivityManager.h"
#include "VirtualTimeActivityManager.h"

namespace Shipping{
    class Conn; 
    class Network : public Fwk::NamedInterface {
	public:
        typedef Fwk::Ptr<Network const> PtrConst; 
        typedef Fwk::Ptr<Network> Ptr; 
        
        static Network::Ptr networkNew(std::string _name);
    
        //Mutators
        void segmentIs(const std::string & _name, Fwk::Ptr<Segment> _segment);
        void locationIs(const std::string & _name, Fwk::Ptr<Location> _location);
        void fleetIs(Fwk::Ptr<Fleet> _fleet);
        void segmentExpeditedSupportIs(const std::string & _name, Segment::ExpeditedSupport es);
        
        void segmentDel(const std::string & _name);
        void locationDel(const std::string & _name);
        
        //Accessors
        Fwk::Ptr<Location> location(const std::string & _name);
        size_t numLocations(){return location_.size();}
	Fwk::Ptr<Segment> segment(const std::string & _name);
	Fwk::Ptr<Fleet> fleet() const { return fleet_; }
	RealTimeActivityManager::Ptr	realTimeActivityManager() const { return realTimeActivityManager_; }
	VirtualTimeActivityManager::Ptr virtualTimeActivityManager() const { return virtualTimeActivityManager_; }
        
        //Iterators
        typedef std::map<const std::string, Location::Ptr >::iterator LocationIt;
        LocationIt locItBegin() { return location_.begin(); }
        LocationIt locItEnd(){ return location_.end(); }
	   
        class Notifiee : public Fwk::BaseNotifiee<Network> {
		public:
		    typedef Fwk::Ptr<Notifiee const> PtrConst;
		    typedef Fwk::Ptr<Notifiee> Ptr;
		    
		    Notifiee(const std::string & _name, Network::Ptr _network):
			    Fwk::BaseNotifiee<Network>(_name, _network){}
    	    	    
		    virtual void onLocationNew( Location::PtrConst ){}
		    virtual void onSegmentNew ( Segment::PtrConst ){}
            	    virtual void onLocationDel( Location::PtrConst ){}
            	    virtual void onSegmentDel ( Segment::PtrConst ){}
		    virtual void onSegmentExpeditedSupportRemoval( Segment::PtrConst){}
		    virtual void onSegmentExpeditedSupportAddition( Segment::PtrConst){}
		    virtual ~Notifiee() {}
    	    	protected:
		    Notifiee(); 
		    Notifiee(const Notifiee &);
    	    };
	    void notifieeIs(const std::string & _name, Notifiee* _notifiee);	

    private:
        Network();
        Network(const Network &);
        Network(std::string _name); 

        std::map<const std::string, Segment::Ptr > segment_;
        std::map<const std::string, Location::Ptr > location_;
        std::map<const std::string, Network::Notifiee::Ptr> notifiee_;
	typedef std::map<const std::string, Network::Notifiee::Ptr>::iterator notifieeIter;
	RealTimeActivityManager::Ptr realTimeActivityManager_; 
	VirtualTimeActivityManager::Ptr virtualTimeActivityManager_; 
        Fwk::Ptr<Fleet> fleet_; 
    };
}

#endif 
