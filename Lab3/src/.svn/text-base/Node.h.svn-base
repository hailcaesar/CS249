//
//  Node.h
//  Lab3
//
//  Created by cdelapaz on 11/19/12.
//  Copyright (c) 2012 cdelapaz. All rights reserved.
//

#ifndef __Lab3__Node__
#define __Lab3__Node__

#include <iostream>



#include "PtrInterface.h"
#include "Ptr.h"
#include <string>
#include <map>
#include "Location.h"

namespace Shipping {
    class Node : public Fwk::PtrInterface<Node> {
    public:
        typedef Fwk::Ptr<Node const> PtrConst;
        typedef Fwk::Ptr<Node> Ptr;
        std::map<std::string, Location::Ptr > nextHop;  //{destination string, Location of next hop}
    };
}



#endif /* defined(__Lab3__Node__) */
