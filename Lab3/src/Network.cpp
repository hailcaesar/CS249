/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/
#include "Network.h"
#include <iostream>
#include <sstream>
#include "fwk/Exception.h"

using namespace Shipping;
using namespace std;

Network::Network(std::string _name) : NamedInterface(_name){
    ostringstream s; 

    realTimeActivityManager_ = 	RealTimeActivityManager::RealTimeActivityManagerNew( 
	    "RealTimeActivityManager"); 
    if(realTimeActivityManager_ == NULL){
	s << "Network constructor: Could not create a RealTimeActivityManager.";
	cerr << s.str() << endl;
	throw Fwk::MemoryException(s.str()); 
    }
    
    virtualTimeActivityManager_ = VirtualTimeActivityManager::VirtualTimeActivityManagerNew(
	    "VirtualTimeActivityManager"); 
    if(virtualTimeActivityManager_ == NULL){
	s << "Network constructor: Could not create a VirtualTimeActivityManager.";
	cerr << s.str() << endl; 
	throw Fwk::MemoryException(s.str()); 
    }

    /* Coupling the Real and virtual time activity managers */
    virtualTimeActivityManager_->realTimeActivityManagerIs(realTimeActivityManager_); 
    realTimeActivityManager_->virtualTimeActivityManagerIs(virtualTimeActivityManager_); 

}

Network::Ptr Network::networkNew(std::string _name){
    Network::Ptr n = new Network(_name);  
    return n;
}

void Network::fleetIs(Fwk::Ptr<Fleet> _fleet){
    if(fleet_ == _fleet){
	return; 
    }
    fleet_ = _fleet;
}

void Network::locationIs(const string & _name, Fwk::Ptr<Location> _location){
    std::map<const string, Location::Ptr >::iterator it;
    it = location_.find(_name);
    if(it != location_.end()){
	if(_location != NULL){ 
	    /* location already exists */
	    return; 
	}
    }
    location_[_name] = _location;
    for( notifieeIter it = notifiee_.begin(); it != notifiee_.end(); ++it){
	(it->second)->onLocationNew(_location); 
    }
}

void Network::segmentIs(const std::string & _name, Fwk::Ptr<Segment> _segment){
    DCOUT( "Network::segmentIs : called for name " << _name << "to be set to " << _segment.ptr() << "\n");
    std::map<const string, Segment::Ptr >::iterator it;
    it = segment_.find(_name);
    if(it != segment_.end()){
	if(_segment != NULL){
	    /* Segment already exists.*/
	    return; 
	}   
    }
    segment_[_name] = _segment; 
    for( notifieeIter it = notifiee_.begin(); it != notifiee_.end(); ++it){
	(it->second)->onSegmentNew(_segment); 
    }
}
	    
void Network::segmentExpeditedSupportIs(const std::string & _name, Segment::ExpeditedSupport es){
    std::map<const string, Segment::Ptr >::iterator it;
    it = segment_.find(_name);
    if(it == segment_.end()){
	/* segment not found */
	return;
    }
    if (segment_[_name] == NULL)
	return;
    Segment::ExpeditedSupport esOld = segment_[_name]->expeditedSupport();
    if(esOld == es) //If there is no change then return
	return; 
    
    int flag = 0; // Made to be no expedited support
    if(es == Segment::SupportPresent())
	flag = 1; // Now there is support
    segment_[_name]->expeditedSupportIs(es);
    DCOUT( "Network::segmentExpeditedSupportIs: name = " << _name << " support = " << es << endl);
    DCOUT( "checking the segment's just set support = " << segment_[_name]->expeditedSupport() << endl);
    for( notifieeIter it = notifiee_.begin(); it != notifiee_.end(); ++it){
	if(flag == 0)
	    (it->second)->onSegmentExpeditedSupportRemoval(segment_[_name]); 
	else
	    (it->second)->onSegmentExpeditedSupportAddition(segment_[_name]); 
    }
}

Fwk::Ptr<Location> Network::location(const std::string & _name){
    std::map<const string, Location::Ptr >::iterator it;
    it = location_.find(_name);
    if(it != location_.end()){
	return it->second; 
    }
    return Fwk::Ptr<Location>(NULL); 
}

Fwk::Ptr<Segment> Network::segment(const std::string & _name){
    std::map<const string, Segment::Ptr >::iterator it;
    it = segment_.find(_name);
    if(it != segment_.end()){
	return it->second; 
    }
    return Fwk::Ptr<Segment>(NULL); 
}

void Network::notifieeIs(const string & _name, Notifiee * _notifiee){
    notifiee_[_name] = _notifiee;
}

void Network::segmentDel(const std::string & _name){
    Fwk::Ptr<Segment> seg = segment_[_name];
    if(seg == NULL)
	return; 

    Fwk::Ptr<Location> source = seg->source();
    if(source != NULL)
        source->segmentDel(seg);

    seg->sourceIs(NULL); 
	
    Fwk::Ptr<Segment> retSeg = seg->returnSegment();
    if(retSeg != NULL)
	retSeg->returnSegmentIs(NULL);
    
    for( notifieeIter it = notifiee_.begin(); it != notifiee_.end(); ++it){
	(it->second)->onSegmentDel(seg); 
    }
    seg->~Segment(); 
}   	

void Network::locationDel(const std::string & _name){
    Fwk::Ptr<Location> loc = location_[_name];
    if(loc == NULL)
	return;
    
    for(Location::SegmentIt it = loc->iterBegin(); it != loc->iterEnd(); ++it){
	(*it)->sourceIs(NULL); 
    }
    for( notifieeIter it = notifiee_.begin(); it != notifiee_.end(); ++it){
	(it->second)->onLocationDel(loc); 
    }
    loc->~Location(); 
}
