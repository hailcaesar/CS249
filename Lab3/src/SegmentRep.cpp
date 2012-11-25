/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "SegmentRep.h"
#include "fwk/Exception.h"

using namespace Shipping; 
using namespace std; 

string SegmentRep::attribute(const string &_attr){
    Ptr<Segment> seg = network_->segment(this->name());
    ostringstream s;  
    s.precision(2);
    s << fixed; 
    if ( _attr == "source") {
	Ptr<Location> loc = seg->source();
        if(loc == NULL){
	    // Don't throw exception: accessor. 
            cerr << "SegmentRep::attribute: The segment " << this->name() << " does not have a source defined!" << endl;
            s << "";
        } else {
            s << loc->name(); 
        }
    }
    else if ( _attr == "return segment"){
        Ptr<Segment> retSeg = seg->returnSegment();
        if(retSeg == NULL){
            cerr << "SegmentRep::attribute: The segment " << this->name() << " does not have a return segment defined!" << endl;
            s << "";
        } else s << retSeg->name();
    }
    else if (_attr == "length")             s << seg->length().value();
    else if (_attr == "difficulty")         s << seg->difficulty().value();
    else if (_attr == "expedite support"){
        Segment::ExpeditedSupport es = seg->expeditedSupport();
        if( es == Segment::SupportPresent())    s << "yes";
        else                                    s << "no";
    }
    else {
	cerr << "SegmentRep::attribute: Invalid attribute requested!" << endl;
        s << "";
    }
    return s.str(); 
}

void SegmentRep::attributeIs(const string& _attr, const string& _v){
    DCOUT( "SegmentRep:: attributeIs. attr = " << _attr << " v = " << _v << endl);
    ostringstream s; 
    s.precision(2);
    s << fixed;

    Ptr<Segment> seg = network_->segment(this->name());
    if(seg == NULL){
	s << "SegmentRep::attributeIs: Segment named " << this->name() << " not found in the network";
	cerr << s.str() << endl; 
        throw Fwk::EntityNotFoundException(s.str()); 
    }
    if ( _attr == "source") {
        Ptr<Location> oldSource = seg->source();
        if(_v == ""){	
            if(oldSource != NULL){
                DCOUT( "\tThe segment has the old source as " << oldSource->name() << endl);
                oldSource->segmentDel(seg);
                seg->sourceIs(NULL);
            } 
        } else {
            Ptr<Location> newSource = network_->location(_v);
            if(newSource == NULL){
		s << "SegmentRep::attributeIs: Tried to set invalid location = " << _v <<
		    ", as the source for " << this->name(); 
		cerr << s.str() << endl;
		throw Fwk::EntityNotFoundException(s.str());
            } else {
                DCOUT( "\tThe segment new source "<< newSource->name() << " was found in the network." << endl);
                Segment::Type segType = seg->type();
                Location::LocationType locType = newSource->type(); 
                bool compatible = false; 
                if(segType == Segment::truck_ && (locType == Location::Customer_ || 
                    locType == Location::Port_ || locType == Location::TruckTerminal_))
                    compatible = true;
                if(segType == Segment::boat_ && (locType == Location::Customer_ || 
                    locType == Location::Port_ || locType == Location::BoatTerminal_))
                    compatible = true;
                if(segType == Segment::plane_ && (locType == Location::Customer_ || 
                    locType == Location::Port_ || locType == Location::PlaneTerminal_))
                    compatible = true;
                
                if(compatible){
		    if(oldSource != NULL){
            	        DCOUT( "The segment has the old source as " << oldSource->name() << endl);
			DCOUT( "\tDecoupling old source and segment." << endl); 
            	        oldSource->segmentDel(seg);
            	    }
                    seg->sourceIs(newSource); 
                    newSource->segmentIs(seg);
                } else {
		    s << "SegmentRep::attributeIs: Incompatible location = " << _v <<" and segment = " 
			<< this->name() <<". Cannot link together.";
		    cerr << s.str() << endl;
		    throw Fwk::UnknownTypeException(s.str()); 
                }
            }
        }
    }
    else if ( _attr == "return segment"){
        Ptr<Segment> oldRetSeg = seg->returnSegment();
        if(_v == "") {
	    if(oldRetSeg != NULL ) 
		oldRetSeg->returnSegmentIs(NULL);
	    seg->returnSegmentIs(NULL);
        } else {
            Ptr<Segment> newRetSeg = network_->segment(_v);
            if(newRetSeg == NULL) {
		s << "SegmentRep::attributeIs: Could not set return segment = " << _v << " for the segment = " 
		    << this->name() << " because the return segment entity was NOT found in the network.";
		cerr << s.str() << endl;
		throw Fwk::EntityNotFoundException(s.str()); 
	    }
            else {
                if(seg->type() != newRetSeg->type()) {
		    s << "SegmentRep::attributeIs: return segment = " << _v << " and the segment = " 
			<< this->name() << " are of INCOMPATIBLE TYPES.";
		    cerr << s.str() << endl;
		    throw Fwk::UnknownTypeException(s.str()); 
		}
                else {
		    if(oldRetSeg != NULL )
			oldRetSeg->returnSegmentIs(NULL);
                    seg->returnSegmentIs(newRetSeg); 
                    newRetSeg->returnSegmentIs(seg);
                }
            }
        }
    }
    else if (_attr == "length") {
	double t = 1.00 * atof(_v.c_str()); 
	if(t < Miles::min()){
	    s << "SegmentRep::attributeIs: Segment = " << this->name() << ". Invalid Segment length attribute value = " << t; 
	    cerr << s.str() << endl;
	    throw Fwk::RangeException(s.str()); 
	} else {
	    seg->lengthIs(t);
	}
    }
    else if (_attr == "difficulty") { 
	double t = 1.00 * atof(_v.c_str()); 
	if(t < DifficultyLevel::min() || t > DifficultyLevel::max()){
	    s << "SegmentRep::attributeIs: Segment = " << this->name() << ". Invalid Segment difficulty level attribute value = " << t; 
	    cerr << s.str() << endl;
	    throw Fwk::RangeException(s.str()); 
	}
	else {
	    seg->difficultyIs(t);
	}
    }
    else if (_attr == "expedite support"){
        Segment::ExpeditedSupport es; 
        if(_v == "yes")         es = Segment::SupportPresent();
        else if (_v == "no")    es = Segment::SupportAbsent();
        else{
	    s << "SegmentRep::attributeIs: Segment = " << this->name() << ". Invalid Segment expedite support attribute value = " << _v; 
	    cerr << s.str() << endl;
	    throw Fwk::RangeException(s.str()); 
        }
        network_->segmentExpeditedSupportIs(this->name(),es);
    }
    else {
	s << "SegmentRep::attributeIs: Segment = " << this->name() << ". Trying to modify an Invalid Segment attribute = " << _attr; 
	cerr << s.str() << endl;
	throw Fwk::UnknownAttrException(s.str()); 
    }
}

TruckSegmentRep::TruckSegmentRep(const string &_name, Ptr<Network> _network):SegmentRep(_name,_network){
    Ptr<TruckSegment> t = TruckSegment::truckSegmentNew(_name, network_->virtualTimeActivityManager(), network_->fleet());
    if(t == NULL){
	ostringstream s; 
	s << "TruckSegmentRep:: constructor: Could not create a Truck segment entity " 
	    << _name <<  ", for the network.";
	cerr << s.str() << endl; 
        throw Fwk::MemoryException(s.str());
    }
    network_->segmentIs(_name, t);
}

BoatSegmentRep::BoatSegmentRep(const string &_name, Ptr<Network> _network):SegmentRep(_name,_network){
    Ptr<BoatSegment> b = BoatSegment::boatSegmentNew(_name, network_->virtualTimeActivityManager(), network_->fleet());
    if(b == NULL){
	ostringstream s; 
	s << "BoatSegmentRep:: constructor: Could not create a Boat segment entity " 
	    << _name <<  ", for the network.";
	cerr << s.str() << endl; 
        throw Fwk::MemoryException(s.str());
    }
    network_->segmentIs(_name, b);
}

PlaneSegmentRep::PlaneSegmentRep(const string &_name, Ptr<Network> _network):SegmentRep(_name,_network){
    Ptr<PlaneSegment> p = PlaneSegment::planeSegmentNew(_name, network_->virtualTimeActivityManager(), network_->fleet());
    if(p == NULL){
	ostringstream s; 
	s << "PlaneSegmentRep:: constructor: Could not create a Plane segment entity " 
	    << _name <<  ", for the network.";
	cerr << s.str() << endl; 
        throw Fwk::MemoryException(s.str());
    }
    network_->segmentIs(_name, p);
}

TruckSegmentRep::~TruckSegmentRep(){
    DCOUT( "In the destructor of TruckSegmentRep. Deleting instance and entity " << this->name() <<" from the manager and network resp." << endl);
    network_->segmentDel(this->name());    
}

BoatSegmentRep::~BoatSegmentRep(){
    DCOUT( "In the destructor of BoatSegmentRep. Deleting instance and entity " << this->name() <<" from the manager and network resp." << endl);
    network_->segmentDel(this->name());    
}

PlaneSegmentRep::~PlaneSegmentRep(){
    DCOUT( "In the destructor of PlaneSegmentRep. Deleting instance and entity " << this->name() <<" from the manager and network resp." << endl);
    network_->segmentDel(this->name());    
}
