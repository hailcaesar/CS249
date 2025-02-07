/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#include "ConnectGraph.h"
using namespace Shipping;
using namespace std;
/*************************** ConnectGraph *************************************/

ConnectGraph::ConnectGraph(Fwk::Ptr<Conn>  _conn, Fwk::Ptr<Location const> _source, Fwk::Ptr<Location const> _destination) : PathGraph(_source, _conn){
    DCOUT( "BFS :: CONNECT BEGIN " << endl);
    destination_ = _destination;
    breadthFirstSearch();
    DCOUT( "BFS:: PathList Size = " << pathList_.size() << endl);
    DCOUT( "BFS:: FirstPath Size = " << pathList_.back()->pathSize() << endl);
    cleanPaths();
    printPaths();
    DCOUT( "BFS :: CONNECT END " << endl);
};

void ConnectGraph::breadthFirstSearch() {
    Path::Ptr firstPath;
    while(!queueEmpty()){
        firstPath = this->firstPath();                                                  //Access front of queue
        DCOUT( "PathListSize = " << pathList_.size() << endl);
        DCOUT( "PathSize = " << firstPath->pathSize() << endl);
        DCOUT( "first elem = " << firstPath->firstElement()->location_->name() << endl);

        if (firstPath->lastElement()->location_->name() == destination_->name()) {
            Path::Ptr path = new Path();
            PathElement_t elem;
            elem.location_ = firstPath->lastElement()->location_;
            path->pathElementIs(elem);
            queueDel();
            continue;
        }

        Location::PtrConst curLocation = firstPath->lastElement()->location_;                      //Get latest Element added to the Path
        DCOUT( "Current Location = " << curLocation->name() << endl);
        Path::Ptr curPath = firstPath->clone();                                                   //Clone current path (in case a new path is added to the List)
        for (Location::SegmentItConst iterator = curLocation->iterBegin(); iterator != curLocation->iterEnd(); iterator++){
            PathElement_t element = pathElementNew(*iterator);
            if(element == NULL) return 0;
            DCOUT( "Path firstPath: Size0 = " << firstPath->pathSize() << endl);
            if (elementValid(curPath, element)) {
                DCOUT( "Modigying: " << firstPath->lastElement()->location_->name() << endl);
                firstPath->lastElement()->segment_ = (*iterator);
                firstPath->lastElement()->returnSegment_ = (*iterator)->returnSegment();
                DCOUT( (*iterator)->name()); DCOUT( firstPath->lastElement()->location_->name() << endl);
                DCOUT( firstPath->lastElement()->segment_->name() << endl); DCOUT( firstPath->lastElement()->returnSegment_->name() << endl);
                Path::Ptr newPath = PathNew(firstPath, curPath,  element); 
                
                if (newPath->lastElement()->segment_->expeditedSupport() == Segment::SupportAbsent()) newPath->expeditedSupportIs( Segment::SupportAbsent());
            }
            else DCOUT( "BFS :: Element could NOT be added.  Element: " << element.location_->name() << endl);
        }
        DCOUT( "BFS:: Queue Size1 = " << pathQueue_.size() << endl);
        queueDel();
        DCOUT( "BFS:: Queue Size2 = " << pathQueue_.size() << endl);

    }
    return 1;
};


void ConnectGraph::cleanPaths() {
    DCOUT( "ConnectGraph::cleanPaths:  Clearing Path that don't have the correct destination" << endl);
    DCOUT( "Destination = " <<destination_->name() << endl);
    std::list<Path::Ptr> pathsToBeDeleted;
    PathGraph::PathIt iterator = this->iterBegin();
    while(iterator != this->iterEnd()){
        bool isActive = (iterator->ptr()->lastElement()->location_->name() == destination_->name());
        if (!isActive) {
            DCOUT( "Deleting Path with destination = " << iterator->ptr()->lastElement()->location_->name() << " ...... " << endl);
            pathList_.erase(iterator++);
        } else ++iterator;
    }

}

int ConnectGraph::elementValid(Path::Ptr _path, PathElement_t _pathElem) {
    for (Path::PathElemIt iterator = _path->iterBegin(); iterator != _path->iterEnd(); iterator++){
        if (iterator->location_->name() == _pathElem.location_->name()) return 0;
    }
    return 1;
};

void ConnectGraph::printPaths(){
    DCOUT( "BFS :: Final Paths: " << endl);
    int i = 0;
    for(PathGraph::PathIt it = this->iterBegin(); it != this->iterEnd(); ++it, ++i){
        DCOUT( "Path " << i+1 << ": Size = " << (*it)->pathSize() << endl);
        for(Path::PathElemIt iterator = (*it)->iterBegin(); iterator != (*it)->iterEnd(); ++iterator){
            DCOUT( iterator->location_->name() << " ");
            DCOUT( iterator->segment_->name() << " ");
            DCOUT( iterator->returnSegment_->name() << endl);
        }
    }
}
