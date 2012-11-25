/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#include "Segment.h"
#include "SegmentReactor.h"
#include <iostream>
#include <sstream>
#include "fwk/Exception.h"

using namespace Shipping; 
using namespace std;

/*
 * Constructor
 */
Segment::Segment(const string & _name, Segment::Type _type, VirtualTimeActivityManager::Ptr _vtManager, Fleet::Ptr _fleet) : NamedInterface(_name){
    type_ = _type;
    source_ = NULL;
    returnSegment_ = NULL;
    packagesInTransit_ = 0;
    capacity_ = DEFAULT_CAPACITY;
    expeditedSupport_ = Segment::SupportAbsent();
    DCOUT( "Segment:: " << _name << " ::Constructor:: " << endl);
    std::string reactorName = _name + "Reactor";
    notifiee_ = SegmentReactor::SegmentReactorNew(reactorName, this, _vtManager, _fleet);

}

std::string Segment::stringType(Segment::Type t) const {
    if(t == Segment::plane_)    return "Plane segment";
    if(t == Segment::truck_)    return "Truck segment";
    if(t == Segment::boat_)     return "Boat segment";
	
    return "";
} 

/*
 * Genetic Segment
 */

void Segment::difficultyIs(DifficultyLevel _difficulty){
    DCOUT( "Segment:: " << name() << " ::returnSegmentIs = " << _difficulty.value() << endl);
    if (difficulty_ == _difficulty) return;
    difficulty_ = _difficulty;
}

void Segment::expeditedSupportIs(ExpeditedSupport _expeditedSupport){
    DCOUT( "Segment:: " << name() << " ::expeditedSupportIs = " << _expeditedSupport << endl);
    if (expeditedSupport_ == _expeditedSupport) return;
    expeditedSupport_ = _expeditedSupport;
}

void Segment::lengthIs(Miles _length){
    DCOUT( "Segment:: " << name() << " ::lengthIs = " << _length.value() << endl);
    if (length_ == _length) return;
    length_ = _length;
}

void Segment::returnSegmentIs(Segment::Ptr _returnSegment){
    if(_returnSegment != NULL) DCOUT( "Segment:: " << name() << " ::returnSegmentIs = " << _returnSegment->name() << endl);
    if (returnSegment_ == _returnSegment) return;
    returnSegment_ = _returnSegment;
}

void Segment::sourceIs(Fwk::Ptr<Location> _source) {
    if(_source != NULL)	 DCOUT( "Segment:: " << name() << " ::sourceIs =" << _source->name() << endl);
    if (source_ == _source) return;
    source_ = _source;
}

void Segment::Notifiee::onShipmentEnq(Shipment::Ptr shipment, Location::Ptr loc) {};

void Segment::Notifiee::onShipmentDeq() {};
void Segment::Notifiee::onActivePackageInc(NumPackages n){};
void Segment::Notifiee::onActivePackageDec(NumPackages n){};

void Segment::refusedShipmentsInc() {
    refusedShipments_ = refusedShipments_.value() + 1;
}

Segment::Notifiee::~Notifiee() {};

Segment::Notifiee::Notifiee(std::string _name, Segment * _segment) :
Fwk::BaseNotifiee<Segment>(_name, _segment) {};

void Segment::notifieeIs(string _name, Notifiee* _notif) {
   
    if (_notif == NULL) {
	ostringstream s; 
	s << "Segment::notifieeIs: Passed notifiee pointer is null!";
	cerr << s.str() << endl;
	throw Fwk::EntityNotFoundException(s.str()); 
    }
    
    notifiee_ = _notif;
}

/*
 * Boat Segment
 */

BoatSegment::BoatSegment(const string & _name, VirtualTimeActivityManager::Ptr _vtManager, Fleet::Ptr _fleet) :
    Segment(_name, Segment::boat_, _vtManager,  _fleet){}

BoatSegment::Ptr BoatSegment::boatSegmentNew(const string & _name, VirtualTimeActivityManager::Ptr _vtManager, Fleet::Ptr _fleet){
    DCOUT( "BoatSegmentNew:: " << _name << endl);
    BoatSegment::Ptr boat = new BoatSegment(_name, _vtManager, _fleet);
    return boat;
}

/*
 * Plane Segment
 */

PlaneSegment::PlaneSegment(const string & _name, VirtualTimeActivityManager::Ptr _vtManager, Fleet::Ptr _fleet) :
    Segment(_name, Segment::plane_, _vtManager,  _fleet){}

PlaneSegment::Ptr PlaneSegment::planeSegmentNew(const string & _name, VirtualTimeActivityManager::Ptr _vtManager, Fleet::Ptr _fleet){
    DCOUT( "PlaneSegmentNew:: " << _name << endl);
    PlaneSegment::Ptr plane = new PlaneSegment(_name, _vtManager, _fleet);
    return plane;
}

/*
 * Truck Segment
 */

TruckSegment::TruckSegment(const string & _name, VirtualTimeActivityManager::Ptr _vtManager, Fleet::Ptr _fleet) :
    Segment(_name, Segment::truck_, _vtManager,  _fleet){}

TruckSegment::Ptr TruckSegment::truckSegmentNew(const string & _name, VirtualTimeActivityManager::Ptr _vtManager, Fleet::Ptr _fleet){
    DCOUT( "TruckSegmentNew:: " << _name << endl);
    TruckSegment::Ptr truck = new TruckSegment(_name, _vtManager, _fleet);
    return truck;
}


void Segment::packagesInTransitInc(NumPackages n) {
    packagesInTransit_ = packagesInTransit_.value() + n.value();
    notifiee_->onActivePackageInc(n);
}
void Segment::packagesInTransitDec(NumPackages n) {
    packagesInTransit_ = packagesInTransit_.value() - n.value();
    assert(packagesInTransit_ >= 0);        //ERROR - throw exception instead of assert?
    notifiee_->onActivePackageDec(n);
}


void Segment::shipmentDeq() {
    
    //destroy Shipment!!!!!!
    
}


void Segment::shipmentEnq() {
    
    
    
}
