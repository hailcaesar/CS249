/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#include <iostream>
#include <sstream>
#include "FleetRep.h"
#include "Fleet.h"
#include <string>
#include <stdlib.h>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <vector>
#include "VirtualTimeActivityManager.h"
#include "fwk/Exception.h"

using namespace Shipping; 
using namespace std; 
using namespace boost;

FleetRep::FleetRep(const string& _name, Ptr<Network> _network): 
    Instance(_name), network_(_network){
    Ptr<Fleet> f = network_->fleet();
    VirtualTimeActivityManager::Ptr vtam = network_->virtualTimeActivityManager(); 
    if(f != NULL)
	return;
    Ptr<Fleet> fleet = Fleet::FleetNew(_name, vtam); 
    if(fleet == NULL){
	ostringstream s; 
	s << "Could not create a Fleet object!";
	cerr << s.str() << endl; 
	throw Fwk::MemoryException(s.str()); 	
    }
    network_->fleetIs(fleet); 
}

string FleetRep::attribute(const string& _attr){
    DCOUT( "FleetRep::attribute: called with = " << _attr << endl);
    char_separator<char> sep(", ");
    tokenizer< char_separator<char> > tokens(_attr, sep);
    vector<string> fields; 
    BOOST_FOREACH (const string& t, tokens) {
	fields.push_back(t);
    }
    
    Fleet::Ptr fleet = network_->fleet(); 
    ostringstream s; 
    s.precision(2); 
    s << fixed; 

    if(fields.size() == 1){
	cerr << "Invalid attribute string for Fleet." << endl;
	return "";
    }

    string typeString = fields[0]; 
    Fleet::Type type;
    
    string fleetAttr = fields[1];
    MilesPerHour speed; 
    NumPackages capacity;
    DollarsPerMile cost;
    HourOfDay hour; 

    if(typeString == "Truck"){
	type = Fleet::truck();
	DCOUT( "Truck type = " << type << endl);
    } 
    else if (typeString == "Boat"){
	type = Fleet::boat();
	DCOUT( "Boat type = " << type << endl);
    }
    else if (typeString == "Plane") {
	type = Fleet::plane();
	DCOUT( "Plane type = " << type << endl);
    }
    else {
	cerr << "Invalid Fleet type : " << _attr << endl;  
	return ""; 
    }
    
    if(fleetAttr == "speed"){    
	speed = fleet->speed(type);     
	s << speed.value(); 
    } 
    else if(fleetAttr == "capacity"){
	capacity = fleet->capacity(type);     
	s << capacity.value();
    }
    else if (fleetAttr == "cost"){
	cost = fleet->cost(type);
	s << cost.value();
    }
    else if(fleetAttr == "otherSpeed"){    
	speed = fleet->otherSpeed(type);     
	s << speed.value(); 
    } 
    else if(fleetAttr == "otherCapacity"){
	capacity = fleet->otherCapacity(type);     
	s << capacity.value();
    }
    else if (fleetAttr == "otherCost"){
	cost = fleet->otherCost(type);
	s << cost.value();
    }
    else if (fleetAttr == "otherAttributeStartHour"){
	hour = fleet->otherAttrStartHour();
	s << hour.value();
    }
    else if (fleetAttr == "otherAttributeStopHour"){
	hour = fleet->otherAttrStopHour();
	s << cost.value();
    }
    else {
	cerr << "Invalid Fleet attribute name : " << _attr << endl;  
	s << ""; 
    }
    return s.str();
}

void FleetRep::attributeIs(const string& _attr, const string& _v){
    ostringstream s; 
    s.precision(2);
    s << fixed; 

    if(_attr == "Other Attribute Hours"){
	char_separator<char> sep(":");
    	tokenizer< char_separator<char> > tokens(_v, sep);
    	vector<string> fields; 
    	BOOST_FOREACH (const string& t, tokens) {
    	    fields.push_back(t); 
    	}
	HourOfDay startHour, stopHour; 
	int t_start = atoi(fields[0].c_str());
    	if(t_start < (int)HourOfDay::min() || t_start > (int)HourOfDay::max()){
    	    s << "FleetRep::attributeIs: Invalid  value for other attribute START hour = " << t_start;
	    cerr << s.str() << endl;
    	    throw Fwk::RangeException(s.str()); 
    	} 
	int t_stop = atoi(fields[1].c_str());
    	if(t_stop < (int)HourOfDay::min() || t_stop > (int)HourOfDay::max()){
	    s << "FleetRep::attributeIs: Invalid  value for other attribute STOP hour = " << t_stop;
	    cerr << s.str() << endl; 
    	    throw Fwk::RangeException(s.str()); 
    	} 
	startHour = t_start; 
	stopHour = t_stop;
	network_->fleet()->otherAttrHoursIs(startHour,stopHour); 
    
    } else { 
	char_separator<char> sep(", ");
    	tokenizer< char_separator<char> > tokens(_attr, sep);
    	vector<string> fields; 
    	BOOST_FOREACH (const string& t, tokens) {
    	    fields.push_back(t); 
    	}
    	
    	Fleet::Ptr fleet = network_->fleet(); 
    	string typeString = fields[0]; 
    	Fleet::Type type;
    	
    	string fleetAttr = fields[1];
    	MilesPerHour speed; 
    	NumPackages capacity;
    	DollarsPerMile cost; 

    	if(typeString == "Truck"){
    	    type = Fleet::truck();
    	} 
    	else if (typeString == "Boat"){
    	    type = Fleet::boat();
    	}
    	else if (typeString == "Plane") {
    	    type = Fleet::plane();
    	}
    	else {
    	    s << "FleetRep: attributeIs: Invalid Fleet type : " << _attr;
	    cerr << s.str() << endl;
	    throw Fwk::UnknownAttrException(s.str());      
    	}
    	
    	if(fleetAttr == "speed"){    
    	    double t = 1.00 * atof(_v.c_str());
    	    if(t < MilesPerHour::min()){
		s << "FleetRep::attributeIs: Invalid Fleet speed value = " << t;
		cerr << s.str() << endl;
    	        throw Fwk::RangeException(s.str()); 
    	    } 
    	    else {
    	        speed = t; 
    	        fleet->speedIs(type, speed);     
    	    }
    	} 
    	else if(fleetAttr == "capacity"){
    	    int t = atoi(_v.c_str());	
    	    if(t < (int)NumPackages::min()){
		s << "FleetRep::attributeIs: Invalid Fleet capacity value = " << t;
		cerr << s.str() << endl;
    	        throw Fwk::RangeException(s.str()); 
    	    }
    	    else {
    	        capacity = t; 
    	        fleet->capacityIs(type,capacity);     
    	    }
    	}
    	else if (fleetAttr == "cost"){
    	    double t = 1.00 * atof(_v.c_str());
    	    if(t < Dollars::min()){
		s << "FleetRep::attributeIs: Invalid Fleet cost value = " << t;
		cerr << s.str() << endl;
    	        throw Fwk::RangeException(s.str()); 
    	    }
    	    else {
    	        cost = t; 
    	        fleet->costIs(type,cost);     
    	    }
    	}
    	else if(fleetAttr == "otherSpeed"){    
    	    double t = 1.00 * atof(_v.c_str());
    	    if(t < MilesPerHour::min()){
		s << "FleetRep::attributeIs: Invalid Fleet other speed value = " << t;
		cerr << s.str() << endl;
    	        throw Fwk::RangeException(s.str()); 
    	    } 
    	    else {
    	        speed = t; 
    	        fleet->otherSpeedIs(type, speed);     
    	    }
    	} 
    	else if(fleetAttr == "otherCapacity"){
    	    int t = atoi(_v.c_str());	
    	    if(t < (int)NumPackages::min()){
		s << "FleetRep::attributeIs: Invalid Fleet other capacity value = " << t;
		cerr << s.str() << endl;
    	        throw Fwk::RangeException(s.str()); 
    	    }
    	    else {
    	        capacity = t; 
    	        fleet->otherCapacityIs(type,capacity);     
    	    }
    	}
    	else if (fleetAttr == "otherCost"){
    	    double t = 1.00 * atof(_v.c_str());
    	    if(t < Dollars::min()){
		s << "FleetRep::attributeIs: Invalid Fleet other cost value = " << t;
		cerr << s.str() << endl;
    	        throw Fwk::RangeException(s.str()); 
    	    }
    	    else {
    	        cost = t; 
    	        fleet->otherCostIs(type,cost);     
    	    }
    	}
    	else {
    	    s << "FleetRep: attributeIs: Invalid Fleet attribute name : " << _attr;  
	    cerr << s.str() << endl;
	    throw Fwk::UnknownAttrException(s.str());      
    	}
    }
}

