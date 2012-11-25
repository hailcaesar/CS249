/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/
#include <iostream>
#include <sstream>
#include "StatsRep.h"
#include "fwk/Exception.h"

using namespace Shipping;
using namespace std; 

StatsRep::StatsRep(const string& _name, Ptr<Network> _network):
    Instance(_name){
    if(stats_ != NULL) return;
    stats_ = Stats::statsNew(_name,_network);
    if(stats_ == NULL) { 
	ostringstream s; 
	s << "Could not create a Stats object for the network";
	cerr << s.str() << endl;
	throw Fwk::MemoryException(s.str()); 
    }
}
    	    
string StatsRep::attribute(const string& attr){
    ostringstream val;
    val.precision(2);
    val << fixed; 
    if(attr == "Port")                      val << stats_->ports();
    else if(attr == "Customer")             val << stats_->customerLocations();
    else if(attr == "Truck terminal")       val << stats_->truckTerminals();
    else if(attr == "Plane terminal")       val << stats_->planeTerminals();
    else if(attr == "Boat terminal")        val << stats_->boatTerminals();
    else if(attr == "Truck segment")        val << stats_->truckSegments();
    else if(attr == "Plane segment")        val << stats_->planeSegments();
    else if(attr == "Boat segment")         val << stats_->boatSegments();
    else if(attr == "expedite percentage")	val << stats_->expeditePercent();
    else {
	//Accessor => don't throw exception
        DCOUT( "Stats called with invalid attribute name = " << attr << endl);
        val << "";
    }
    return val.str(); 
}


void StatsRep::attributeIs(const string& _name, const string& _v){
    /* Nothing to do here because the attributes will get 
       modified as a side effect of adding or removing entities
       from the Network (Engine Layer). */
}
