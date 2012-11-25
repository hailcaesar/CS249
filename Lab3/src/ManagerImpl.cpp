/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/
#include "Instance.h"
#include <map>
#include "ManagerImpl.h"
#include "LocationRep.h"
#include "SegmentRep.h"
#include "StatsRep.h"
#include "ConnRep.h"
#include "FleetRep.h"
#include "TimeManagerRep.h"

using namespace Shipping; 
using namespace std;

ManagerImpl::ManagerImpl(const std::string & _name){
    name_ = _name; 
    /* Creating the network which automatically creates
       the Real and Virtual Time Activity Managers */
    network_ = Network::networkNew(_name);
    
    /*Creating a Stats Rep Instance and consequently a Stats entity. */
    Ptr<StatsRep> s = new StatsRep("defaultStats", network_);
    instance_["defaultStats"] = s;

    /*Creating a Conn Rep Instance and consequently a Conn entity. */
    Ptr<ConnRep> c = new ConnRep("defaultConn", network_);
    instance_["defaultConn"] = c;

    /*Creating a Fleet Rep Instance and consequently a Fleet entity. */
    Ptr<FleetRep> f = new FleetRep("defaultFleet", this->network_);
    instance_["defaultFleet"] = f;

    /*Creating a TimeManager Rep Instance. */
    Ptr<TimeManagerRep> t = new TimeManagerRep("defaultTimeManager", this->network_);   
    instance_["defaultTimeManager"] = t; 

}

Ptr<Instance> ManagerImpl::instanceNew(const string& _name, const string& _type) {
    if(_type == "TimeManager"){
        if(_name != "defaultTimeManager") instance_[_name] = instance_["defaultTimeManager"];
        return instance_[_name];
    } 
    else if(_type == "Stats"){
        if(_name != "defaultStats") instance_[_name] = instance_["defaultStats"];
        return instance_[_name];
    } 
    else if(_type == "Conn"){
        if(_name != "defaultConn") instance_[_name] = instance_["defaultConn"];
        return instance_[_name];
    }
    else if(_type == "Fleet"){
        if(_name != "defaultFleet") instance_[_name] = instance_["defaultFleet"];
        return instance_[_name];
    }
    else if(_type == "Customer"){
	if (instance_.find(_name) != instance_.end())
	    return instance_[name_]; 
	
        Ptr<CustomerRep> t = new CustomerRep(_name, this->network_);
        instance_[_name] = t;
        return t;
    }
    else if(_type == "Port"){
	if (instance_.find(_name) != instance_.end())
	    return instance_[name_]; 
	
        Ptr<PortRep> t = new PortRep(_name, this->network_);
        instance_[_name] = t;
        return t;
    }
    else if (_type == "Truck terminal") {
	if (instance_.find(_name) != instance_.end())
	    return instance_[name_]; 
	
        Ptr<TruckTerminalRep> t = new TruckTerminalRep(_name, this->network_);
        instance_[_name] = t;
        return t;
    }
    else if(_type == "Boat terminal"){
	if (instance_.find(_name) != instance_.end())
	    return instance_[name_]; 
	
        Ptr<BoatTerminalRep> t = new BoatTerminalRep(_name, this->network_);
        instance_[_name] = t;
        return t;
    }
    else if(_type == "Plane terminal"){
	if (instance_.find(_name) != instance_.end())
	    return instance_[name_]; 
	
        Ptr<PlaneTerminalRep> t = new PlaneTerminalRep(_name, this->network_);
        instance_[_name] = t;
        return t;
    }
    else if (_type == "Truck segment") {
	if (instance_.find(_name) != instance_.end())
	    return instance_[name_]; 
	
        Ptr<TruckSegmentRep> t = new TruckSegmentRep(_name, this->network_);
        instance_[_name] = t;
        return t;
    }
    else if(_type == "Boat segment"){
	if (instance_.find(_name) != instance_.end())
	    return instance_[name_]; 
	
        Ptr<BoatSegmentRep> t = new BoatSegmentRep(_name, this->network_);
        instance_[_name] = t;
        return t;
    }
    else if(_type == "Plane segment"){
	if (instance_.find(_name) != instance_.end())
	    return instance_[name_]; 
	
        Ptr<PlaneSegmentRep> t = new PlaneSegmentRep(_name, this->network_);
        instance_[_name] = t;
        return t;
    }
    return NULL;
}

Ptr<Instance> ManagerImpl::instance(const string& _name) {
    std::map<std::string,Ptr<Instance> >::const_iterator t = instance_.find(_name);
    return t == instance_.end() ? NULL : (*t).second;
}

void ManagerImpl::instanceDel(const string& _name) {
    std::map<std::string, Ptr<Instance> >:: iterator it; 
    it=instance_.find(_name);
    if(it != instance_.end()){
        (it->second)->~Instance(); 
        instance_.erase(it);  
    }
}

