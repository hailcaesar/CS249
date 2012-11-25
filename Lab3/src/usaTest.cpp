#include <assert.h>
#include <string>
#include <ostream>
#include <iostream>
#include <string>
#include "Instance.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using std::cout;
using std::cerr;
using std::endl;
using std::string;

void usaTest();

int main(int argc, char *argv[]) {
    usaTest(); 
    return 0;
}

void usaTest(){
    Ptr<Instance::Manager> manager = shippingInstanceManager();
    if (manager == NULL) {
        cerr << "Unexpected NULL manager." << endl;
        return;
    }

    Ptr<Instance> stats = manager->instanceNew("myStats", "Stats");
    if (stats == NULL) {
        cerr << "Unexpected NULL stats." << endl;
        return;
    }
    
    Ptr<Instance> conn = manager->instanceNew("myConn", "Conn");
    
    if (conn == NULL) {
        cerr << "Unexpected NULL conn." << endl;
        return;
    }

    Ptr<Instance> fleet = manager->instanceNew("myFleet", "Fleet");
    if (fleet == NULL) {
        cerr << "Unexpected NULL." << endl;
        return;
    }
    
    /* Set attributes */
    fleet->attributeIs("Plane, speed", "400.32145");
    fleet->attributeIs("Plane, cost", "100");
    fleet->attributeIs("Plane, capacity", "500");

    fleet->attributeIs("Boat, speed", "35.666");
    fleet->attributeIs("Boat, cost", "150.6832");
    fleet->attributeIs("Boat, capacity", "600");

    fleet->attributeIs("Truck, speed", "65.789");
    fleet->attributeIs("Truck, cost", "10.321");
    fleet->attributeIs("Truck, capacity", "60");
    
    /* Ports */
    Ptr<Instance> SFO = manager->instanceNew("SFO","Port");  
    Ptr<Instance> SEA = manager->instanceNew("SEA","Port"); 
    Ptr<Instance> NYC = manager->instanceNew("NYC","Port"); 
    
    /*Truck Terminals*/
    Ptr<Instance> DAL = manager->instanceNew("DAL","Truck terminal");

    /*Plane Terminals*/
    Ptr<Instance> MIA = manager->instanceNew("MIA","Plane terminal");

    /*Boat Terminals*/
    Ptr<Instance> HNL = manager->instanceNew("HNL","Boat terminal");
    
    if ( SFO == NULL || SEA == NULL || HNL == NULL || 
	 MIA == NULL || DAL == NULL || NYC == NULL ){
        cerr << "Unexpected NULL Location." << endl;
        return;
    }

    /* Truck Segments */
    Ptr<Instance> SFO_SEA = manager->instanceNew("SFO_SEA", "Truck segment");  
    Ptr<Instance> SEA_SFO = manager->instanceNew("SEA_SFO", "Truck segment");  
    Ptr<Instance> SFO_DAL = manager->instanceNew("SFO_DAL", "Truck segment");  
    Ptr<Instance> DAL_SFO = manager->instanceNew("DAL_SFO", "Truck segment");  
    Ptr<Instance> NYC_DAL = manager->instanceNew("NYC_DAL", "Truck segment");  
    Ptr<Instance> DAL_NYC = manager->instanceNew("DAL_NYC", "Truck segment");  
    Ptr<Instance> SEA_DAL = manager->instanceNew("SEA_DAL", "Truck segment");  
    Ptr<Instance> DAL_SEA = manager->instanceNew("DAL_SEA", "Truck segment");  
    
    if (SFO_SEA == NULL || SEA_SFO == NULL || SFO_DAL == NULL || DAL_SFO == NULL ||
    	NYC_DAL == NULL || DAL_NYC == NULL || SEA_DAL == NULL || DAL_SEA == NULL ){
        cerr << "Unexpected NULL Truck segment." << endl;
        return;
    }
   
    SFO_SEA->attributeIs("source","SFO"); 
    SEA_SFO->attributeIs("source","SEA");  
    SFO_DAL->attributeIs("source","SFO");  
    DAL_SFO->attributeIs("source","DAL");  
    NYC_DAL->attributeIs("source","NYC");  
    DAL_NYC->attributeIs("source","DAL");  
    SEA_DAL->attributeIs("source","SEA");  
    DAL_SEA->attributeIs("source","DAL");  

    SFO_SEA->attributeIs("return segment","SEA_SFO"); 
    SFO_DAL->attributeIs("return segment","DAL_SFO");  
    NYC_DAL->attributeIs("return segment","DAL_NYC");  
    SEA_DAL->attributeIs("return segment","DAL_SEA");  

    SFO_SEA->attributeIs("length","900.4567"); 
    SEA_SFO->attributeIs("length","900.4567");  
    SFO_DAL->attributeIs("length","700.4567");  
    DAL_SFO->attributeIs("length","700.4567");  
    NYC_DAL->attributeIs("length","1000.1234");  
    DAL_NYC->attributeIs("length","1000.1234");  
    SEA_DAL->attributeIs("length","1200.1234");  
    DAL_SEA->attributeIs("length","1200.1234");  

    NYC_DAL->attributeIs("difficulty","2.0543");  
    DAL_NYC->attributeIs("difficulty","2.0543");  
    SEA_DAL->attributeIs("difficulty","1.5543");  
    DAL_SEA->attributeIs("difficulty","1.5543");  

    NYC_DAL->attributeIs("expedite support","yes");  
    DAL_NYC->attributeIs("expedite support","yes");  
    SEA_DAL->attributeIs("expedite support","yes");  
    DAL_SEA->attributeIs("expedite support","yes");  

    /* Plane Segments */
    Ptr<Instance> SEA_NYC = manager->instanceNew("SEA_NYC", "Plane segment");  
    Ptr<Instance> NYC_SEA = manager->instanceNew("NYC_SEA", "Plane segment");  
    Ptr<Instance> SFO_MIA = manager->instanceNew("SFO_MIA", "Plane segment");  
    Ptr<Instance> MIA_SFO = manager->instanceNew("MIA_SFO", "Plane segment");  
    Ptr<Instance> MIA_NYC = manager->instanceNew("MIA_NYC", "Plane segment");  
    Ptr<Instance> NYC_MIA = manager->instanceNew("NYC_MIA", "Plane segment");  
    
    if ( SEA_NYC == NULL || NYC_SEA == NULL || SFO_MIA == NULL || MIA_SFO == NULL ||
    	 MIA_NYC == NULL || NYC_MIA == NULL ){
        cerr << "Unexpected NULL Plane segment." << endl;
        return;
    }
    
    SEA_NYC->attributeIs("source","SEA"); 
    NYC_SEA->attributeIs("source","NYC");  
    SFO_MIA->attributeIs("source","SFO");  
    MIA_SFO->attributeIs("source","MIA");  
    MIA_NYC->attributeIs("source","MIA");  
    NYC_MIA->attributeIs("source","NYC");  

    SEA_NYC->attributeIs("return segment","NYC_SEA"); 
    SFO_MIA->attributeIs("return segment","MIA_SFO");  
    MIA_NYC->attributeIs("return segment","NYC_MIA");  

    SEA_NYC->attributeIs("length","1300.5717"); 
    NYC_SEA->attributeIs("length","1300.5717");  
    SFO_MIA->attributeIs("length","1000.5717");  
    MIA_SFO->attributeIs("length","1000.5717");  
    MIA_NYC->attributeIs("length","1250.5717");  
    NYC_MIA->attributeIs("length","1250.5717");  

    /* Boat Segments */
    Ptr<Instance> HNL_SEA = manager->instanceNew("HNL_SEA", "Boat segment");  
    Ptr<Instance> SEA_HNL = manager->instanceNew("SEA_HNL", "Boat segment");  
    Ptr<Instance> SFO_HNL = manager->instanceNew("SFO_HNL", "Boat segment");  
    Ptr<Instance> HNL_SFO = manager->instanceNew("HNL_SFO", "Boat segment");  
    Ptr<Instance> HNL_NYC = manager->instanceNew("HNL_NYC", "Boat segment");  
    Ptr<Instance> NYC_HNL = manager->instanceNew("NYC_HNL", "Boat segment");  
    
    if ( HNL_SEA == NULL || SEA_HNL == NULL || SFO_HNL == NULL || HNL_SFO == NULL ||
    	 HNL_NYC == NULL || NYC_HNL == NULL ){
        cerr << "Unexpected NULL Boat segment." << endl;
        return;
    }

    HNL_SEA->attributeIs("source","HNL"); 
    SEA_HNL->attributeIs("source","SEA");
    SFO_HNL->attributeIs("source","SFO");
    HNL_SFO->attributeIs("source","HNL");
    HNL_NYC->attributeIs("source","HNL");
    NYC_HNL->attributeIs("source","NYC");
    
    HNL_SEA->attributeIs("return segment","SEA_HNL"); 
    SFO_HNL->attributeIs("return segment","HNL_SFO");
    HNL_NYC->attributeIs("return segment","NYC_HNL");
    
    HNL_SEA->attributeIs("length","1400.7635"); 
    SEA_HNL->attributeIs("length","1400.7635");
    SFO_HNL->attributeIs("length","800.1329");
    HNL_SFO->attributeIs("length","800.1329");
    HNL_NYC->attributeIs("length","3000.0732");
    NYC_HNL->attributeIs("length","3000.0732");
    
    SFO_HNL->attributeIs("difficulty","1.50717");
    HNL_SFO->attributeIs("difficulty","1.50717");
    HNL_NYC->attributeIs("difficulty","2.00717");
    NYC_HNL->attributeIs("difficulty","2.00717");

    HNL_NYC->attributeIs("expedite support","yes");
    NYC_HNL->attributeIs("expedite support","yes");

    Ptr<Instance> STAN = manager->instanceNew("STAN", "Customer");
    
    if ( STAN == NULL){
        cerr << "Unexpected NULL customer" << endl;
        return;
    }

    /* Truck Segment */
    Ptr<Instance> STAN_SFO = manager->instanceNew("STAN_SFO", "Truck segment");  
    Ptr<Instance> SFO_STAN = manager->instanceNew("SFO_STAN", "Truck segment");  
    
    if (SFO_STAN == NULL || STAN_SFO == NULL){
        cerr << "Unexpected NULL Truck segment." << endl;
        return;
    }
    
    STAN_SFO->attributeIs("source","STAN"); 
    SFO_STAN->attributeIs("source","SFO"); 
    
    STAN_SFO->attributeIs("return segment","SFO_STAN"); 

    STAN_SFO->attributeIs("length","70.3456"); 
    SFO_STAN->attributeIs("length","70.3456"); 

    cout << "Fleet characteristics of the system" << endl;
    cout << "--------------------" << endl;
    cout << "fleet->attribute('Boat, speed'): "	<< fleet->attribute("Boat, speed") << endl ;
    cout << "fleet->attribute('Boat, cost'): "	<< fleet->attribute("Boat, cost")<< endl;
    cout << "fleet->attribute('Boat, capacity'): " << fleet->attribute("Boat, capacity")<< endl;

    cout << "fleet->attribute('Truck, speed'): " << fleet->attribute("Truck, speed")<< endl;
    cout << "fleet->attribute('Truck, cost'): "	 << fleet->attribute("Truck, cost")<< endl;
    cout << "fleet->attribute('Truck, capacity'): " << fleet->attribute("Truck, capacity")<< endl;

    cout << "fleet->attribute('Plane, speed'): " << fleet->attribute("Plane, speed")<< endl;
    cout << "fleet->attribute('Plane, cost'): "	 << fleet->attribute("Plane, cost")<< endl;
    cout << "fleet->attribute('Plane, capacity'): " << fleet->attribute("Plane, capacity")<< endl;

    cout << "Stats of system" << endl;
    cout << "--------------------" << endl;
    cout << "Stats Attrs:" << endl;
    cout << "Truck segments = " << stats->attribute("Truck segment") << endl;
    cout << "Boat Segments = "	<< stats->attribute("Boat segment")<< endl;
    cout << "Plane segments = " << stats->attribute("Plane segment")<< endl;

    cout << "Truck terminals= " << stats->attribute("Truck terminal")<< endl;
    cout << "Boat terminals= "	<< stats->attribute("Boat terminal")<< endl;
    cout << "Plane terminals= " << stats->attribute("Plane terminal")<< endl;

    cout << "Ports= "	    << stats->attribute("Port")<< endl;
    cout << "Customers= "   << stats->attribute("Customer")<< endl ;
    cout << "expedite % = " << stats->attribute("expedite percentage") << endl;
   
        
    cout << "*** Connect STAN : NYC ****" << endl;
    cout << conn->attribute("connect STAN : MIA") << endl;
    cout << endl;
    
    cout << "**** explore SEA : distance 1350 ****" << endl;
    cout << conn->attribute("explore SEA : distance 1350") << endl;
    cout << endl;

}


