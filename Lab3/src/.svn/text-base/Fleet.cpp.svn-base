/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#include "Fleet.h"
#include "FleetReactor.h"
#include "fwk/Exception.h"
#include <sstream>
#include <iostream>

using namespace Shipping; 
using namespace std;


/*
 * Constructor
 */

Fleet::Fleet(const string & _name, Fwk::Ptr<VirtualTimeActivityManager> _vtam) :
    Fwk::NamedInterface(_name),
    vtam_(_vtam){
	string rName = _name + string("Reactor");
	FleetReactor::Ptr fr = FleetReactor::fleetReactorNew(rName, this, vtam_);
	notifieeIs(rName, fr);     
}

/*
 * Mutators
 */

 /* Regular attributes */
void Fleet::speedIs(Type _type, MilesPerHour _speed){
    DCOUT( "Fleet:: " << name() << " ::speedIs:: " << _speed.value() << endl);
    if(typeAttr[_type].speed_ == _speed) return;
    typeAttr[_type].speed_ = _speed;
}

void Fleet::capacityIs(Type _type, NumPackages _capacity){
    DCOUT( "Fleet:: " << name() << " ::capacityIs:: " << _capacity.value() << endl);
    if(typeAttr[_type].capacity_ == _capacity) return; 
    typeAttr[_type].capacity_ = _capacity; 
}

void Fleet::costIs(Type _type, DollarsPerMile _cost) {
    DCOUT( "Fleet:: " << name() << " ::costIs:: " << _cost.value() << " Type: " << _type << endl);
    if(typeAttr[_type].cost_ == _cost) return;
    typeAttr[_type].cost_ = _cost; 
}

/* Other attributes */
void Fleet::otherSpeedIs(Type _type, MilesPerHour _speed){
    DCOUT( "Fleet:: " << name() << " ::otherSpeedIs:: " << _speed.value() << endl);
    if(otherTypeAttr[_type].speed_ == _speed) return;
    otherTypeAttr[_type].speed_ = _speed;
}

void Fleet::otherCapacityIs(Type _type, NumPackages _capacity){
    DCOUT( "Fleet:: " << name() << " ::otherCapacityIs:: " << _capacity.value() << endl);
    if(otherTypeAttr[_type].capacity_ == _capacity) return; 
    otherTypeAttr[_type].capacity_ = _capacity; 
}

void Fleet::otherCostIs(Type _type, DollarsPerMile _cost) {
    DCOUT( "Fleet:: " << name() << " ::otherCostIs:: " << _cost.value() << " Type: " << _type << endl);
    if(otherTypeAttr[_type].cost_ == _cost) return;
    otherTypeAttr[_type].cost_ = _cost; 
}

void Fleet::otherAttrHoursIs(HourOfDay _startHour, HourOfDay _stopHour){
    otherAttrStartHour_ = _startHour; 
    otherAttrStopHour_ = _stopHour; 
    /* If some fleet types donot have other attributes set then, setting it
	to the regular attribute values. */
    for (int i=0; i<3; ++i) {
	if(otherTypeAttr[i].speed_ == MilesPerHour::min())
	    otherTypeAttr[i].speed_ = typeAttr[i].speed_; 

	if(otherTypeAttr[i].capacity_ == NumPackages::min())
	    otherTypeAttr[i].capacity_ = typeAttr[i].capacity_; 

	if(otherTypeAttr[i].cost_ == DollarsPerMile::min())
	    otherTypeAttr[i].cost_ = typeAttr[i].cost_; 
    }
    notifiee_->onOtherAttrHours(); 
}

void Fleet::notifieeIs(const string& _name, Notifiee::Ptr _notifiee) {
    if(_notifiee == NULL){
	ostringstream s; 
        s << "Fleet::notifieeIs: Could not set notifiee. Provided instance is NULL.";
	cerr << s.str() << endl;
	throw Fwk::EntityNotFoundException(s.str()); 
    }
    notifiee_ = _notifiee;
}

/*
 * Instantiating Attribute
 */
Fleet::Ptr Fleet::FleetNew(const string & _name, Fwk::Ptr<VirtualTimeActivityManager> _vtam){
    Fleet::Ptr fleet = new Fleet(_name, _vtam);
    if (fleet == NULL) {
	ostringstream s; 
        s << "Fleet::fleetNew, could not create the new fleet name: " << _name;
	cerr << s.str() << endl;
	throw Fwk::MemoryException(s.str()); 
    }
    return fleet;
}
