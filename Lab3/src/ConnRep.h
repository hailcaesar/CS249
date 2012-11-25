/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/
#ifndef _CONNREP_H_
#define _CONNREP_H_

#include "Network.h"
#include "Instance.h"
#include "Conn.h"
#include "Graph.h"

namespace Shipping {
    class ConnRep : public Instance {
	public:
    	    ConnRep(const string& _name, Ptr<Network> _network);
    	    string attribute(const string& _attr);
    	    void attributeIs(const string& _name, const string& _v);
    	protected:
    	    Ptr<Conn> conn_; 
	private:
	    std::string pathString(Path::Ptr it); 
    };
}

#endif
