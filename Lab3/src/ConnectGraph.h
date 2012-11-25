/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#ifndef _CONNECTGRAPH_
#define _CONNECTGRAPH_

#include <iostream>
#include "Graph.h"
#include "Location.h"
namespace Shipping{
    class ConnectGraph : public PathGraph {
    public:
        ConnectGraph(Fwk::Ptr<Conn> _conn, Fwk::Ptr<Location const> _source, Fwk::Ptr<Location const> _destination);
    private:
        Location::PtrConst destination_;
        void modifyLastElement(PathElement_t& _element, Segment::Ptr _segment);
        void breadthFirstSearch();
        int elementValid(Path::Ptr _path, PathElement_t _pathElem);
        void cleanPaths();
        void printPaths();
        
    };
}

#endif 
