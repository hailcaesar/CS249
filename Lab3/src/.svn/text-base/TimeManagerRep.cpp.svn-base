/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#include "TimeManagerRep.h"
#include "Network.h"
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include "fwk/Exception.h"

using namespace Shipping;
using namespace std; 

TimeManagerRep::TimeManagerRep(const std::string& _name, Fwk::Ptr<Network> _network) : 
    Instance(_name), network_(_network) {}

string TimeManagerRep::attribute(const string& _attr){
    if(_attr == "scaling factor"){
	Fwk::ScalingFactor sf = network_->realTimeActivityManager()->scalingFactor(); 
	ostringstream s; 
	s.precision(2); 
	s << fixed; 
	s << sf.value(); 
	return s.str(); 
    } 
    else if (_attr == "now"){
	Fwk::Time time = network_->virtualTimeActivityManager()->now(); 
	ostringstream s; 
	s.precision(2); 
	s << fixed; 
	s << time.value(); 
	return s.str(); 
    }    
    
    cerr << "TimeManagerRep::attribute Invalid attribute = " << _attr << endl;
    return ""; 
    
}

void TimeManagerRep::attributeIs(const string& _attr, const string& _v) {
    ostringstream s; 
    s.precision(2);
    s << fixed; 

    if (_attr == "scaling factor") {
        double sf = atof(_v.c_str());
        if (sf < Fwk::ScalingFactor::min()){
	    s << "TimeManagerRep::attributeIs: Invalid Scaling factor value = " << sf;
	    cerr << s.str() << endl;
	    throw Fwk::RangeException(s.str()); 
	}
	network_->realTimeActivityManager()->scalingFactorIs(sf);
    } 
    else if (_attr == "now"){
	double t = atof(_v.c_str());
	if( t < Fwk::Time::min()){
	    s << "TimeManagerRep::attributeIs: Invalid Time value = " << t;
	    cerr << s.str() << endl;
	    throw Fwk::RangeException(s.str()); 
	}
	Fwk::Time oldVTime = network_->virtualTimeActivityManager()->now(); 
	if(t < oldVTime.value()){
	    s << "TimeManagerRep::attributeIs: Invalid Time value = " << t << " is before the current time = " << oldVTime.value();
	    cerr << s.str() << endl;
	    throw Fwk::RangeException(s.str()); 
	}
	Fwk::ScalingFactor sf =  network_->realTimeActivityManager()->scalingFactor();
	/* Launch the simulation. */
	network_->realTimeActivityManager()->nowIs(sf.value()*t); 
    }    
    else {
	s << "TimeManagerRep::attributeIs Invalid attribute = " << _attr;
	cerr << s.str() << endl;
	throw Fwk::UnknownAttrException(s.str()); 
    }
}
