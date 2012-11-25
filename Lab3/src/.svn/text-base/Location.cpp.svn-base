/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/
#include "Location.h"
#include "Network.h"
#include "CustomerReactor.h"
#include <iostream>
#include <sstream>
#include "fwk/Exception.h"

using namespace Shipping;
using namespace std; 

/*----------------------------------------- Location ------------------------------------------*/

Location::Location(const string & _name, Location::LocationType _type, Fwk::Ptr<Network> _network) : 
    NamedInterface(_name), type_(_type),
    network_(_network){
    DCOUT( "Location:: " << _name << " ::Constructor:: Type: " << _type << endl);
}

Fwk::Ptr<Segment> Location::segment(int _index) const{
    DCOUT( "Location::segment(index). index = " << _index <<". Segment size = " << segment_.size() << endl); 
    if(_index >= (int)segment_.size()) return ((Fwk::Ptr<Segment>)NULL) ;
    return segment_.at(_index);
}

std::string Location::stringType(Location::LocationType t) const{
    if(t == Location::Customer_)        return "Customer";
    if(t == Location::Port_)            return "Port";
    if(t == Location::TruckTerminal_)   return "Truck terminal";
    if(t == Location::PlaneTerminal_)   return "Plane terminal";
    if(t == Location::BoatTerminal_)	return "Boat terminal";
    return ""; 
}

void Location::segmentIs(Fwk::Ptr<Segment> _segment){
    segment_.push_back(_segment);
    DCOUT( "Location:: " << name() << " ::segmentNew:: " << _segment->name() << endl);
    DCOUT( "Location:: " << name() << " ::numSegments:: " << segment_.size() << endl);
}

void Location::segmentDel(Segment::Ptr _segment) {
    DCOUT( "Location:: " << name() << " ::segmentDel:: " << _segment->name() << endl);
    DCOUT( "Before Deleting: segment vector size = " << segment_.size() << endl); 
    int found = 0;
    int index; 
    for (unsigned int i = 0; i < segment_.size(); i++) {
        if (segment_[i]->name() == _segment->name()){
	    index = i; 
            found = 1;
        }
    }
    if (!found) { 
        DCOUT( "Error: Tried to delete a non-existing segment.  Location: " << name() << " Segment: " << _segment->name() << endl);
    } else {
        segment_.erase(segment_.begin() + index);
    }
    DCOUT( "After Deleting: segment vector size = " << segment_.size() << endl); 
    return;
}


/*-------------------------------------- Customer --------------------------------------------*/

CustomerLocation::CustomerLocation(const string & _name, Fwk::Ptr<VirtualTimeActivityManager> _vtam, Fwk::Ptr<Network> _network) : 
    Location(_name, Location::Customer_, _network), 
    destination_(string("")) {
    DCOUT( "CustomerLocation::constructor. also declaring a CustomerReactor" << endl);
    string crName = _name + string("Reactor");
    Fwk::Ptr<CustomerReactor> cr = CustomerReactor::CustomerReactorNew(
	crName, this, _vtam, network_); 
    if (cr == NULL) {
	ostringstream s; 
	s << "CustomerLocation::constructor: Could not create a new CustomerReactor";
	cerr << s.str() << endl;	
	throw Fwk::MemoryException(s.str()); 
    }
    notifieeIs(crName, cr); 
}

CustomerLocation::Ptr CustomerLocation::customerLocationNew(const string & _name, 
    Fwk::Ptr<VirtualTimeActivityManager> _vtam, 
    Fwk::Ptr<Network> _network){
    DCOUT( "CustomerLocation:: " << _name << " ::Constructor::" << endl);
    CustomerLocation::Ptr customer = new CustomerLocation(_name, _vtam, _network);
    return customer;
}


void CustomerLocation::averageLatencyIs(Hours _averageLatency) {
    averageLatency_ = _averageLatency;
}


void CustomerLocation::destinationIs(const string &_destination) {
    if(destination_ == _destination) return;
    destination_ = _destination;
    if(notifiee_) notifiee_->onUpdate();
}

CustomerLocation::Notifiee::Notifiee(const string &_name, CustomerLocation* _notifier)
: Fwk::BaseNotifiee<CustomerLocation>(_name, _notifier) {}

void CustomerLocation::notifieeIs(const string &_name, Notifiee::Ptr _notifiee) {
    notifiee_ = _notifiee;
}


void CustomerLocation::recievedShipmentsInc() {
    shipmentsReceived_ = shipmentsReceived_.value() + 1;
}


void CustomerLocation::recievedShipmentsIs(NumShipments _shipmentsReceived) {
    shipmentsReceived_ = _shipmentsReceived;
}

void CustomerLocation::shipmentSizeIs(NumPackages _shipmentSize) {
    if (shipmentSize_ == _shipmentSize) return;
    shipmentSize_ = _shipmentSize;
    if (notifiee_) notifiee_->onUpdate();
}


void CustomerLocation::totalLatencyIs(Hours _totalLatency) {
    totalLatency_ = _totalLatency;
}

void CustomerLocation::totalCostIs(Dollars _totalCost) {
    totalCost_ = _totalCost;
}

void CustomerLocation::transferRateIs(TransferRate _transferRate) {
    if (transferRate_ == _transferRate) return;
    transferRate_ = _transferRate;
    if (notifiee_) notifiee_->onUpdate();
}


/*---------------------------------------- Port ---------------------------------------------*/

Port::Port(const string & _name, Fwk::Ptr<Network> _network) : Location(_name, Location::Port_, _network) {}

Port::Ptr Port::portNew(const string & _name, Fwk::Ptr<Network> _network){
    Port::Ptr port = new Port(_name, _network);
    return port;
}
    
    
/*---------------------------------------------------------------------------------------------
--------------------------------------- Terminals ---------------------------------------------
---------------------------------------------------------------------------------------------*/ 

/*--------------------------------------- Truck ---------------------------------------------*/
    
TruckTerminal::TruckTerminal(const string & _name, Fwk::Ptr<Network> _network) : Location(_name, Location::TruckTerminal_, _network){}

TruckTerminal::Ptr TruckTerminal::truckTerminalNew(const string & _name, Fwk::Ptr<Network> _network){
    DCOUT( "TruckTerminal:: " << _name << " ::Constructor::" << endl);
    TruckTerminal::Ptr truckTerminal = new TruckTerminal(_name, _network);
    return truckTerminal;
}
    
    
/*---------------------------------------- Boat ---------------------------------------------*/


BoatTerminal::BoatTerminal(const string & _name, Fwk::Ptr<Network> _network) : Location(_name, Location::BoatTerminal_, _network){}

BoatTerminal::Ptr BoatTerminal::boatTerminalNew(const string & _name, Fwk::Ptr<Network> _network){
    DCOUT( "BoatTerminal:: " << _name << " ::Constructor::" << endl);
    BoatTerminal::Ptr boatTerminal = new BoatTerminal(_name, _network);
    return boatTerminal;
}

/*---------------------------------------- Plane --------------------------------------------*/

PlaneTerminal::PlaneTerminal(const string & _name, Fwk::Ptr<Network> _network) : Location(_name, Location::PlaneTerminal_, _network){}

PlaneTerminal::Ptr PlaneTerminal::planeTerminalNew(const string & _name, Fwk::Ptr<Network> _network){
    DCOUT( "PlaneTerminal:: " << _name << " ::Constructor::" << endl);
    PlaneTerminal::Ptr planeTerminal = new PlaneTerminal(_name, _network);
    return planeTerminal;
}

