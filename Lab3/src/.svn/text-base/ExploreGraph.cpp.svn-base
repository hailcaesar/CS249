/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/
#include "ExploreGraph.h"
using namespace Shipping;
using namespace std;

/*************************** ExploreGraph *************************************/
ExploreGraph::ExploreGraph(Conn::ExploreRequirements _exploreReqs, Location::PtrConst _source, Fwk::Ptr<Conn> _conn) : PathGraph(_source, _conn){
    exploreRequirements_ = _exploreReqs;
    DCOUT( "BFS :: EXPLORE BEGIN " << endl);
    breadthFirstSearch();
    pathList_.pop_front(); 
    printPaths();
    DCOUT( "BFS :: EXPLORE END " << endl);
};

void ExploreGraph::breadthFirstSearch() {
    printRequirements();

    while(!pathQueue_.empty()){
        Path::Ptr firstPath = this->firstPath();                                                    //Access front of queue
        int first = 1;
        Location::PtrConst curLocation = firstPath->lastElement()->location_;                       //last location of the path
        Path::Ptr curPath = firstPath->clone();
        for (Location::SegmentItConst iterator = curLocation->iterBegin(); iterator != curLocation->iterEnd(); iterator++){
            PathElement_t element = PathGraph::pathElementNew(*iterator);
            if (meetsRequirements(firstPath, element)) {
                firstPath->lastElement()->segment_ = (*iterator);
                firstPath->lastElement()->returnSegment_ = (*iterator)->returnSegment();
                DCOUT( "BFS:: AddingPath" << endl);
                Path::Ptr newPath = PathNew(firstPath, curPath,  element);                          //modifies firstPath on first iteration
            }
            else DCOUT( "BFS:: doesn't meet reqs" << endl);
        }
        if (curPath->pathSize() >= 2 && first == 0)pathList_.push_back(curPath->clone());           //current one was modified! so add to path
        pathQueue_.pop();
    }
}



int ExploreGraph::meetsRequirements(Path::Ptr _path, PathElement_t _pathElement) {
    for (Path::PathElemIt iterator = _path->iterBegin(); iterator != _path->iterEnd(); iterator++){
        DCOUT( "Element already exists in the path" << endl);
        if (iterator->location_->name() == _pathElement.location_->name()) return 0;
    }
    assert(_pathElement.segment_);
    if (_path->time() + segmentTime(_pathElement.segment_, _path->expeditedSupport()) > exploreRequirements_.time_.value())     return 0;
    if (_path->cost() + segmentCost(_pathElement.segment_, _path->expeditedSupport()) > exploreRequirements_.cost_.value())     return 0;
    if (_path->distance() + _pathElement.segment_->length() > exploreRequirements_.length_.value())                             return 0;
    if((_pathElement.segment_->expeditedSupport() == Segment::SupportAbsent()) &&
       (exploreRequirements_.expeditedSupport_ == Segment::SupportPresent()))                                                   return 0;
    
    return 1;
};

void ExploreGraph::printRequirements(){
    DCOUT( "Requiremenets" << endl);
    DCOUT( "Time = " << exploreRequirements_.time_.value() << endl);
    DCOUT( "Cost = " << exploreRequirements_.cost_.value() << endl);
    DCOUT( "Length = " << exploreRequirements_.length_.value() << endl);
    if(exploreRequirements_.expeditedSupport_ == Segment::SupportPresent()) DCOUT( "Expedited = Yes" << endl);
    else DCOUT( "Expedited = No" << endl);
}

void ExploreGraph::printPaths(){
    DCOUT( "BFS:: PathList Size = " << pathList_.size() << endl);
    DCOUT( "BFS:: FirstPath Size = " << pathList_.back()->pathSize() << endl);
    DCOUT( "BFS :: Final Explore Paths: " << endl);
    int i = 0;
    for(PathGraph::PathIt it = this->iterBegin(); it != this->iterEnd(); ++it, ++i){
        DCOUT( "Path " << i+1 << ": " << endl);
        DCOUT( "Path " << i+1 << ": Size = " << (*it)->pathSize() << endl);
        for(Path::PathElemIt iterator = (*it)->iterBegin(); iterator != (*it)->iterEnd(); ++iterator){
            DCOUT( iterator->location_->name() << " ");
            DCOUT( iterator->segment_->name() << " ");
            DCOUT( iterator->returnSegment_->name() << endl);
        }
    }
}
