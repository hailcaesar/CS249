//
//  Shipment.cpp
//  Lab3
//
//  Created by cdelapaz on 11/19/12.
//  Copyright (c) 2012 cdelapaz. All rights reserved.
//

#include "Shipment.h"
#include "fwk/Activity.h"


using namespace Shipping;
using namespace std;


Shipment::Shipment(NumPackages _numPackages, Location::Ptr _destination){
    totalPackages_ = _numPackages;
    destination_ = _destination;
    shipmentStatus_ = Shipment::notCompleted_;
}


void Shipment::timeStartIs(Fwk::Time _timeStart) { timeStart_ = _timeStart;}
void Shipment::timeFinishIs(Fwk::Time _timeFinish) { timeFinish_ = _timeFinish;}

void Shipment::sentPackagesInc(NumPackages n){
    sentPackages_ = sentPackages_.value() + n.value();
}

void Shipment::sentPackagesDel(){
    sentPackages_ = 0;
}
