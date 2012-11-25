//
//  RoutingInfoBase.h
//  Lab3
//
//  Created by cdelapaz on 11/19/12.
//  Copyright (c) 2012 cdelapaz. All rights reserved.
//

#ifndef __Lab3__RoutingInformationBase__
#define __Lab3__RoutingInformationBase__

#include <iostream>

#include <map>
#include "PtrInterface.h"
#include "Ptr.h"
#include <string>
#include "Conn.h"
#include "Node.h"
#include "Graph.h"
#include <map>
#include <list>
#include <set>


namespace Shipping {
    class Location;
    class Segment;
    class ShortestDistance;
    class Conn;
    class RoutingInformationBase : public Fwk::PtrInterface<RoutingInformationBase>{
    public:
        //Constructor
        RoutingInformationBase(Conn::Ptr _conn);
        
        typedef Fwk::Ptr<RoutingInformationBase const> PtrConst;
        typedef Fwk::Ptr<RoutingInformationBase> Ptr;
        
        //Enum
        enum Status {updated, updateNeeded};
        enum Algorithm {BFS, Dijkstra};
        
        
        //Accessor
        Location::PtrConst nextHop (Location::Ptr, Location::Ptr);
        Status status() const { return status_;}
        Fwk::Ptr<Node> breadthFirstSearch(std::string);
        Fwk::Ptr<Node> dijkstra(std::string source);
        
        //Mutator
        void statusIs(Status _status);

        
    private:
        std::map<const std::string, Fwk::Ptr<Node> > routeTable_;
        Fwk::Ptr<Conn> conn_;
        Status status_;
        Algorithm algorithm_;
        RoutingInformationBase();
        RoutingInformationBase(const RoutingInformationBase & );
        
        void routeTableUpdate();
        int findKeybyValue(std::map<int, std::string>& map, std::string value);

    };
};



#endif /* defined(__Lab3__RoutingInformationBase__) */
