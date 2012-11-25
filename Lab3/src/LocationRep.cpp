/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "LocationRep.h"
#include <string>
#include "fwk/Exception.h"

using namespace Shipping;
using namespace std; 

string LocationRep::attribute(const string& _attr) {
    Location::PtrConst loc = network_->location(name());
    if (loc == NULL) {
	cerr << "LocationRep::attribute Invalid location name = " << this->name() << endl;
	/* Accessor, so no throwing exceptions */
	return ""; 
    }
    size_t pos = _attr.find(string("segment")); 
    if (pos == 0) {
	int i = segmentNumber(_attr);
    	if(i == 0){
    	    cerr << "LocationRep::attribute: Invalid Segment number attribute!"<< endl;
    	    return "";
    	}
    	Location::PtrConst loc = network_->location(this->name());
    	Segment::Ptr seg = loc->segment(i-1); 
    	if(seg == NULL){
    	    cerr << "LocationRep::attribute: Invalid Segment number attribute!"<< endl;
    	    return "";
    	}
    	return seg->name(); 
    } else {
	if(loc->type() != Location::Customer_){
    	    cerr << "LocationRep::attribute: non-Customer locations have only segment number attributes" << endl;
    	    return ""; 
    	}
	Fwk::Ptr<CustomerLocation const> customer = static_cast<const CustomerLocation *>(loc.ptr()); 
        ostringstream s;
	s.precision(2);
	s << fixed; 
        if (_attr == "Transfer rate" ) {
            s << customer->transferRate().value();
            return s.str();
        } else if (_attr == "Shipment size") {
            s << customer->shipmentSize().value();
            return s.str();
        } else if (_attr == "Destination" ) {
            return customer->destination();
        } else if (_attr == "Shipments recieved") {
            s << customer->shipmentsReceived().value();
            return s.str();
        } else if (_attr == "Average latency") {
            s << customer->averageLatency().value();
            return s.str();
        } else if (_attr == "Total cost") {
            s << customer->totalCost().value();
            return s.str();
        } else {
            cerr << "LocationRep::attribute: Invalid attribute name = " << _attr << endl;
            return "";
        }
    }
}

void LocationRep::attributeIs(const string& _attr, const string& _v) {
    ostringstream s; 
    s.precision(2); 
    s << fixed; 

    Fwk::Ptr<Location> loc = network_->location(this->name());
    if(loc == NULL) {
	s << "LocationRep::attributeIs Invalid location name = " << this->name();
	cerr << s.str() << endl;
	throw Fwk::MemoryException(s.str()); 
    }

    if(loc->type() != Location::Customer_){
	s << "LocationRep::attributeIs: Cannot set attributes of non-Customer locations";
	cerr << s.str() << endl;
	throw Fwk::UnknownAttrException(s.str()); 
    }
    Fwk::Ptr<CustomerLocation> customer = static_cast<CustomerLocation *>(loc.ptr()); 
    if (_attr == "Transfer rate") {
	double tr = atof(_v.c_str());
	if (tr < TransferRate::min()){
	    s << "LocationRep::attributeIs: Invalid value for Transfer rate = " << tr ; 
	    cerr << s.str() << endl;
	    throw Fwk::RangeException(s.str()); 
	}
        customer->transferRateIs(tr);
    } 
    else if (_attr == "Shipment size") {
        int ss = atoi(_v.c_str());
	if (ss < (int)NumPackages::min()){
	    s << "LocationRep::attributeIs: Invalid value for Shipment size = " << ss ; 
	    cerr << s.str() << endl;
	    throw Fwk::RangeException(s.str()); 
	}
        customer->shipmentSizeIs(ss);
    } 
    else if (_attr == "Destination") {
        Fwk::Ptr<Location> dst = network_->location(_v); 
	if(dst == NULL) {
	    s << "LocationRep::attributeIs: Invalid destination name = " <<_v 
		<<". Location doesn't exist!";
	    cerr << s.str() << endl;
	    throw Fwk::EntityNotFoundException(s.str()); 
	}
	customer->destinationIs(_v);
    } 
    else {
	s << "LocationRep::attributeIs: Invalid attribute name = " << _attr << endl; 
	cerr << s.str() << endl;
	throw Fwk::UnknownAttrException(s.str()); 
    }
}

const string LocationRep::segmentStr = "segment";
const int LocationRep::segmentStrlen = LocationRep::segmentStr.length();

int LocationRep::segmentNumber(const string& name) {
    if (name.substr(0, segmentStrlen) == segmentStr) {
        const char* t = name.c_str() + segmentStrlen;
        return atoi(t);
    }
    return 0;
}

CustomerRep::CustomerRep(const string & _name, Ptr<Network> _network):LocationRep(_name, _network){
    Ptr<CustomerLocation> customer = 
	CustomerLocation::customerLocationNew(_name, 
	    network_->virtualTimeActivityManager(),
	    network_);
    if(customer == NULL){
	ostringstream s; 
	s << "Could not create a customer object for the network!";
	cerr << s.str() << endl; 
        throw Fwk::MemoryException(s.str()); 
    }
    network_->locationIs(_name, customer);
}

PortRep::PortRep(const string& _name, Ptr<Network> _network):LocationRep(_name, _network){
    Ptr<Port> port = Port::portNew(_name, network_);
    if(port == NULL){
	ostringstream s; 
	s << "Could not create a Port object for the network!";
	cerr << s.str() << endl; 
        throw Fwk::MemoryException(s.str());
    }
    network_->locationIs(_name, port);
}

TruckTerminalRep::TruckTerminalRep(const string& _name, Ptr<Network> _network) : LocationRep(_name, _network){
    Ptr<TruckTerminal> truckTerminal = TruckTerminal::truckTerminalNew(_name, network_);
    if(truckTerminal == NULL){
	ostringstream s; 
	s << "Could not create a Truck Terminal object for the network!";
	cerr << s.str() << endl; 
        throw Fwk::MemoryException(s.str());
    }
    network_->locationIs(_name, truckTerminal);
}

BoatTerminalRep::BoatTerminalRep(const string& _name, Ptr<Network> _network):LocationRep(_name,_network){
    Ptr<BoatTerminal> boatTerminal = BoatTerminal::boatTerminalNew(_name, network_);
    if(boatTerminal == NULL){
	ostringstream s; 
	s << "Could not create a Boat Terminal object for the network!";
	cerr << s.str() << endl; 
        throw Fwk::MemoryException(s.str());
    }
    network_->locationIs(_name, boatTerminal);
}

PlaneTerminalRep::PlaneTerminalRep(const string& _name, Ptr<Network> _network):LocationRep(_name,_network){
    Ptr<PlaneTerminal> planeTerminal = PlaneTerminal::planeTerminalNew(_name, network_);
    if(planeTerminal == NULL){
	ostringstream s; 
	s << "Could not create a Plane Terminal object for the network!";
	cerr << s.str() << endl; 
        throw Fwk::MemoryException(s.str());
    }
    network_->locationIs(_name, planeTerminal);
}

CustomerRep::~CustomerRep(){
    DCOUT( "In the destructor of CustomerRep. Deleting instance and entity " << this->name() <<" from the manager and network resp." << endl);
    network_->locationDel(this->name());    
}

PortRep::~PortRep(){
    DCOUT( "In the destructor of PortRep. Deleting instance and entity " << this->name() <<" from the manager and network resp." << endl);
    network_->locationDel(this->name());    
}

TruckTerminalRep::~TruckTerminalRep(){
    DCOUT( "In the destructor of TruckTerminalRep. Deleting instance and entity " << this->name() <<" from the manager and network resp." << endl);
    network_->locationDel(this->name());    
}

BoatTerminalRep::~BoatTerminalRep(){
    DCOUT( "In the destructor of BoatTerminalRep. Deleting instance and entity " << this->name() <<" from the manager and network resp." << endl);
    network_->locationDel(this->name());    
}

PlaneTerminalRep::~PlaneTerminalRep(){
    DCOUT( "In the destructor of PlaneTerminalRep. Deleting instance and entity " << this->name() <<" from the manager and network resp." << endl);
    network_->locationDel(this->name());    
}
