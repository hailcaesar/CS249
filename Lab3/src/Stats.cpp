/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/
#include "Stats.h"

using namespace Shipping;
using namespace std; 

Stats::Stats(const string & _name, Fwk::Ptr<Network> _network) : 
    Notifiee(_name, _network), 
    truckSegments_(0),
    boatSegments_(0),
    planeSegments_(0),
    expeditedSegments_(0),
    totalSegments_(0), 
    ports_(0), 
    customerLocations_(0), 
    truckTerminals_(0),
    boatTerminals_(0),
    planeTerminals_(0) {}

Stats::Ptr Stats::statsNew(const string & _name, Fwk::Ptr<Network> _network){
    Stats::Ptr stats = new Stats(_name,_network);
    return stats; 
}

double Stats::expeditePercent () const { 
    if (totalSegments_ == 0 ) return(0);
    else return(100.0 * expeditedSegments_/totalSegments_);
}

void Stats::onLocationNew(Location::PtrConst loc){
    if(loc == NULL) return;
    
    string type = loc->stringType(loc->type());

    if(type == "Customer")                  customerLocations_++;
    else if (type == "Port")                ports_++;
    else if (type == "Truck terminal")      truckTerminals_++;
    else if (type == "Boat terminal")       boatTerminals_++;
    else if (type == "Plane terminal")      planeTerminals_++;
}

void Stats::onSegmentNew ( Segment::PtrConst seg){
    if (seg == NULL) return;

    string type = seg->stringType(seg->type());
    DCOUT("Stats::onSegmentNew: called for segment " << seg->name() << ". Type = enum value = " 
	<<  seg->type() << ", string val = " << type << endl); 
    if(type == "Truck segment")             truckSegments_++;
    else if (type == "Boat segment")        boatSegments_++;
    else if (type == "Plane segment")       planeSegments_++;
    
    Segment::ExpeditedSupport es = seg->expeditedSupport();
    if(es == Segment::SupportPresent())     expeditedSegments_++;

    totalSegments_++;
    DCOUT( "Stats:: onSegmentNew, total Segments = " << totalSegments_ << endl); 
}

void Stats::onLocationDel( Location::PtrConst loc) {
    if(loc == NULL) return;

    string type = loc->stringType(loc->type());
    if(type == "Customer")
	customerLocations_--;
    else if (type == "Port")                ports_--;
    else if (type == "Truck terminal")      truckTerminals_--;
    else if (type == "Boat terminal")       boatTerminals_--;
    else if (type == "Plane terminal")      planeTerminals_--;
}

void Stats::onSegmentDel ( Segment::PtrConst seg){
    if(seg == NULL)
	return;
    string type = seg->stringType(seg->type());
    if(type == "Truck segment")             truckSegments_--;
    else if (type == "Boat segment")        boatSegments_--;
    else if (type == "Plane segment")       planeSegments_--;
    
    Segment::ExpeditedSupport es = seg->expeditedSupport();
    if(es == Segment::SupportPresent())     expeditedSegments_--;

    totalSegments_--; 
}


void Stats::onSegmentExpeditedSupportRemoval( Segment::PtrConst seg){
    Segment::ExpeditedSupport es = seg->expeditedSupport();
    if(es == Segment::SupportPresent())     expeditedSegments_--;
}

void Stats::onSegmentExpeditedSupportAddition( Segment::PtrConst seg){
    Segment::ExpeditedSupport es = seg->expeditedSupport();
    if(es == Segment::SupportPresent())     expeditedSegments_++;
    
    DCOUT( "Stats:: onSegmentNew, expedited Segments = " << expeditedSegments_ << endl); 
}
