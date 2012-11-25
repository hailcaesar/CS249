/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#include "CustomerReactor.h"
#include "Network.h"
#include "ShippingValueTypes.h"
#include "fwk/Exception.h"
#include <iostream>
#include <sstream>

using namespace Shipping; 
using namespace std; 


CustomerReactor::CustomerReactor(   const string& _name, CustomerLocation * _notifier,
    VirtualTimeActivityManager::Ptr _vtam, Network::Ptr _network) : 
    CustomerLocation::Notifiee(_name, _notifier),
    status_(notUpdated_), vtam_(_vtam), network_(_network){
    DCOUT( "CustomerReactor constructor, name = " << name() << " Notifier: " << notifier()->name() << endl);  
    iar_ = NULL;  
    activity_ = NULL; 
}

CustomerReactor::Ptr CustomerReactor::CustomerReactorNew( const string& _name, CustomerLocation *_notifier,
    VirtualTimeActivityManager::Ptr _vtam, Network::Ptr _network) {
    CustomerReactor::Ptr cr = new CustomerReactor(_name,  _notifier, _vtam, _network);
    return cr;
}

void CustomerReactor::onUpdate(){
    
    TransferRate transferRate = notifier()->transferRate(); 
    string dstName = notifier()->destination(); 
    NumPackages shipmentSize = notifier()->shipmentSize(); 
    string activityName = this->name() + string("InjectActivity"); 
    string iarName = this->name() + string("InjectActivityReactor"); 
    string srcName = notifier()->name(); 

    switch(status_){
	case notUpdated_: {
	    
	    if (transferRate.value() != TransferRate::min() && dstName != "" && shipmentSize.value() != NumPackages::min()) {
                    DCOUT( "CustomerReactor::onUpdate: all attributes updated. Transitioning to fullyUpdated status." << endl);
                    status_ = fullyUpdated_;
		    if(activity_ == NULL) {
			activity_ = vtam_->activityNew(activityName); 
		    }
                    if(iar_ == NULL) {
			iar_ = new InjectActivityReactor(iarName, srcName, dstName, transferRate, shipmentSize, 
							network_, vtam_, activity_); 
		    }
                    activity_->notifieeIs(iarName, iar_.ptr());
                    activity_->nextTimeIs(vtam_->now());
                    activity_->statusIs(Fwk::Activity::nextTimeScheduled);
            } else {
                DCOUT( "CustomerReactor::onUpdate: all attributes NOT updated. Retaining notUpdated status." << endl);
		status_ = notUpdated_; 
            }
	    break;
	}
	
	case fullyUpdated_:{
            if (transferRate.value() == TransferRate::min() || dstName == "" || shipmentSize.value() == NumPackages::min()) {
                DCOUT( "CustomerReactor::onUpdate: some attribute is NOT updated. Transitioning to notUpdated status." << endl);
                status_ = notUpdated_;
                if(activity_ != NULL){
		    activity_->notifieeIs("", NULL); 
		    vtam_->activityDel(activity_->name());
		    activity_ = NULL;
		}
                iar_ = NULL;
            } else {
                DCOUT( "CustomerReactor::onUpdate: Some updated attribute value vas changed. Updating the InjectActivityReactor." << endl);
                iar_->transferRateIs(transferRate);
                iar_->dstNameIs(dstName);
                iar_->shipmentSizeIs(shipmentSize);
		status_ = fullyUpdated_; 
            }
	    break;
	}
	
	default: {
	    // Reactor => don't throw exception
	    cerr << "CustomerReactor::onUpdate: Should not transition here. Illegal state." << endl;
	}    
    }
}
