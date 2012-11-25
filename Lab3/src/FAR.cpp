//
//  FAR.cpp
//  Lab3
//
//  Created by cdelapaz on 11/20/12.
//  Copyright (c) 2012 cdelapaz. All rights reserved.
//

#include "FAR.h"
#include "Shipment.h"
#include "Network.h"
#include "Location.h"

using namespace Shipping;


ForwardActivityReactor::ForwardActivityReactor(const std::string &_name, NumPackages _packagesToBeSent, Fwk::Activity* _activity,
                                               Fwk::Ptr<Fwk::Activity::Manager> _vtManager,Fwk::Ptr<Fleet> _fleet, Fwk::Ptr<Location> _nextHop,
                                               Fwk::Ptr<Segment> _segment, Fwk::Ptr<Shipment> _shipment){
    Fwk::Activity::Notifiee(_name,_activity);
    fleet_ = _fleet;
    activity_ = _activity;
    vtManager_ = _vtManager;
    nextHop_ = _nextHop;
    shipment_ = _shipment;
    segment_ = _segment;
    packagesInTransit_ = 0;
}


void ForwardActivityReactor::onStatus() {
    try {
        segment_->packagesInTransitDec(packagesInTransit_);                                                     //Decrement any previous Shipments from segment
        
        if(activity_->status() == Fwk::Activity::executing) {                                                   //EXECUTING
            if(shipment_->waitingPackages().value() > 0){                                                       //--Packages need to be sent
                updateSegmentAndShipmentRecords();
                scheduleActivity();
            }
            else if(shipment_->waitingPackages().value() == 0){                                                 //--No more packages left
                if (shipment_->sentPackages() != shipment_->totalPackages()) 
                    DCOUT( "ERROR:  Something wrong with the algorithm" << std::endl);
        
                //DESTROY THIS ACTIVITY... HOW???
                segment_->shipmentDeq();                                                                        //--Remove Shipment from Segment
                
                if (nextHop_->name() == shipment_->destination()->name()){                                      //--Final dst reached
                    CustomerLocation::Ptr dst = shipment_->destination();
                    dst->recievedShipmentsInc();
                    shipment_->timeFinishIs(activity_->nextTime());
                    
                    Hours tripTime(shipment_->timeFinish().value() - shipment_->timeStart().value());
                    dst->totalLatencyIs(dst->totalLatency().value() + tripTime.value());                        //--Update Total Trip Time
                    dst->averageLatencyIs(dst->totalLatency().value() / dst->shipmentsReceived().value());      //--Average Trip Time
                    //Add cost!!!!!!!!!
                }
                else{                                                                                           //--Send to next-hop segment
                    shipment_->sentPackagesDel();
                   // network_->ShipmentNew(nextLocation_->name(), shipment_);
                }
            }
        }
        else if(activity_->status() == Fwk::Activity::nextTimeScheduled)                                        //NEXT_TIME_SCHEDULED
            vtManager_->lastActivityIs(activity_);                                                              //--add to vt manager
        
        else if(activity_->status() == Fwk::Activity::free){}
        else{
            DCOUT( "ERROR: FAR status not recognized" << std::endl);
            //THROW EXCEPTION!!!!!!!!!!!!
        }
    }
    catch (Fwk::Exception e) {
        //this.onNotificationException();           todo: fix this error
    }
}


void ForwardActivityReactor::updateSegmentAndShipmentRecords() {
    NumPackages txLimit;
    NumPackages segmentPackageLimit = segment_->capacity().value() - segment_->packagesInTransit().value();     //locks needed in segment?
    NumPackages fleetPackageLimit = fleet_->capacity(segment_->type());
    
    if(segmentPackageLimit < fleetPackageLimit) txLimit = segmentPackageLimit;
    else txLimit = fleetPackageLimit;
    
    if (txLimit.value() == 0) return;           // { TODO: FIX!!!!! WHAT DO WE DO IF SEGMENT CAPACITY IS FILLED??? WHEN DO WE SCHEDULE ACTIVITY TO RUN AGAIN?
    //  activity->nextTimeIs(????)
    //}
    
    if (shipment_->waitingPackages() > txLimit){
        packagesInTransit_ = txLimit;
        segment_->packagesInTransitInc(txLimit);
        shipment_->sentPackagesInc(txLimit);
    }
    else{
        packagesInTransit_ = shipment_->waitingPackages();
        segment_->packagesInTransitInc(shipment_->waitingPackages());
        shipment_->sentPackagesInc(shipment_->waitingPackages());
    }
};

void ForwardActivityReactor::scheduleActivity() {
    MilesPerHour segmentSpeed = fleet_->speed(segment_->type());
    Miles segmentLength = segment_->length();
    Time segmentTime = segmentLength.value() / segmentSpeed.value();
    activity_->nextTimeIs(Fwk::Time(activity_->nextTime().value() + segmentTime));         //old time + new time!???
    activity_->statusIs(Fwk::Activity::nextTimeScheduled);
};

