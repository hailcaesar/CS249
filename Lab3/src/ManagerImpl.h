/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#ifndef _MANAGERIMPL_H
#define _MANAGERIMPL_H

#include <string>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include "Instance.h"
#include "Network.h"

namespace Shipping {

    class ManagerImpl : public Instance::Manager {
	public:
	    ManagerImpl(const std::string & _name);
        
        // Accessor
        Ptr<Instance> instance(const string& name);
    	
        // Instantiating Attribute
        Ptr<Instance> instanceNew(const string& name, const string& type);
        void instanceDel(const string& name);
    private:
        ManagerImpl();
        ManagerImpl(const ManagerImpl &); 
        std::map<std::string,Ptr<Instance> > instance_;
        Network::Ptr network_;
        std::string name_;  
    };
}
#endif
