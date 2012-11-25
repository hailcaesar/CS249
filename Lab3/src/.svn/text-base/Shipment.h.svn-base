//
//  Shipment.h
//  Lab3
//
//  Created by cdelapaz on 11/19/12.
//  Copyright (c) 2012 cdelapaz. All rights reserved.
//

#ifndef __Lab3__Shipment__
#define __Lab3__Shipment__

#include <iostream>
#include "ShippingValueTypes.h"
#include "Fwk.h"
#include "Defines.h"
#include "Location.h"
#include "fwk/Activity.h"


namespace Shipping {
    class Time;
    class Location;
    class Shipment : public Fwk::PtrInterface<Shipment> {
    public:
        typedef Fwk::Ptr<Shipment const> PtrConst;
        typedef Fwk::Ptr<Shipment> Ptr;

        //Enum
        enum TransferStatus{completed_, notCompleted_};

        //Constructor
        Shipment(NumPackages, Fwk::Ptr<Location>);


        //Accessors
        Fwk::Ptr<Location> destination(){ return destination_; }
        Fwk::Time timeStart() const { return timeStart_; }
        Fwk::Time timeFinish() const { return timeFinish_; }
        TransferStatus transferStatus() const { return shipmentStatus_;}

        NumPackages totalPackages() const { return totalPackages_; }
        NumPackages waitingPackages() const {return (totalPackages_.value() - sentPackages_.value());}
        NumPackages sentPackages() const { return sentPackages_; }
        

        //Mutators
        void timeFinishIs(Fwk::Time);
        void timeStartIs(Fwk::Time);
        void transferStatusIs(TransferStatus);

        void sentPackagesInc(NumPackages);
        void sentPackagesDel();

    protected:
        Fwk::Time timeStart_;
        Fwk::Time timeFinish_;
        TransferStatus shipmentStatus_;
        
        NumPackages sentPackages_;
        NumPackages waitingPackages_;
        NumPackages totalPackages_;
        
        Fwk::Ptr<Location> destination_;

    };
}

                                             
#endif /* defined(__Lab3__Shipment__) */
