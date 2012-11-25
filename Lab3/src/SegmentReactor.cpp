//
//  SegmentReactor.cpp
//  Lab3
//
//  Created by cdelapaz on 11/19/12.
//  Copyright (c) 2012 cdelapaz. All rights reserved.
//
#include "Location.h"
#include "Network.h"
#include "SegmentReactor.h"
#include "Shipment.h"
#include "VirtualTimeActivityManager.h"
#include <iostream>
#include <sstream>
#include "fwk/Exception.h"

using namespace std;
using namespace Shipping;

SegmentReactor::SegmentReactor(std::string _name, Segment* _segment, Fwk::Ptr<VirtualTimeActivityManager> _vtManager, Fwk::Ptr<Fleet> _fleet) :
    Notifiee(_name, _segment){
        segment_ = _segment;
        vtManager_ = _vtManager;
        fleet_ = _fleet;
};

SegmentReactor::Ptr SegmentReactor::SegmentReactorNew(std::string _name,
                                                      Segment * _segment,
                                                      Fwk::Ptr<VirtualTimeActivityManager> _vtManager,
                                                      Fwk::Ptr<Fleet> _fleet) {
    SegmentReactor::Ptr segReactor = new SegmentReactor(_name, _segment, _vtManager, _fleet);
    if (segReactor == NULL){ 
	ostringstream s; 
	s << "SegmentReactor::SegmentReactorNew: could not create a new segment reactor"; 
	cerr << s.str() << endl; 
	throw Fwk::MemoryException(s.str());
    }
    return segReactor;
};

SegmentReactor::~SegmentReactor() {};


void SegmentReactor::onShipmentEnq(Shipment::Ptr _shipment, Location::Ptr _dest) {
    if (segment_->packagesInTransit().value() < segment_->capacity().value())
        activityNew(_shipment, _dest);
}

void SegmentReactor::onShipmentDeq() {
    sendShipment();
};

void SegmentReactor::onPackagesInTransitInc(NumPackages n) {
    sendShipment();
};

void SegmentReactor::onPackagesInTransitDec(NumPackages n) {};

void SegmentReactor::activityNew(Shipment::Ptr _shipment, Location::Ptr _nextHop) {
    
    NumPackages txLimit, txNumPkgs;
    NumPackages segmentPackageLimit = segment_->capacity().value() - segment_->packagesInTransit().value();
    //NumPackages fleetPackageLimit = fleet_->capacity(segment_->type());  //FIX
    NumPackages fleetPackageLimit = segmentPackageLimit.value();
    
    if(segmentPackageLimit < fleetPackageLimit) txLimit = segmentPackageLimit;
    else txLimit = fleetPackageLimit;

    if (txLimit <= 0) return;
    
    if(txLimit > _shipment->waitingPackages()) txNumPkgs = _shipment->waitingPackages();
    else txNumPkgs = txLimit;

    
    //_shipment->inProgressPackagesInc(txNumPkgs);          //not needed?
    

    //Create Activity with #txNumPkts number of packets to "_dest"

};

void SegmentReactor::sendShipment() {

};
