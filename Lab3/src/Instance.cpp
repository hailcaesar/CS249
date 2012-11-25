#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include "Instance.h"
#include "ManagerImpl.h"
#include "fwk/Exception.h"

/*
 * This is the entry point for your library.
 * The client program will call this function to get a handle
 * on the Instance::Manager object, and from there will use
 * that object to interact with the middle layer (which will
 * in turn interact with the engine layer).
 */
Ptr<Instance::Manager> shippingInstanceManager() {
    Ptr<Instance::Manager> manager = new Shipping::ManagerImpl("iManager");
    if (manager == NULL) {
	Fwk::MemoryException("Could not create new Instance manager!"); 
    }
    return manager; 
}
