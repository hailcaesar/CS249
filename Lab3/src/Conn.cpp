/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/
#include "Conn.h"
#include "ExploreGraph.h"
#include "ConnectGraph.h"

using namespace Shipping;
using namespace std; 


Conn::Conn(const string & _name, Fwk::Ptr<Network> _network) :
    Fwk::NamedInterface(_name), 
    network_(_network) {} 

Conn::Ptr Conn::connNew(const string & _name, Fwk::Ptr<Network> _network){
    Conn::Ptr conn = new Conn(_name,_network);
    return conn; 
}


PathGraph::Ptr Conn::exploration(string& _source, Dollars _cost, Hours _time, Miles _distance, Segment::ExpeditedSupport _es){
    if(network_->location(_source) == NULL){
        DCOUT("Segment could not be found" << endl);
        return NULL;
    }

    Conn::ExploreRequirements exploreReqs = {_time, _cost, _distance};
    PathGraph::Ptr exploreGraph = new ExploreGraph(exploreReqs, network_->location(_source), this);
    return exploreGraph;
};

PathGraph::Ptr Conn::connection(const string& _source, const string& _destination){
    if (network_->location(_source) == NULL || network_->location(_destination) == NULL) {
        DCOUT("Error:  start or end location not found!" << endl);
        return NULL;
    }
    PathGraph::Ptr connectGraph = new ConnectGraph(this, static_cast<Location::PtrConst>(network_->location(_source)),
                                                   static_cast<Location::PtrConst>(network_->location(_destination)));
    return connectGraph;
};


