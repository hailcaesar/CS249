//
//  RoutingInfoBase.cpp
//  Lab3
//
//  Created by cdelapaz on 11/19/12.
//  Copyright (c) 2012 cdelapaz. All rights reserved.
//

#include "RoutingInformationBase.h"

using namespace std;
using namespace Shipping;

RoutingInformationBase::RoutingInformationBase(Conn::Ptr _conn){
    conn_ = _conn;
    status_ = updateNeeded;
    algorithm_ = Dijkstra;
}


Location::PtrConst RoutingInformationBase::nextHop(Location::Ptr currLoc, Location::Ptr dst){
    Location::Ptr nextHop;
    if (status() != updateNeeded) routeTableUpdate();
    Fwk::Ptr<Node> curNode = routeTable_[currLoc->name()];                                                              //Find current Node
    
    if(curNode == NULL){
        DCOUT( "ERROR: The current location cannot be found in the Route table mapping.  Please Update" << endl);
        return NULL;            //THROW EXCEPTION????
    }
    
    if (curNode->nextHop.find(dst->name()) != curNode->nextHop.end())  nextHop = curNode->nextHop[dst->name()];         //Find next hop
    else {
        DCOUT( "ERROR: The destination specified cannot be reached from the current location" << endl);
        return NULL;            //THROW EXCEPTION????
    }
    
    Segment::Ptr desiredSegment = NULL;                                                                                 //Get Segment  curr loc <==> next hop
    for (Location::SegmentItConst iterator = currLoc->iterBegin(); iterator != currLoc->iterEnd(); iterator++){
        if((*iterator)->returnSegment()->source()->name() == nextHop->name()){                      
                desiredSegment = *iterator;
                break;
        }
    }
    
    if(desiredSegment == NULL){
        DCOUT( "ERROR: No segment connects the current and next hop location" << endl);
        return NULL;
    }

    if (desiredSegment->packagesInTransit() != desiredSegment->capacity()) { return nextHop; }
    else {                                                                                                              //Check for capacity/active packages limit
        desiredSegment->refusedShipmentsInc();
        //HOW DO WE NOTIFEE TO RESTART SEACH???
        return NULL;
    }

};


void RoutingInformationBase::routeTableUpdate() {
    Network::Ptr network = conn_->network();
    if(algorithm_ == BFS){
        for (Network::LocationIt it1 = network->locItBegin(); it1 != network->locItEnd(); ++it1)   //iterate through locations
            routeTable_[it1->second->name()] = breadthFirstSearch(it1->second->name());
            
    }
    else if (algorithm_ == Dijkstra){
        for (Network::LocationIt it1 = network->locItBegin(); it1 != network->locItEnd(); ++it1)   //iterate through locations
            routeTable_[it1->second->name()] = dijkstra(it1->second->name());
    }
    
    //else if Bellman-Ford
    status_ = updated;
}

//BFS algorithm to find the spanning tree for each node in the network
Node::Ptr RoutingInformationBase::breadthFirstSearch(std::string source) {
    Node::Ptr node = new Node();
    Location::Ptr nextHop = NULL;
    Network::Ptr network = conn_->network();
    
    for (Network::LocationIt it1 = network->locItBegin(); it1 != network->locItEnd(); ++it1){   //iterate through locations
        if(it1->second->name() == source) continue;
        Miles minLength = Miles::max();
        Location::PtrConst nextHop;
        PathGraph::Ptr paths = conn_->connection(source, it1->second->name());
        for(PathGraph::PathIt it2 = paths->iterBegin(); it2 != paths->iterEnd(); ++it2){        //iterate through paths
            Miles pathLength = (*it2)->distance();
            if (pathLength < minLength) {
                minLength = pathLength;
                Path::PathElemIt t = (*it2)->iterBegin();  ++t;
                nextHop = t->location_;
            }
        }
        node->nextHop[it1->second->name()] = nextHop;                                           //Add nextHop Location for each of the destinations
    }
    return node;
}

//Dijkstra algorithm to find the spanning tree for each node in the network
//Used pseudocode in Wikipedia.com ("Dijkstra Algorithm") as reference
Node::Ptr RoutingInformationBase::dijkstra(std::string source) {
    Node::Ptr node = new Node();
    Network::Ptr network = conn_->network();
    size_t numLocations = network->numLocations();

    map<int, std::string> translationMap;
    std::map<std::string, Location::PtrConst > previous;                //previous[]
    Miles * distance = new Miles[numLocations];                         //distance[]
    std::set<int> candidateSet;                                         //Q set

    std::map<std::string, Location::PtrConst > prev;
    
    int i = 0;
    for (Network::LocationIt it1 = network->locItBegin(); it1 != network->locItEnd(); ++it1, ++i){   //iterate through locations
        candidateSet.insert(i);
        std::string name = it1->second->name();
        translationMap[i] = name;
        previous[name] = NULL;
        if (name == source)     distance[i] = 0;
        else                    distance[i] = Miles::max();
    }
    
    while (!candidateSet.empty()) {
        Miles minDistance = Miles::max();
        int u;
        for (std::set<int>::iterator it = candidateSet.begin(); it != candidateSet.end(); ++it){
            if (distance[*it] < minDistance){
                minDistance = distance[*it];
                u = *it;
            }
        }
    
        if (minDistance == Miles::max()) break;
        candidateSet.erase(u);
        
        map<int, std::string>::iterator it = translationMap.find(u);
        if(it == translationMap.end()){
            DCOUT( "ERROR: Could not find key in dijkstra's map" << endl);
            return NULL;
        }
        Location::Ptr curLoc = network->location(it->second);
        for (Location::SegmentItConst segIt = curLoc->iterBegin(); segIt != curLoc->iterEnd(); segIt++){
            Segment::Ptr returnSegment = (*segIt)->returnSegment();
            Location::Ptr neighbor = returnSegment->source();
            Miles length = distance[u].value() + (*segIt)->length().value();
                int v = findKeybyValue(translationMap, neighbor->name());
                if(v == -1) DCOUT( "ERROR:  Key could not be found" << endl);
                if (length < distance[v]){
                    distance[v] = length;
                    prev[neighbor->name()] = curLoc;
                }
        }
    }
    
    for (int i = 0; i < numLocations; i++) {
        if (distance[i] == 0 || distance[i] == Miles::max()) continue;
        map<int, std::string>::iterator it = translationMap.find(i);
        if(it == translationMap.end()) return NULL;
        
        Location::PtrConst previousLoc = previous[it->second];
        Location::PtrConst temp = network->location(it->second);
        while (previousLoc->name() != source) {
            temp = previousLoc;
            previousLoc = previous[previousLoc->name()];
        }
        node->nextHop[it->second] = temp;
    }

    return node;

}

int RoutingInformationBase::findKeybyValue(map<int, std::string>& map, std::string value){
    std::map<int, std::string>::const_iterator it;
    int key = -1;

    for (it = map.begin(); it != map.end(); ++it){
        if (it->second == value){
            key = it->first;
            break;
        }
    }
    return key;
}







