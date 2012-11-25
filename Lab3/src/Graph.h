/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#ifndef _GRAPH_
#define _GRAPH_

#include <iostream>
#include "Location.h"
#include "Segment.h"
#include "Conn.h"
#include <queue>
#include <list>

namespace Shipping {
    typedef struct{
        Segment::PtrConst segment_;
        Segment::PtrConst returnSegment_;
        Location::PtrConst location_;
    } PathElement_t;

    class Path : public Fwk::PtrInterface<Path> {
    public:
        typedef Fwk::Ptr<Path const> PtrConst;
        typedef Fwk::Ptr<Path> Ptr;
    
        //Constructor
        Path();
    
        //Mutators
        void costIs(Dollars _cost);
        Ptr clone();                  //not needed!
        void distanceIs(Miles _distance);
        void expeditedSupportIs(Segment::ExpeditedSupport _expeditedSupport);
        void pathElementIs(PathElement_t _pathElement);
        size_t pathSize() const { return pathElements_.size(); }
        void timeIs(Hours);
        void removeFront(){ pathElements_.pop_front();}
                                                 
        //Accessors
        Dollars cost() const {return cost_;}
        Miles distance() const { return distance_;}
        Segment::ExpeditedSupport expeditedSupport() const { return expeditedSupport_;}
        PathElement_t * lastElement()  { return &pathElements_.back();}
        PathElement_t * firstElement()  { return &pathElements_.front();}
        Hours time() const { return time_; }
        
    
        //Iterators
        typedef std::list<PathElement_t>::iterator PathElemIt;
        typedef std::list<PathElement_t>::const_iterator PathElemItConst;
    
        PathElemIt iterBegin() { return pathElements_.begin(); }
        PathElemIt iterEnd() { return pathElements_.end(); }
    private:
        Path(const Path&);
    
        //Segments
        std::list<PathElement_t> pathElements_;
    
        //Metrics
        Dollars cost_;
        Miles distance_;
        Hours time_;
        Segment::ExpeditedSupport expeditedSupport_;
    };
    
    class PathGraph : public Fwk::PtrInterface<PathGraph>{
    public:
        typedef Fwk::Ptr<PathGraph const> PtrConst;
        typedef Fwk::Ptr<PathGraph> Ptr;

        //Iterators
        typedef std::list<Path::Ptr>::iterator PathIt;
        typedef std::list<Path::Ptr>::const_iterator PathItConst;
        PathIt iterBegin() { return pathList_.begin(); }
        PathIt iterEnd() { return pathList_.end(); }
    protected:
        PathGraph(Location::PtrConst _source, Fwk::Ptr<Conn> _conn);
        PathGraph();
        PathGraph(const PathGraph &);

        //Attributes
        std::queue<Path::Ptr> pathQueue_;
        std::list<Path::Ptr> pathList_;
        Fwk::Ptr<Conn> conn_;
        Location::PtrConst source_;

        
        //Accessors
        std::list<Path::Ptr> pathList() { return pathList_; }
        Path::Ptr firstPath() const { return pathQueue_.front();}
        Path::Ptr lastPath() const { return pathQueue_.back();}
        Location::PtrConst location(const string & _locationName);
        Segment::PtrConst segment(const string & _segmentName);
        float segmentCost(Segment::PtrConst _segment, Segment::ExpeditedSupport _es) const;
        float segmentTime(Segment::PtrConst _segment, Segment::ExpeditedSupport _es) const;
        MilesPerHour typeSpeed(Segment::Type type) const;
        DollarsPerMile typeCost(Segment::Type type) const;
        bool queueEmpty() const { return pathQueue_.empty(); }
        
        //Mutator
        static PathElement_t pathElementNew(Segment::PtrConst _segment);
        void queueDel(){ pathQueue_.pop();}
        

        //Instantiating Attributes
        Path::Ptr PathNew(Path::Ptr _curPath, Path::Ptr _firstPath, PathElement_t _pathElement);
    

    };
    



    
}; 

#endif /* defined(__Lab2__Graph__) */
