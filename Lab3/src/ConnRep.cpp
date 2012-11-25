/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include "ConnRep.h"
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <vector>
#include "ShippingValueTypes.h"
#include "Graph.h"
#include "fwk/Exception.h"

using namespace Shipping;
using namespace std;
using namespace boost; 
    	    
ConnRep::ConnRep(const string& _name, Ptr<Network> _network):
    Instance(_name){
    if(conn_ != NULL) return;
    conn_ = Conn::connNew(_name, _network);
    if(conn_ == NULL) {
	ostringstream s; 
	s << "Could not create a Conn object for the network" ;
	cerr << s.str() << endl;
	throw Fwk::MemoryException(s.str());
    }
}

string ConnRep::attribute(const string& _attr){
    char_separator<char> sep(" :");
    tokenizer< char_separator<char> > tokens(_attr, sep);
    vector<string> fields; 
    BOOST_FOREACH (const string& t, tokens) {
        fields.push_back(t); 
    }
    ostringstream s;
    s.precision(2);
    s << fixed; 
    if(fields[0] == "explore"){
        string srcName; 
        Miles distance; 
        Dollars cost; 
        Hours time; 
        Segment::ExpeditedSupport es = Segment::SupportAbsent();

        srcName = fields[1]; 

        for(unsigned int i = 2; i < fields.size(); i += 2){
            if(fields[i] == "distance")         distance = atof(fields[i+1].c_str());
            else if (fields[i] == "cost")       cost = atof(fields[i+1].c_str());
            else if (fields[i] == "time")       time = atof(fields[i+1].c_str());
            else if (fields[i] == "expedited")  es = Segment::SupportPresent();
            else {
                DCOUT("Invalid Conn command: " << _attr << endl);
                return "";
            }
        }
        PathGraph::Ptr g = conn_->exploration(srcName, cost, time, distance, es);
        for(PathGraph::PathIt it = g->iterBegin(); it != g->iterEnd(); ++it){
            s << pathString(*it); 
        }
        return s.str(); 
    }
    else if (fields[0] == "connect"){
        string srcName, dstName;
        srcName = fields[1]; 
        dstName = fields[2]; 
        PathGraph::Ptr g = conn_->connection(srcName, dstName);
		if(g->iterBegin() == g->iterEnd()){
            return ""; 
        }
        for(PathGraph::PathIt it = g->iterBegin(); it != g->iterEnd(); ++it){
            s << (*it)->cost().value() << " "
              << (*it)->time().value() << " ";
            Segment::ExpeditedSupport es = (*it)->expeditedSupport();
            if(es == Segment::SupportPresent()) s << "yes; ";
            else                                s << "no; ";
            s << pathString(*it); 
        }
        return s.str(); 
    }
    else {
        DCOUT("Invalid Conn command: " << _attr << endl);
        return ""; 
    }
}

string ConnRep::pathString(Path::Ptr p){
    ostringstream s;
    s.precision(2);
    s << fixed; 

    DCOUT("ConnRep::pathString " << endl); 
    for(Path::PathElemIt it = p->iterBegin(); it != p->iterEnd(); ++it){
	Path::PathElemIt next = it; 
	++next;
	if(next != p->iterEnd()){
	    s  << it->location_->name() << "("
        <<  it->segment_->name() << ":"
        << it->segment_->length().value() << ":"
        << it->returnSegment_->name() << ") ";
	} else {
	    s << it->location_->name() << "\n";
	    break; 
	}
    }
    return s.str();
} 


void ConnRep::attributeIs(const string& _name, const string& _v){
    /* Nothing to do here. This class only works as
       a response to a query. */
}


