/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#ifndef _SEGMENT_H_
#define _SEGMENT_H_

#include <iostream>
#include <string>

#include "Fwk.h"
#include "ShippingValueTypes.h"
#include "Shipment.h"
#include "VirtualTimeActivityManager.h"
#include <vector>

#define DEFAULT_CAPACITY  10

namespace Shipping {
    class Shipment;
    class Location;
    
    struct shipmentElement {
        Fwk::Ptr<Shipment> shipment;
        Fwk::Ptr<Location> nextLocation;
    };
    
    class Segment : public Fwk::NamedInterface {
    public:
        typedef Fwk::Ptr<Segment const> PtrConst;
        typedef Fwk::Ptr<Segment> Ptr;
            
        //Enums
        enum ExpeditedSupport {SupportAbsent_, SupportPresent_};
        enum Type {plane_ = 0, truck_ = 1, boat_ = 2};
        static ExpeditedSupport SupportPresent() { return SupportPresent_; }
        static ExpeditedSupport SupportAbsent() { return SupportAbsent_; }

       // Accessors
        std::string stringType(Type t) const;
        DifficultyLevel difficulty() const { return difficulty_; }
        ExpeditedSupport expeditedSupport() const { return expeditedSupport_; }
        Miles length() const { return length_; }
        Segment::Ptr returnSegment() const { return returnSegment_;}
        size_t shipments() const { return shipment_.size();};
        Fwk::Ptr<Location> source() const { return source_;}
        Segment::Type type() const { return type_;}
        NumPackages capacity() const { return capacity_;};
        NumPackages packagesInTransit() const { return packagesInTransit_;};

       

        //Mutators
        void difficultyIs(DifficultyLevel _difficulty);
        void expeditedSupportIs(ExpeditedSupport _es);
        void lengthIs(Miles _length);
        void returnSegmentIs(Segment::Ptr _returnSegment);
        void sourceIs(Fwk::Ptr<Location> _source);
        NumShipments recievedShipments() const { return recievedShipments_; }
        
        void packagesInTransitInc(NumPackages n);
        void packagesInTransitDec(NumPackages n);
        
        //Instantatiating Attributes
        void refusedShipmentsInc();
        void shipmentEnq();
        void shipmentDeq();
        typedef std::vector<shipmentElement>::const_iterator ShipmentIteratorConst;
        ShipmentIteratorConst shipmentIterConst() const { return shipment_.begin(); };
        
        class Notifiee : public Fwk::BaseNotifiee<Segment> {
        public:
            typedef Fwk::Ptr<Segment::Notifiee> Ptr;
            typedef Fwk::Ptr<Segment::Notifiee const> PtrConst;

            
            //Destructor
            virtual ~Notifiee();
            
            //Notifee Functions
            virtual void onShipmentDeq();
            virtual void onShipmentEnq(Fwk::Ptr<Shipment>, Fwk::Ptr<Location>);
            virtual void onActivePackageDec(NumPackages);
            virtual void onActivePackageInc(NumPackages);

            
            Notifiee(std::string, Segment *);
        };
        
        void notifieeIs(std::string, Notifiee*);
        

    protected:
        Segment(); 
        Segment(const Segment &);
        Segment(const string & _name, Segment::Type _type, VirtualTimeActivityManager::Ptr _vtManager, Fleet::Ptr _fleet);
        
        VirtualTimeActivityManager::Ptr vtManager_;
        Fleet::Ptr fleet_;


    private:
        std::vector<shipmentElement> shipment_;
        Notifiee::Ptr notifiee_;
        NumPackages capacity_;
 
        Segment::Type type_;
        Fwk::Ptr<Location> source_;
        Miles length_;
        Segment::Ptr returnSegment_;
        DifficultyLevel difficulty_;
        ExpeditedSupport expeditedSupport_;
        
        NumShipments recievedShipments_;
        NumShipments refusedShipments_;
        NumPackages packagesInTransit_;
};
    
class BoatSegment: public Segment{
public:
    typedef Fwk::Ptr<BoatSegment const> PtrConst;
    typedef Fwk::Ptr<BoatSegment> Ptr;
    static BoatSegment::Ptr boatSegmentNew(const std::string &, VirtualTimeActivityManager::Ptr, Fleet::Ptr);
    
protected:
    BoatSegment();
    BoatSegment(const BoatSegment &);
    BoatSegment(const std::string &, VirtualTimeActivityManager::Ptr, Fleet::Ptr);
};

    
class PlaneSegment: public Segment{
    public:
        typedef Fwk::Ptr<PlaneSegment const> PtrConst;
        typedef Fwk::Ptr<PlaneSegment> Ptr;
    
    static PlaneSegment::Ptr planeSegmentNew(const std::string &, VirtualTimeActivityManager::Ptr, Fleet::Ptr);
    protected:
        PlaneSegment();
        PlaneSegment(const PlaneSegment &);
        PlaneSegment(const std::string &, VirtualTimeActivityManager::Ptr, Fleet::Ptr);
};


class TruckSegment: public Segment{
    public:
        typedef Fwk::Ptr<TruckSegment const> PtrConst;
        typedef Fwk::Ptr<TruckSegment> Ptr;

        static TruckSegment::Ptr truckSegmentNew(const std::string &, VirtualTimeActivityManager::Ptr, Fleet::Ptr);
    protected:
        TruckSegment();
        TruckSegment(const TruckSegment &);
        TruckSegment(const std::string &, VirtualTimeActivityManager::Ptr, Fleet::Ptr);
};



}
#endif
