/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#include "RealTimeActivityReactor.h"
#include "RealTimeActivityManager.h"
#include "VirtualTimeActivityManager.h"
#include "Defines.h"
#include <iostream>
#include <sstream>
#include "fwk/Exception.h"

using namespace Shipping;
using namespace std;

RealTimeActivityReactor::RealTimeActivityReactor(const std::string &_name,
    Fwk::Activity* _activity, RealTimeActivityManager::Ptr _rtam,
    VirtualTimeActivityManager::Ptr _vtam, Fwk::Time _vNextTime) :
    Fwk::Activity::Notifiee(_name,_activity),
    activity_(_activity),
    rtam_(_rtam),
    vtam_(_vtam),
    vNextTime_(_vNextTime) {}

void RealTimeActivityReactor::onStatus() {
    switch (activity_->status()) {
        case Fwk::Activity::executing: 
            DCOUT( "RTAR::onStatus: executing" << endl);
            vtam_->nowIs(vNextTime_);
            break;
        
	case Fwk::Activity::free:
	    throw Fwk::NoImplementationException("RTAR::onStatus: free. Should not have come here.");
	    /* Will not be called, since VTAM does enqueing and creates a 
	       reactor per activity. */
	    break;

        case Fwk::Activity::nextTimeScheduled:
            rtam_->lastActivityIs(activity_);
            break;
        
	default:
	    ostringstream s; 
            s << "RTAR::onStatus: invalid status. Should not come here.";
	    cerr << s.str() << endl;
            throw Fwk::UnknownTypeException(s.str());
    }
}

RealTimeActivityReactor::~RealTimeActivityReactor(){
    DCOUT( "RealTimeActivityReactor name = " << name() << " destructor" << endl);
}


