//
//  SegmentReactor.h
//  Lab3
//
//  Created by cdelapaz on 11/19/12.
//  Copyright (c) 2012 cdelapaz. All rights reserved.
//

#ifndef __Lab3__SegmentReactor__
#define __Lab3__SegmentReactor__
#include "Segment.h"
#include "Fwk.h"
#include "Fleet.h"
#include <iostream>

namespace Shipping {
    class Location;
    class Fleet;
    class Shipment;
    class VirtualTimeActivityManager;

    class SegmentReactor : public Segment::Notifiee {
    public:
        typedef Fwk::Ptr<SegmentReactor> Ptr;
        typedef Fwk::Ptr<SegmentReactor const> PtrConst;
        
        //Reactor Functions
        virtual void onShipmentEnq(Fwk::Ptr<Shipment>, Fwk::Ptr<Location>) ;
        virtual void onShipmentDeq();
        virtual void onPackagesInTransitInc(NumPackages);
        virtual void onPackagesInTransitDec(NumPackages);
        
        //Constructor and Destructor
        virtual ~SegmentReactor();
        static SegmentReactor::Ptr SegmentReactorNew(std::string,
                                                     Segment *,
                                                     Fwk::Ptr<VirtualTimeActivityManager>,
                                                     Fwk::Ptr<Fleet>);
    protected:
        SegmentReactor(std::string, Segment*, Fwk::Ptr<VirtualTimeActivityManager>, Fwk::Ptr<Fleet>);
        SegmentReactor();
        SegmentReactor(const SegmentReactor&);
        
        Fwk::Ptr<Fleet> fleet_;
        Fwk::Ptr<VirtualTimeActivityManager> vtManager_;
        Segment * segment_;
    
        void sendShipment();
        void activityNew(Shipment::Ptr, Location::Ptr);
        
    };
};

#endif 
