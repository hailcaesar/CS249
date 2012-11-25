/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#include "InjectActivityReactor.h"
#include "Shipment.h"
#include "Location.h"
#include <iostream>

using namespace Shipping; 
using namespace std;

InjectActivityReactor::InjectActivityReactor(	
    const string& _iarName, const string& _srcName, const string& _dstName, 
    TransferRate _transferRate, NumPackages _shipmentSize, Fwk::Ptr<Network> _network, 	
    Fwk::Ptr<VirtualTimeActivityManager> _vtam, Fwk::Activity::Ptr _activity ) :
	Fwk::Activity::Notifiee(_iarName, _activity.ptr()),
    	srcName_(_srcName),
    	dstName_(_dstName), 
    	transferRate_(_transferRate),
    	shipmentSize_(_shipmentSize),
    	network_(_network),
    	vtam_(_vtam),
    	activity_(_activity) {}

void InjectActivityReactor::dstNameIs(const string& _dstName) {
    if (dstName_ != _dstName)
	dstName_ = _dstName;
}

void InjectActivityReactor::transferRateIs(TransferRate _transferRate) {
    if (transferRate_ != _transferRate)
	transferRate_ = _transferRate;
}

void InjectActivityReactor::shipmentSizeIs(NumPackages _shipmentSize) {
    if (shipmentSize_ != _shipmentSize) 
	shipmentSize_ = _shipmentSize;
}

void InjectActivityReactor::onStatus() {
    switch(activity_->status()) {
	case Fwk::Activity::executing: {
    	    DCOUT( "InjectActivityReactor::onStatus: New shipment from" << srcName_ << " to " << 
		dstName_ << " of size = " << shipmentSize_.value());
	    
	    Fwk::Ptr<Location> dst = network_->location(dstName_);
	    Fwk::Ptr<Location> src = network_->location(srcName_);

    	    Shipment::Ptr s = new Shipment(shipmentSize_, dst);
    	    s->timeStartIs(activity_->nextTime());
	    //TODO : from here
	    //  do we need to update any shipment stats here?
	    // basically initialize them somehow?
    	    break;
	}
    	case Fwk::Activity::free: {
    	    DCOUT( "InjectActivityReactor::onStatus: in free: re enqueuing injection activity." << endl);
	    
	    Fwk::Time nextTime = activity_->nextTime().value() + (double)HOURS_PER_DAY/transferRate_.value();
	    /* Since transferRate is number of Shipments per day */
	    
	    activity_->nextTimeIs(nextTime); 
    	    activity_->statusIs(Fwk::Activity::nextTimeScheduled);
    	    break;
	}
    	case Fwk::Activity::nextTimeScheduled: {
    	    DCOUT( "InjectActivityReactor::onStatus: in nextTimeScheduled: scheduling activity." << endl);
    	    vtam_->lastActivityIs(activity_);
    	    break;
	}
    	default: {
	    // Reactor => should not throw exception.
	    cerr << "InjectActivityReactor::onStatus: Should not come to this activity status = Enum State " << activity_->status() << endl;
	}
    }
}
