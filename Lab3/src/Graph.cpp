/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/
#include "Graph.h"
#include "Fleet.h"
using namespace Shipping;
using namespace std;

/******************************************** Path ********************************************************/

Path::Path() {
    expeditedSupport_ = Segment::SupportPresent();
    cost_ = 0;
    distance_ = 0;
    time_ = 0;
};

void Path::costIs(Dollars _cost){
    DCOUT( "Path::CostIs = " << _cost.value() << endl);
    cost_ = _cost;
}

void Path::distanceIs(Miles _distance) {
    DCOUT( "Path::DistanceIs = " << _distance.value() << endl);
    distance_ = _distance;
};

void Path::expeditedSupportIs(Segment::ExpeditedSupport _expeditedSupport){
    expeditedSupport_ = _expeditedSupport;
};

void Path::pathElementIs(PathElement_t _pathElement){
    assert(_pathElement.location_);
    DCOUT( "Path::pathElementIs:  location: " << _pathElement.location_->name() << endl);
    pathElements_.push_back(_pathElement);
    DCOUT( "Path:: Size =  " << pathElements_.size() << endl);

}

void Path::timeIs(Hours _time){
    DCOUT( "Path::timeIs = " << _time.value() << endl);
    time_ = _time;
}

Path::Ptr Path::clone() {
    Path::Ptr clone = new Path();
    clone->costIs(this->cost_);
    clone->distanceIs(this->distance_);
    clone->timeIs(this->time_);
    clone->pathElements_ = this->pathElements_;
    return clone;
};



/******************************************** Path Graph ***************************************************/

PathGraph::PathGraph(Location::PtrConst _source, Fwk::Ptr<Conn> _conn){
    DCOUT( "PathGraph :: Constructor :: source = " << _source->name() << endl);
    PathElement_t elem;
    this->conn_ = _conn;
    this->source_ = _source;
    Path::Ptr path = new Path();                                        
    elem.location_ = _source;
    path->pathElementIs(elem);
    pathList_.push_back(path);
    pathQueue_.push(path);
};



float PathGraph::segmentCost(Segment::PtrConst _segment, Segment::ExpeditedSupport _es) const{
    float cost = _segment->length().value() *                   //length in miles
                  typeCost(_segment->type()).value() *          //cost per mile of that segment type
                 _segment->difficulty().value();                //difficutly
    if (_es == Segment::SupportPresent() && _segment->expeditedSupport() == Segment::SupportPresent()) cost = cost * 1.5;
    return cost;
};


float PathGraph::segmentTime(Segment::PtrConst _segment, Segment::ExpeditedSupport _es) const{
    if (_segment->expeditedSupport() == Segment::SupportPresent() && _es == Segment::SupportPresent())
        return _segment->length().value() / (typeSpeed(_segment->type()).value() * 1.3);
    else
        return _segment->length().value() / (typeSpeed(_segment->type()).value());
};


DollarsPerMile PathGraph::typeCost(Segment::Type type) const{
    if(type == Segment::boat_)       return conn_->network()->fleet()->cost(Fleet::boat());
    else if(type == Segment::plane_) return conn_->network()->fleet()->cost(Fleet::plane());
    else if(type == Segment::truck_) return conn_->network()->fleet()->cost(Shipping::Fleet::truck());
    else{
        DCOUT( "Error:  Invalid setgment type: " << type << endl);
        return 0;
    }
};

MilesPerHour PathGraph::typeSpeed(Segment::Type type) const{
    if(type == Segment::boat_)       return conn_->network()->fleet()->speed(Fleet::boat());
    else if(type == Segment::plane_) return conn_->network()->fleet()->speed(Fleet::plane());
    else if(type == Segment::truck_) return conn_->network()->fleet()->speed(Shipping::Fleet::truck());
    else return MilesPerHour::min();
};

PathElement_t PathGraph::pathElementNew(Segment::PtrConst _segment) {
    if(_segment->source() && _segment->name() && _segment->returnSegment() && _segment->returnSegment()->source())
        DCOUT( "PathGraph::pathElementNew:: Adding new Path Element: " << endl);
        DCOUT( "Elem::Segment's Source =          " << _segment->source()->name() << endl);
        DCOUT( "Elem::Segment =                   " << _segment->name() << endl);
        DCOUT( "Elem::Return Segment =            " << _segment->returnSegment()->name() << endl);
        DCOUT( "Elem::Return Segment's source =   " << _segment->returnSegment()->source()->name() << endl);
    }
    else return NULL;

    Segment::PtrConst retSeg = _segment->returnSegment();
    PathElement_t elem;
    elem.location_ = _segment->returnSegment()->source();
    elem.returnSegment_ = _segment->returnSegment();
    elem.segment_ = _segment;
    assert(elem.location_);
    assert(elem.segment_);
    assert(elem.returnSegment_);
    return elem;
}

Path::Ptr PathGraph::PathNew(Path::Ptr _curPath, Path::Ptr _firstPath, PathElement_t _pathElement) {
    Path::Ptr newPath = _curPath->clone();
    newPath->pathElementIs(_pathElement);
    newPath->costIs(Dollars(segmentCost(_pathElement.segment_, newPath->expeditedSupport()) + newPath->cost().value()));
    newPath->distanceIs(Miles(_pathElement.segment_->length().value() + newPath->distance().value()));
    newPath->timeIs(Hours(segmentTime(_pathElement.segment_, newPath->expeditedSupport()) + newPath->time().value()));
    pathList_.push_back(newPath);
    pathQueue_.push(pathList_.back());
    return pathQueue_.back();
};



//DCOUT( "old cost = " << newPath->cost().value() << endl);
//DCOUT( "old time = " << newPath->time().value() << endl);
//DCOUT( "new cost = " << segmentCost(_pathElement.segment_, newPath->expeditedSupport()) + newPath->cost().value() << endl);
//DCOUT( "new time = " << segmentTime(_pathElement.segment_, newPath->expeditedSupport()) + newPath->time().value() << endl);


