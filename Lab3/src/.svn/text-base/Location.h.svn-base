/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#ifndef _LOCATION_H_
#define _LOCATION_H_

#include <iostream>
#include <string>
#include "Ptr.h"
#include "PtrInterface.h"
#include "Fleet.h"
#include "Segment.h"
#include <vector>
#include <list>
#include "VirtualTimeActivityManager.h"

namespace Shipping {
    class Network; 
    class Fleet; 
    class Segment; 

    class Location : public Fwk::NamedInterface{
    public:
        typedef Fwk::Ptr<Location const> PtrConst;
        typedef Fwk::Ptr<Location> Ptr;
    
        enum LocationType { Customer_, Port_, TruckTerminal_, PlaneTerminal_, BoatTerminal_ };

        //Accessors
        std::string stringType(LocationType t) const;
        Fwk::Ptr<Segment> segment(int _index) const;
        size_t numSegments() const {return segment_.size();}

        LocationType type() const {return type_; }
    
        
        //Instantiating Attributes
        void segmentIs(Fwk::Ptr<Segment> _segment);
        void segmentDel(Fwk::Ptr<Segment> _segment);
        
        //Iterators
        typedef std::vector<Fwk::Ptr<Segment> >::iterator SegmentIt;
        typedef std::vector<Fwk::Ptr<Segment> >::const_iterator SegmentItConst;
        
        SegmentItConst iterBegin() const{ return segment_.begin(); }
        SegmentItConst iterEnd() const { return segment_.end(); }
        
        SegmentIt iterBegin() { return segment_.begin(); }
        SegmentIt iterEnd(){ return segment_.end(); }

    protected:
        //Constructors
        Location();
        Location(const Location &);
        Location(const std::string & _name, LocationType _type, Fwk::Ptr<Network> _network);
    
        //Attributes
        std::vector<Fwk::Ptr<Segment> > segment_;
        LocationType type_;
        Fwk::Ptr<Network> network_; 
    };

    class CustomerLocation : public Location{
    public:
        typedef Fwk::Ptr<CustomerLocation const> PtrConst;
        typedef Fwk::Ptr<CustomerLocation> Ptr;
        enum Service {Pickup_, Delivery_};
    
        //Constructor
        static CustomerLocation::Ptr customerLocationNew(
	    const std::string & _name, 
	    Fwk::Ptr<VirtualTimeActivityManager> _vtam,
	    Fwk::Ptr<Network> n);

        //Accessors
        static Service serviceType() { return Pickup_; }
        static Service Delivery() { return Delivery_; }
        Service service() { return service_; }
        Hours averageLatency() const { return averageLatency_; }
        std::string destination() const { return destination_; }
        NumShipments shipmentsReceived() const { return shipmentsReceived_; }
        NumPackages shipmentSize() const { return shipmentSize_; }
        Hours totalLatency() const { return totalLatency_; }
        Dollars totalCost() const { return totalCost_; }
        TransferRate transferRate() const { return transferRate_; }
    
        //Mutator
        void serviceIs(Service _service);
        void averageLatencyIs(Hours _averageLatency);
        void destinationIs(const string &_destination);
        void recievedShipmentsIs(NumShipments);
        void recievedShipmentsInc();
        void shipmentSizeIs(NumPackages _shipmentSize);
        void totalLatencyIs(Hours _totalLatency);
        void totalCostIs(Dollars _totalCost);
        void transferRateIs(TransferRate _transferRate);



        class Notifiee : public Fwk::BaseNotifiee<CustomerLocation> {
        public:
            typedef Fwk::Ptr<CustomerLocation::Notifiee const> PtrConst;
            typedef Fwk::Ptr<CustomerLocation::Notifiee> Ptr;

            Notifiee(const std::string &_name, CustomerLocation* _notifier);
            virtual void onUpdate(){};
            virtual ~Notifiee() {}
        };
        
        void notifieeIs(const string &_name, Notifiee::Ptr _notifiee);
    protected:
        CustomerLocation(); 
        CustomerLocation(const CustomerLocation &); 
        CustomerLocation(const std::string & _name, 
	    Fwk::Ptr<VirtualTimeActivityManager> _vtam,
	    Fwk::Ptr<Network> n); 
	    
        //Attributes
        Service service_;

        Hours averageLatency_;      
        NumShipments shipmentsReceived_;
        Hours totalLatency_;
        Dollars totalCost_;
        
        string destination_;
        NumPackages shipmentSize_;
        TransferRate transferRate_;
        
        Notifiee::Ptr notifiee_;
        VirtualTimeActivityManager::Ptr vtManager_;
    };

    class Port : public Location{
    public:
        typedef Fwk::Ptr<Port const> PtrConst;
        typedef Fwk::Ptr<Port> Ptr;
    
        static Port::Ptr portNew(const std::string & _name, Fwk::Ptr<Network> n);
   
    protected:
        Port(); 
        Port(const Port &); 
        Port(const std::string & _name, Fwk::Ptr<Network> n);
    };


    class BoatTerminal : public Location{
    public:
        typedef Fwk::Ptr<BoatTerminal const> PtrConst;
        typedef Fwk::Ptr<BoatTerminal> Ptr;
    
        static BoatTerminal::Ptr boatTerminalNew(const std::string & _name, Fwk::Ptr<Network> n);
    
    protected:
        BoatTerminal();
        BoatTerminal(const BoatTerminal &); 
        BoatTerminal(const std::string & _name, Fwk::Ptr<Network> n); 
    };

    class PlaneTerminal : public Location{
    public:
        typedef Fwk::Ptr<PlaneTerminal const> PtrConst;
        typedef Fwk::Ptr<PlaneTerminal> Ptr;
    
        static PlaneTerminal::Ptr planeTerminalNew(const std::string & _name, Fwk::Ptr<Network> n);
    
    protected:
        PlaneTerminal();
        PlaneTerminal(const PlaneTerminal &); 
        PlaneTerminal(const std::string & _name, Fwk::Ptr<Network> n); 
    };
    
    class TruckTerminal : public Location{
    public:
        typedef Fwk::Ptr<TruckTerminal const> PtrConst;
        typedef Fwk::Ptr<TruckTerminal> Ptr;
        
        static TruckTerminal::Ptr truckTerminalNew(const std::string & _name, Fwk::Ptr<Network> n);
        
    protected:
        TruckTerminal();
        TruckTerminal(const TruckTerminal &);
        TruckTerminal(const std::string & _name, Fwk::Ptr<Network> n);
    };


}

#endif
