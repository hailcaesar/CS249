/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#ifndef _EXPLOREGRAPH_
#define _EXPLOREGRAPH_

#include <iostream>
#include "Graph.h"

namespace Shipping {
    class ExploreGraph : public PathGraph {
    public:
        ExploreGraph(Conn::ExploreRequirements _exploreReqs, Location::PtrConst _source, Fwk::Ptr<Conn> _conn);
    private:
        void breadthFirstSearch();
        int meetsRequirements(Path::Ptr, PathElement_t);
        Conn::ExploreRequirements exploreRequirements_;
        void printRequirements();
        void printPaths();
    };
}

#endif 
