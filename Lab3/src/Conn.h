/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#ifndef _CONN_H_
#define _CONN_H_

#include <iostream>
#include "fwk/Ptr.h"
#include "fwk/PtrInterface.h"
#include "fwk/NamedInterface.h"
#include "ShippingValueTypes.h"
#include "Network.h"
#include "Location.h"
#include "Segment.h"
#include "Fleet.h"

namespace Shipping {
    class Network; 
    class PathGraph;
    class ExploreGraph;
    class ConnectGraph;

    class Conn : public Fwk::NamedInterface{
    public:

        struct ExploreRequirements{
            Hours time_;
            Dollars cost_;
            Miles length_;
            Segment::ExpeditedSupport expeditedSupport_;
            
        };

        typedef Fwk::Ptr<Conn const> PtrConst;
        typedef Fwk::Ptr<Conn> Ptr;
        
        //Accessor
        Fwk::Ptr<Network> network() const{return network_;};
	    
        //Algorithms
        Fwk::Ptr<PathGraph> exploration(std::string & _source, Dollars _cost, Hours _time, Miles _distance, Segment::ExpeditedSupport _es);
        Fwk::Ptr<PathGraph> connection(const std::string & _source, const std::string & _destination);
        static Conn::Ptr connNew(const std::string & _name, Fwk::Ptr<Network> _network );

    private:
        Conn();
        Conn(const Conn &); 
        Conn(const std::string & _name, Fwk::Ptr<Network> _network);
        Fwk::Ptr<Network> network_;
    };
}
#endif
