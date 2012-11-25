//
//  FAR.h
//  Lab3
//
//  Created by cdelapaz on 11/20/12.
//  Copyright (c) 2012 cdelapaz. All rights reserved.
//

#ifndef __Lab3__FAR__
#define __Lab3__FAR__

#include <iostream>
#include "Activity.h"
#include "Segment.h"
#include "Defines.h"
#include "Fleet.h"
#include "Location.h"

namespace Shipping{
    
    class ForwardActivityReactor : public Fwk::Activity::Notifiee {
    public:
        
        //Constructor
        static ForwardActivityReactor::Ptr ForwardActivityReactorNew(const std::string &_name, NumPackages, Fwk::Activity*, Fwk::Ptr<Fwk::Activity::Manager>,
                                                                     Fwk::Ptr<Fleet>, Fwk::Ptr<Location>, Fwk::Ptr<Segment> , Fwk::Ptr<Shipment>);
 
        virtual void onStatus();
    
    private:
        
        //Constructors
        ForwardActivityReactor(const std::string &_name, NumPackages, Fwk::Activity*, Fwk::Ptr<Fwk::Activity::Manager>,
                               Fwk::Ptr<Fleet>, Fwk::Ptr<Location>, Fwk::Ptr<Segment> , Fwk::Ptr<Shipment>);
        ForwardActivityReactor();
        ForwardActivityReactor(const ForwardActivityReactor &);
    
        Fwk::Activity::Ptr activity_;
        Fwk::Ptr<Fleet> fleet_;
        Fwk::Ptr<Location> nextHop_;
        Fwk::Ptr<Shipment> shipment_;
        Fwk::Ptr<Segment> segment_;
        Fwk::Ptr<Fwk::Activity::Manager> vtManager_;
        
        NumPackages packagesInTransit_;                 //needed to keep track of segment usage by this activity
        
        void updateSegmentAndShipmentRecords();
        void scheduleActivity();
        
        
    };
}


#endif /* defined(__Lab3__FAR__) */
