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
#include <boost/lexical_cast.hpp>
#include <set>

#define STRINGIFY(a) #a
#define STRING(a) STRINGIFY(a)

#define ASSERT(a) {\
    if (!(a)) {\
        throw std::string("Assertion failed: "__FILE__ ":" STRING(__LINE__) " " #a);\
    }\
}

#define EQUAL(a, b) {\
    if ((a) != (b)) {\
      throw std::string("Assertion failed: "__FILE__":" STRING(__LINE__) " " + a + " == " + b);\
    }\
} 

#define MAYBETHROW(a) {\
    try {\
        a;\
    } catch (...) {\
    }\
}
        
#define TEST(testfn, points) {\
    test(&(testfn), (points), #testfn);\
}

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::set; 

/* Tokenizes the multi-line input into a set of strings */
set<string> tokenize(const std::string& output) {
    set<string> tokens; 
    static const char *delim = "\n";
    size_t last = output.find_first_not_of(delim, 0);
    size_t pos = output.find_first_of(delim, last);
    
    /* Find all lines that are non-empty */
    while (string::npos != pos || string::npos != last) {
        string token = output.substr(last, pos - last);
        for (size_t i = 0; i < token.size(); i++) {
            if (!isspace(token[i])) {
                /* Only insert if non-empty */
                tokens.insert(output.substr(last, pos - last));
                break;
            }
        }

        last = output.find_first_not_of(delim, pos);
        pos = output.find_first_of(delim, last);
    }
    return tokens;
}

bool contains(const set<string>& s, const string& str) {
    return s.find(str) != s.end();
}


void repLayerConfigTest();
void simpleConnectionsTest();
void networkTest();
void invalidOperationsTest1(); /* Testing invalid ops on fleet, stats, locations. */
void invalidOperationsTest2(); /* testing on segment-location...linking unlinking etc*/
void invalidOperationsTest3(); /* testing on segment-return segment...linking unlinking etc*/
void segmentLocationTypeCompatibilityTest(); /* Testing the type compatibility between locations and segments */
void passThroughTest(); /* Check if the fleet set values actually pass through */
void finalTest();

void simpleConnectionsTest(){
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

    Ptr<Instance> fleet = manager->instanceNew("myFleet", "Fleet");
    if (fleet == NULL) {
        cerr << "Unexpected NULL." << endl;
        return;
    }
    
    /* Set attributes */
    fleet->attributeIs("Plane, speed"	, "40");
    fleet->attributeIs("Plane, cost"	, "40");
    fleet->attributeIs("Plane, capacity", "40");

    fleet->attributeIs("Boat, speed"	, "30");
    fleet->attributeIs("Boat, cost"	, "30");
    fleet->attributeIs("Boat, capacity", "30");

    fleet->attributeIs("Truck, speed"	, "60");
    fleet->attributeIs("Truck, cost"	, "60");
    fleet->attributeIs("Truck, capacity", "60");

    Ptr<Instance> c1  = manager->instanceNew("Chicago", "Port");  
    Ptr<Instance> c2 = manager->instanceNew("Detroit", "Port");
    Ptr<Instance> c3 = manager->instanceNew("NewYork", "Port");

    if (c1 == NULL || c2 == NULL || c3 == NULL) {
        cerr << "Unexpected NULL customer or port." << endl;
	return;
    }

    
    Ptr<Instance> ts1 = manager->instanceNew("Chicago-Detroit", "Truck segment");
    Ptr<Instance> ts2 = manager->instanceNew("Detroit-Chicago", "Truck segment");
    Ptr<Instance> ts3 = manager->instanceNew("Chicago-NewYork", "Truck segment");
    Ptr<Instance> ts4 = manager->instanceNew("NewYork-Chicago", "Truck segment");
    Ptr<Instance> ts5 = manager->instanceNew("Detroit-NewYork", "Truck segment");
    Ptr<Instance> ts6 = manager->instanceNew("NewYork-Detroit", "Truck segment");

    ts1->attributeIs("return segment", "Detroit-Chicago");
    ts3->attributeIs("return segment", "NewYork-Chicago");
    ts5->attributeIs("return segment", "NewYork-Detroit");

    ts1->attributeIs("length","400");
    ts2->attributeIs("length","400");
    ts3->attributeIs("length","400");
    ts4->attributeIs("length","400");
    ts5->attributeIs("length","400");
    ts6->attributeIs("length","400");

    ts1->attributeIs("expedite support", "no");
    ts2->attributeIs("expedite support", "no");
    ts3->attributeIs("expedite support", "yes");
    ts4->attributeIs("expedite support", "no");

    fleet->attributeIs("Truck, speed"	, "60");
    fleet->attributeIs("Truck, cost"	, "15");
    fleet->attributeIs("Truck, capacity", "20");


    if (ts1 == NULL || ts2 == NULL || ts3 == NULL || ts4 == NULL) {
        cerr << "Unexpected NULL segment." << endl;
        return;
    }
    ts1->attributeIs("source","Chicago");
    ts2->attributeIs("source","Detroit");
    ts3->attributeIs("source","Chicago");
    ts4->attributeIs("source","NewYork");
    ts5->attributeIs("source","Detroit");
    ts6->attributeIs("source","NewYork");




        // -- Connectivity queries
    Ptr<Instance> conn = manager->instanceNew("Connection1", "Conn");
    
    if (conn == NULL) {
        cerr << "Unexpected NULL conn." << endl;
        return;
    }
    
    cout << "*** Connect Chicago : NewYork ****" << endl;
    cout << conn->attribute("connect Chicago : NewYork") << endl;
    cout << endl;
    
    cout << "**** explore customer1 : distance 1500 ****" << endl;
    cout << conn->attribute("explore Chicago : distance 1500") << endl;
    cout << endl;
    
}

void networkTest(){
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

    Ptr<Instance> fleet = manager->instanceNew("myFleet", "Fleet");
    if (fleet == NULL) {
        cerr << "Unexpected NULL." << endl;
        return;
    }
    
    /* Set attributes */
    fleet->attributeIs("Truck, speed"	, "60");
    fleet->attributeIs("Truck, cost"	, "15");
    fleet->attributeIs("Truck, capacity", "20");

    Ptr<Instance> c1  = manager->instanceNew("c1", "Customer");  
    Ptr<Instance> tt1 = manager->instanceNew("tt1", "Truck terminal");  

    if (c1 == NULL || tt1 == NULL ) {
        cerr << "Unexpected NULL customer or port." << endl;
	return;
    }

    Ptr<Instance> ts1 = manager->instanceNew("ts1", "Truck segment");  
    Ptr<Instance> ts2 = manager->instanceNew("ts2", "Truck segment");  

    if (ts1 == NULL || ts2 == NULL ) {
        cerr << "Unexpected NULL segment." << endl;
        return;
    }
    ts1->attributeIs("source","c1");
    ts2->attributeIs("source","tt1");
    
    ts1->attributeIs("return segment","ts2");
    
    ts1->attributeIs("length","400");
    ts2->attributeIs("length","420");
    
    ts1->attributeIs("difficulty","1.4");
    ts2->attributeIs("difficulty","1.2");
   
    ts1->attributeIs("expedite support","yes");

    cout << "Stats of system" << endl;
    cout << "--------------------" << endl;
    cout << "Stats Attrs:" << endl;
    cout << "Truck segments = " <<stats->attribute("Truck segment") << endl;
    cout << "Boat Segments = "	<<stats->attribute("Boat segment")<< endl;
    cout << "Plane segments = " <<stats->attribute("Plane segment")<< endl;

    cout << "Truck terminals= " <<stats->attribute("Truck terminal")<< endl;
    cout << "Boat terminals= "	<<stats->attribute("Boat terminal")<< endl;
    cout << "Plane terminals= " <<stats->attribute("Plane terminal")<< endl;
    cout << "Ports= "	    <<stats->attribute("Port")<< endl;
    cout << "Customers= "   <<stats->attribute("Customer")<< endl ;

    cout << "expedite % = " << stats->attribute("expedite percentage") << endl;
    
    cout << "--------------------" << endl;
    cout << "Checking attributes to see if connections were made" << endl;
    cout << "--------------------" << endl << endl;

    cout << "ts1 source = " << ts1->attribute("source") << endl;
    cout << "ts1 retseg = " << ts1->attribute("return segment") << endl;

    cout << "ts2 source = " << ts2->attribute("source") << endl;
    cout << "ts2 retseg = " << ts2->attribute("return segment") << endl;
    
    cout << "c1 segment1 = " << c1->attribute("segment1") << endl;
    cout << "tt1 segment1 = " << tt1->attribute("segment1") << endl;
    cout << "\nDone...." << endl << endl;

    /* removing a segment and adding another one to replace it*/

    Ptr<Instance> ts3 = manager->instanceNew("ts3", "Truck segment");  
    Ptr<Instance> bs1 = manager->instanceNew("bs1", "Boat segment");  

    if (ts3 == NULL || bs1 == NULL ) {
        cerr << "Unexpected NULL segment." << endl;
        return;
    }
    ts1->attributeIs("source","");
    ts1->attributeIs("return segment","");
    
    ts3->attributeIs("length","700");
    ts3->attributeIs("difficulty","1.4");
    ts3->attributeIs("source","c1");
    ts3->attributeIs("return segment","ts2");
   
    bs1->attributeIs("expedite support","yes");
    bs1->attributeIs("return segment", "ts1");

    cout << "New output" << endl;
    
    cout << "Stats of system" << endl;
    cout << "--------------------" << endl;
    cout << "Stats Attrs:" << endl;
    cout << "Truck segments = " <<stats->attribute("Truck segment") << endl;
    cout << "Boat Segments = "	<<stats->attribute("Boat segment")<< endl;
    cout << "Plane segments = " <<stats->attribute("Plane segment")<< endl;

    cout << "Truck terminals= " <<stats->attribute("Truck terminal")<< endl;
    cout << "Boat terminals= "	<<stats->attribute("Boat terminal")<< endl;
    cout << "Plane terminals= " <<stats->attribute("Plane terminal")<< endl;
    cout << "Ports= "	    <<stats->attribute("Port")<< endl;
    cout << "Customers= "   <<stats->attribute("Customer")<< endl ;

    cout << "expedite % = " << stats->attribute("expedite percentage") << endl;
    
    cout << "--------------------" << endl;
    cout << "Checking attributes to see if connections were made" << endl;
    cout << "--------------------" << endl << endl;

    cout << "ts1 source = " << bs1->attribute("source") << endl;
    cout << "ts1 retseg = " << bs1->attribute("return segment") << endl;

    cout << "bs1 source = " << bs1->attribute("source") << endl;
    cout << "bs1 retseg = " << bs1->attribute("return segment") << endl;

    cout << "ts2 source = " << ts2->attribute("source") << endl;
    cout << "ts2 retseg = " << ts2->attribute("return segment") << endl;
    
    cout << "ts3 source = " << ts3->attribute("source") << endl;
    cout << "ts3 retseg = " << ts3->attribute("return segment") << endl;
    
    cout << "c1 segment1 = " << c1->attribute("segment1") << endl;
    cout << "tt1 segment1 = " << tt1->attribute("segment1") << endl;
    cout << "\nDone...." << endl << endl;
}

void repLayerConfigTest(){
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

    Ptr<Instance> fleet = manager->instanceNew("myFleet", "Fleet");

    if (fleet == NULL) {
        cerr << "Unexpected NULL." << endl;
        return;
    }
    
    /* Set attributes */
    fleet->attributeIs("Boat, speed"	, "10");
    fleet->attributeIs("Boat, cost"	, "20");
    fleet->attributeIs("Boat, capacity"	, "30");

    fleet->attributeIs("Truck, speed"	, "11");
    fleet->attributeIs("Truck, cost"	, "21");
    fleet->attributeIs("Truck, capacity", "31");

    fleet->attributeIs("Plane, speed"	, "15");
    fleet->attributeIs("Plane, cost"	, "25");
    fleet->attributeIs("Plane, capacity", "35");

    Ptr<Instance> fleet2 = manager->instanceNew("sameFleet", "Fleet");
    /*This fleet should alias to the same default fleet*/
    if (fleet2 == NULL) {
        cerr << "Unexpected NULL." << endl;
        return;
    }
    
    /* Check attribute values */
    cout << "fleet->attribute('Boat, speed'): "	    << fleet->attribute("Boat, speed") << endl ;
    cout << "fleet->attribute('Boat, cost'): "	    << fleet->attribute("Boat, cost")<< endl;
    cout << "fleet->attribute('Boat, capacity'): "  << fleet->attribute("Boat, capacity")<< endl;

    cout << "fleet->attribute('Truck, speed'): "    << fleet->attribute("Truck, speed")<< endl;
    cout << "fleet->attribute('Truck, cost'): "	    << fleet->attribute("Truck, cost")<< endl;
    cout << "fleet->attribute('Truck, capacity'): " << fleet->attribute("Truck, capacity")<< endl;

    cout << "fleet->attribute('Plane, speed'): "    << fleet->attribute("Plane, speed")<< endl;
    cout << "fleet->attribute('Plane, cost'): "	    << fleet->attribute("Plane, cost")<< endl;
    cout << "fleet->attribute('Plane, capacity'): " << fleet->attribute("Plane, capacity")<< endl;

    assert(fleet->attribute("Boat, speed")	==  fleet2->attribute("Boat, speed"));	
    assert(fleet->attribute("Boat, cost")	==  fleet2->attribute("Boat, cost"));	
    assert(fleet->attribute("Boat, capacity")	==  fleet2->attribute("Boat, capacity"));	
    assert(fleet->attribute("Truck, speed")	==  fleet2->attribute("Truck, speed"));
    assert(fleet->attribute("Truck, cost")	==  fleet2->attribute("Truck, cost"));	
    assert(fleet->attribute("Truck, capacity")	==  fleet2->attribute("Truck, capacity"));	
    assert(fleet->attribute("Plane, speed")	==  fleet2->attribute("Plane, speed"));
    assert(fleet->attribute("Plane, cost")	==  fleet2->attribute("Plane, cost"));	
    assert(fleet->attribute("Plane, capacity")	==  fleet2->attribute("Plane, capacity"));	


    Ptr<Instance> customer1 = manager->instanceNew("customer1", "Customer");  
    Ptr<Instance> customer2 = manager->instanceNew("customer2", "Customer");  
    Ptr<Instance> port1 = manager->instanceNew("port1", "Port");  
    Ptr<Instance> truckTerminal1 = manager->instanceNew("tt1", "Truck terminal");  
    Ptr<Instance> boatTerminal1 = manager->instanceNew("bt1", "Boat terminal");  
    Ptr<Instance> boatTerminal2 = manager->instanceNew("bt2", "Plane terminal");  
    Ptr<Instance> planeTerminal1 = manager->instanceNew("pt1", "Plane terminal");  

    if (customer1 == NULL || customer2 == NULL || port1 == NULL || truckTerminal1 == NULL || boatTerminal1 == NULL || boatTerminal2 == NULL || planeTerminal1 == NULL) {
        cerr << "Unexpected NULL while creating a location." << endl;
	return;
    }

    Ptr<Instance> boatSeg1 = manager->instanceNew( "boatSeg1", "Boat segment");  
    Ptr<Instance> boatSeg2 = manager->instanceNew( "boatSeg2", "Boat segment");  
    Ptr<Instance> truckSeg1 = manager->instanceNew("truckSeg1", "Truck segment");  
    Ptr<Instance> truckSeg2 = manager->instanceNew("truckSeg2", "Truck segment");  
    Ptr<Instance> planeSeg1 = manager->instanceNew("planeSeg1", "Plane segment");  
    Ptr<Instance> planeSeg2 = manager->instanceNew("planeSeg2", "Plane segment");  
    Ptr<Instance> planeSeg3 = manager->instanceNew("planeSeg3", "Plane segment");  

    if (boatSeg1 == NULL || boatSeg2 == NULL || truckSeg1 == NULL || truckSeg2 == NULL || planeSeg1 == NULL ||  planeSeg2 == NULL || planeSeg3 == NULL) {
        cerr << "Unexpected NULL segment." << endl;
        return;
    }

    // -- Segment lengths
    boatSeg1->attributeIs("length", "400");
    boatSeg2->attributeIs("length", "450");
    truckSeg1->attributeIs("length", "900");
    truckSeg2->attributeIs("length", "950");
    planeSeg1->attributeIs("length", "650");
    planeSeg2->attributeIs("length", "725");
    planeSeg3->attributeIs("length", "811");

    /*Segment length attribute values, check with program*/
    cout << "Check for segment length values =>" << endl;
    cout << "boatSeg1  : Set as : 400" << "Got value: " << boatSeg1->attribute("length" ) << endl;
    cout << "boatSeg2  : Set as : 450" << "Got value: " << boatSeg2->attribute("length" ) << endl;
    cout << "truckSeg1 : Set as : 900" << "Got value: " << truckSeg1->attribute("length") << endl;
    cout << "truckSeg2 : Set as : 950" << "Got value: " << truckSeg2->attribute("length") << endl;
    cout << "planeSeg1 : Set as : 650" << "Got value: " << planeSeg1->attribute("length") << endl;
    cout << "planeSeg2 : Set as : 725" << "Got value: " << planeSeg2->attribute("length") << endl;
    cout << "planeSeg3 : Set as : 811" << "Got value: " << planeSeg3->attribute("length") << endl;

    // -- Segment difficulties
    boatSeg1->attributeIs("difficulty", "1.4");
    boatSeg2->attributeIs("difficulty", "1.8");
    truckSeg1->attributeIs("difficulty", "2.0");
    truckSeg2->attributeIs("difficulty", "3.0");
    planeSeg1->attributeIs("difficulty", "1.0");
    planeSeg2->attributeIs("difficulty", "1.1");
    planeSeg3->attributeIs("difficulty", "1.2");
    
    cout << "Check for segment difficulty values =>" << endl;
    cout << "boatSeg1  : Set as : 1.4" << "Got value: " << boatSeg1->attribute( "difficulty") << endl;
    cout << "boatSeg2  : Set as : 1.8" << "Got value: " << boatSeg2->attribute( "difficulty") << endl;
    cout << "truckSeg1 : Set as : 2.0" << "Got value: " << truckSeg1->attribute("difficulty") << endl;
    cout << "truckSeg2 : Set as : 3.0" << "Got value: " << truckSeg2->attribute("difficulty") << endl;
    cout << "planeSeg1 : Set as : 1.0" << "Got value: " << planeSeg1->attribute("difficulty") << endl;
    cout << "planeSeg2 : Set as : 1.1" << "Got value: " << planeSeg2->attribute("difficulty") << endl;
    cout << "planeSeg3 : Set as : 1.2" << "Got value: " << planeSeg3->attribute("difficulty") << endl;

    // -- Segment expedite support
    boatSeg1->attributeIs("expedite support", "yes");
    boatSeg2->attributeIs("expedite support", "no");
    truckSeg1->attributeIs("expedite support", "no");
    truckSeg2->attributeIs("expedite support", "yes");
    planeSeg1->attributeIs("expedite support", "yes");
    //planeSeg2->attributeIs("expedite support", "yes"); //should be no by default
    planeSeg3->attributeIs("expedite support", "yes");

    cout << "Check for expedite support values =>" << endl;
    cout << "boatSeg1  : Set as : yes" << "Got value: " << boatSeg1->attribute( "expedite support") << endl;
    cout << "boatSeg2  : Set as :  no" << "Got value: " << boatSeg2->attribute( "expedite support") << endl;
    cout << "truckSeg1 : Set as :  no" << "Got value: " << truckSeg1->attribute("expedite support") << endl;
    cout << "truckSeg2 : Set as : yes" << "Got value: " << truckSeg2->attribute("expedite support") << endl;
    cout << "planeSeg1 : Set as : yes" << "Got value: " << planeSeg1->attribute("expedite support") << endl;
    cout << "planeSeg2 : Set as : no" << "Got value: " << planeSeg2->attribute("expedite support") << endl;
    cout << "planeSeg3 : Set as : yes" << "Got value: " << planeSeg3->attribute("expedite support") << endl;

    cout << "Stats Attrs:" << endl;
    cout << "Truck segments = " <<stats->attribute("Truck segment") << endl;
    cout << "Boat Segments = " <<stats->attribute("Boat segment")<< endl;
    cout << "Plane segments = " <<stats->attribute("Plane segment")<< endl;

    cout << "Truck terminals= " <<stats->attribute("Truck terminal")<< endl;
    cout << "Boat terminals= " <<stats->attribute("Boat terminal")<< endl;
    cout << "Plane terminals= " <<stats->attribute("Plane terminal")<< endl;
    cout << "Ports= " <<stats->attribute("Port")<< endl;
    cout << "Customers= " <<stats->attribute("Customer")<< endl ;

    cout << "expedite % = " << stats->attribute("expedite percentage") << endl;

}

void invalidOperationsTest1(){
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

    Ptr<Instance> fleet = manager->instanceNew("myFleet", "Fleet");
    if (fleet == NULL) {
        cerr << "Unexpected NULL." << endl;
        return;
    }
    
    /* Set attributes */
    fleet->attributeIs("Truck, speed"	, "60");
    fleet->attributeIs("Truck, cost"	, "15");
    fleet->attributeIs("Truck, capacity", "20");
    
    cout  << "-----------------------------" << endl;
    cout  << "Fleet invalid attributes test" << endl;
    cout  << "-----------------------------" << endl;

    cout << "Testing no type for fleet attribute" << endl;
    cout << "\tFleet attribute speed = " << fleet->attribute("speed") << endl << endl;

    cout << "Testing invalid attribute name for fleet" << endl;
    cout << "\tFleet attribute Truck, spied = " << fleet->attribute("Truck, spied") << endl << endl;
    
    cout << "Testing VALID attribute name for fleet" << endl;
    cout << "\tFleet attribute Truck, capacity = " << fleet->attribute("Truck, capacity") << endl << endl;
    
    cout << "Testing undeclared attribute for fleet..should return default value" << endl;
    cout << "\tFleet attribute Boat, cost = " << fleet->attribute("Boat, cost") << endl << endl;
   
    fleet->attributeIs("Truck, INVALIDTYPE", "20");
  
    cout << endl ;

    cout  << "-----------------------------" << endl;
    cout  << "Stats invalid attributes test" << endl;
    cout  << "-----------------------------" << endl;

    cout << "Testing with invalid stats attribute name" << endl;
    cout << "\tStats attribute INVALID = " << stats->attribute("INVALID") << endl << endl;

    cout  << "-----------------------------" << endl;
    cout  << "Customer invalid attributes test" << endl;
    cout  << "-----------------------------" << endl;

    Ptr<Instance> c1  = manager->instanceNew("c1", "Customer");  
    if(c1 == NULL){
        cerr << "Unexpected NULL Customer." << endl;
        return;
    }
    Ptr<Instance> ps1  = manager->instanceNew("ps1", "Plane segment");  
    if(ps1 == NULL){
        cerr << "Unexpected NULL Plane segment." << endl;
        return;
    }
    cout << "Testing a customer invalid segment number attribute" << endl;
    cout << "\tc1 attribute= segment12; result = " << c1->attribute("segment12") << endl << endl;
    
    ps1->attributeIs("source", "c1");
    cout << "Testing a customer VALID segment number attribute" << endl;
    cout << "\tc1 attribute= segment1; result = " << c1->attribute("segment1") << endl << endl;

    cout << "Deleting the segment and checking for the segment number again" << endl;
    manager->instanceDel("ps1");
    cout << "\tc1 attribute= segment1; result = " << c1->attribute("segment1") << endl << endl;

    cout << endl;
    cout << "Creating a new fleet f2" << endl;
    Ptr<Instance> f2 = manager->instanceNew("f2", "Fleet");
    if (f2 == NULL) {
        cerr << "Unexpected NULL." << endl;
        return;
    }
    cout << "Deleting myFleet" << endl;
    manager->instanceDel("myFleet"); 
    cout << "Looking for attribute in f2 " << f2->attribute("Truck, cost") << endl;

    cout  << "-----------------------------" << endl;
    cout  << "Port invalid attributes test" << endl;
    cout  << "-----------------------------" << endl;

    Ptr<Instance> p1  = manager->instanceNew("p1", "Port");  
    if(p1 == NULL){
        cerr << "Unexpected NULL Port." << endl;
        return;
    }
    Ptr<Instance> bseg  = manager->instanceNew("bseg", "Boat segment");  
    Ptr<Instance> bseg2  = manager->instanceNew("bseg2", "Boat segment");  
    if(bseg == NULL || bseg2 == NULL){
        cerr << "Unexpected NULL Boat segment." << endl;
        return;
    }
    cout << "Testing a port invalid segment number attribute" << endl;
    cout << "\tp1 attribute= segment12; result = " << p1->attribute("segment12") << endl << endl;
    
    bseg->attributeIs("source", "p1");
    bseg2->attributeIs("source", "p1");

    cout << "Testing a port VALID segment number attribute" << endl;
    cout << "\tp1 attribute= segment1; result = " << p1->attribute("segment1") << endl << endl;
    cout << "\tp1 attribute= segment2; result = " << p1->attribute("segment2") << endl << endl;

    cout << "Deleting the segment and checking for the segment number again" << endl;
    manager->instanceDel("bseg");
    cout << "\tp1 attribute= segment1; result = " << p1->attribute("segment1") << endl << endl;
    cout << "\tp1 attribute= segment2; result = " << p1->attribute("segment2") << endl << endl;
    
}

void invalidOperationsTest2(){
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

    Ptr<Instance> fleet = manager->instanceNew("myFleet", "Fleet");
    if (fleet == NULL) {
        cerr << "Unexpected NULL." << endl;
        return;
    }
    
    /* Set attributes */
    fleet->attributeIs("Truck, speed"	, "60");
    fleet->attributeIs("Truck, cost"	, "15");
    fleet->attributeIs("Truck, capacity", "20");
    
    cout  << "-----------------------------" << endl;
    cout  << "Port invalid attributes test" << endl;
    cout  << "-----------------------------" << endl;

    Ptr<Instance> p1  = manager->instanceNew("p1", "Port");  
    Ptr<Instance> p2  = manager->instanceNew("p2", "Port");  
    if(p1 == NULL || p2 == NULL){
        cerr << "Unexpected NULL Port." << endl;
        return;
    }
    Ptr<Instance> bseg  = manager->instanceNew("bseg", "Boat segment");  
    Ptr<Instance> bseg2  = manager->instanceNew("bseg2", "Boat segment");  
    if(bseg == NULL || bseg2 == NULL){
        cerr << "Unexpected NULL Boat segment." << endl;
        return;
    }
    cout << "Testing a port invalid segment number attribute" << endl;
    cout << "\tp1 attribute= segment12; result = " << p1->attribute("segment12") << endl << endl;
    
    bseg->attributeIs("source", "p1");
    bseg2->attributeIs("source", "p1");
    
    cout << "Deleting bseg" << endl;
    manager->instanceDel("bseg");
    cout << "Deleting bseg AGAIN" << endl;
    manager->instanceDel("bseg");

    cout << "TEST: p1 segment1 = " << p1->attribute("segment1") << endl; 
    cout << "TEST: p1 segment2 = " << p1->attribute("segment2") << endl; 
    
    cout << "Trying to set the source of bseg2 to something invalid" << endl;
    bseg2->attributeIs("source", "p34");
    cout << endl;
    
    cout << "Trying to set the source of bseg to something valid when it is already something valid" << endl;
    bseg2->attributeIs("source", "p2");
    cout << endl;

    cout << "bseg2 source (should be p2) = " << bseg2->attribute("source") << endl;
    cout << endl;
    
    cout << "p1 segment 1 (should be NULL)= " << p1->attribute("segment1") << endl;
    cout << "p1 segment 2 (should be NULL)= " << p1->attribute("segment2") << endl;
    cout << "p2 segment 1 (should be bseg2)= " << p2->attribute("segment1") << endl;
    
    cout << endl;
    cout << "unlinking bseg2 and p2" << endl;
    bseg2->attributeIs("source","");
    cout << "linking bseg2 and p1" << endl;
    bseg2->attributeIs("source","p1");
    cout << endl;

    cout << "bseg2 source (should be p1)= " << bseg2->attribute("source") << endl;
    cout << endl;
    
    cout << "p1 segment 1 (should be bseg2)= " << p1->attribute("segment1")<< endl;
    cout << "p1 segment 2 (should be NULL)= " << p1->attribute("segment2")<< endl;
    cout << "p2 segment 1 (should be bseg1)= " << p2->attribute("segment1")<< endl;
}

void invalidOperationsTest3(){
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

    Ptr<Instance> fleet = manager->instanceNew("myFleet", "Fleet");
    if (fleet == NULL) {
        cerr << "Unexpected NULL." << endl;
        return;
    }
    
    /* Set attributes */
    fleet->attributeIs("Truck, speed"	, "60");
    fleet->attributeIs("Truck, cost"	, "15");
    fleet->attributeIs("Truck, capacity", "20");
    
    cout  << "-----------------------------" << endl;
    cout  << "Port invalid attributes test" << endl;
    cout  << "-----------------------------" << endl;

    Ptr<Instance> p1  = manager->instanceNew("p1", "Port");  
    Ptr<Instance> p2  = manager->instanceNew("p2", "Port");  
    if(p1 == NULL || p2 == NULL){
        cerr << "Unexpected NULL Port." << endl;
        return;
    }
    Ptr<Instance> bseg  = manager->instanceNew("bseg", "Boat segment");  
    Ptr<Instance> bseg2  = manager->instanceNew("bseg2", "Boat segment");  
    Ptr<Instance> bseg3  = manager->instanceNew("bseg3", "Boat segment");  
    if(bseg == NULL || bseg2 == NULL || bseg3 == NULL){
        cerr << "Unexpected NULL Boat segment." << endl;
        return;
    }
    cout << "Testing a port invalid segment number attribute" << endl;
    cout << "\tp1 attribute= segment12; result = " << p1->attribute("segment12") << endl << endl;
    
    bseg->attributeIs("return segment", "bseg2");
    cout << " bseg ret seg (should be bseg 2) = " << bseg->attribute("return segment") << endl;
    cout << " bseg2 ret seg (should be bseg) = " << bseg2->attribute("return segment") << endl;
    cout << " bseg3 ret seg (should be NULL) = " << bseg3->attribute("return segment") << endl;
   
    cout << endl;
    cout << "Trying to set the return segment of bseg to something invalid" << endl;
    bseg2->attributeIs("return segment", "seg34");
    cout << endl;
    
    cout << endl;
    cout << "Trying to set the source of bseg to something valid (bseg3) when it is already something valid" << endl;
    bseg2->attributeIs("return segment", "bseg3");
    cout << endl;

    bseg->attributeIs("return segment", "bseg2");
    cout << "bseg ret seg (should be bseg 2) = " << bseg->attribute("return segment") << endl;
    cout << "bseg2 ret seg (should be bseg) = " << bseg2->attribute("return segment") << endl;
    cout << "bseg3 ret seg (should be NULL) = " << bseg3->attribute("return segment") << endl;
    cout << endl;

    cout << "unlinking bseg and bseg2 " << endl;
    bseg->attributeIs("return segment", "");
    cout << "bseg ret seg (should be NULL) = " << bseg->attribute("return segment") << endl;
    cout << "bseg2 ret seg (should be NULL) = " << bseg2->attribute("return segment") << endl;
    cout << "bseg3 ret seg (should be NULL) = " << bseg3->attribute("return segment") << endl;
    cout << endl;
    
    cout << "linking bseg2 and bseg3 " << endl;
    bseg2->attributeIs("return segment", "bseg3");
    cout << "bseg ret seg (should be NULL) = " << bseg->attribute("return segment") << endl;
    cout << "bseg2 ret seg (should be bseg3) = " << bseg2->attribute("return segment") << endl;
    cout << "bseg3 ret seg (should be bseg2) = " << bseg3->attribute("return segment") << endl;
    cout << endl;
}

void segmentLocationTypeCompatibilityTest(){
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

    Ptr<Instance> fleet = manager->instanceNew("myFleet", "Fleet");
    if (fleet == NULL) {
        cerr << "Unexpected NULL." << endl;
        return;
    }
    
    /* Set attributes */
    fleet->attributeIs("Truck, speed"	, "60");
    fleet->attributeIs("Truck, cost"	, "15");
    fleet->attributeIs("Truck, capacity", "20");
    
    Ptr<Instance> tt  = manager->instanceNew("tt", "Truck terminal");  
    Ptr<Instance> bt  = manager->instanceNew("bt", "Boat terminal");  
    Ptr<Instance> pt  = manager->instanceNew("pt", "Plane terminal");  
    if(tt == NULL || bt == NULL || pt == NULL){
        cerr << "Unexpected NULL Location." << endl;
        return;
    }
    Ptr<Instance> ts  = manager->instanceNew("ts", "Truck segment");  
    Ptr<Instance> bs  = manager->instanceNew("bs", "Boat segment");  
    Ptr<Instance> ps  = manager->instanceNew("ps", "Plane segment");  
    if(bs == NULL || ts == NULL || ps == NULL){
        cerr << "Unexpected NULL segment." << endl;
        return;
    }
    
    cout << "Setting bs;ts;ps source to incompatible Locations (tt,pt);(bt,pt),(tt,bt)" << endl;
    bs->attributeIs("source", "tt");
    bs->attributeIs("source", "pt");
    ts->attributeIs("source", "bt");
    ts->attributeIs("source", "pt");
    ps->attributeIs("source", "tt");
    ps->attributeIs("source", "bt");

}

void passThroughTest(){
    Ptr<Instance::Manager> manager = shippingInstanceManager();
    Ptr<Instance> fleet = manager->instanceNew("myFleet", "Fleet");
    
    /* Set attributes */
    fleet->attributeIs("Truck, speed"	, "1");
    fleet->attributeIs("Truck, cost"	, "2");
    fleet->attributeIs("Truck, capacity", "3");
    
    fleet->attributeIs("Boat, speed"	, "4");
    fleet->attributeIs("Boat, cost"	, "5");
    fleet->attributeIs("Boat, capacity", "6");

    fleet->attributeIs("Plane, speed"	, "7");
    fleet->attributeIs("Plane, cost"	, "8");
    fleet->attributeIs("Plane, capacity", "9");

    cout << "Truck speed" << fleet->attribute("Truck, speed")   << endl;
    cout << "Truck cost" << fleet->attribute("Truck, cost")    << endl;
    cout << "Truck capacity" << fleet->attribute("Truck, capacity")<< endl;
    cout << "Boat  speed" << fleet->attribute("Boat, speed")    << endl;
    cout << "Boat  cost" << fleet->attribute("Boat, cost")	    << endl;
    cout << "Boat  capacity" << fleet->attribute("Boat, capacity") << endl;
    cout << "Plane speed" << fleet->attribute("Plane, speed")   << endl;
    cout << "Plane cost" << fleet->attribute("Plane, cost")    << endl;
    cout << "Plane capacity" << fleet->attribute("Plane, capacity")<< endl;
     

}

void finalTest(){
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
    fleet->attributeIs("Plane, speed", "400");
    fleet->attributeIs("Plane, cost", "100");
    fleet->attributeIs("Plane, capacity", "500");

    fleet->attributeIs("Boat, speed", "35");
    fleet->attributeIs("Boat, cost", "150");
    fleet->attributeIs("Boat, capacity", "600");

    fleet->attributeIs("Truck, speed", "65");
    fleet->attributeIs("Truck, cost", "10");
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

    SFO_SEA->attributeIs("length","900"); 
    SEA_SFO->attributeIs("length","900");  
    SFO_DAL->attributeIs("length","700");  
    DAL_SFO->attributeIs("length","700");  
    NYC_DAL->attributeIs("length","1000");  
    DAL_NYC->attributeIs("length","1000");  
    SEA_DAL->attributeIs("length","1200");  
    DAL_SEA->attributeIs("length","1200");  

    NYC_DAL->attributeIs("difficulty","2.0");  
    DAL_NYC->attributeIs("difficulty","2.0");  
    SEA_DAL->attributeIs("difficulty","1.5");  
    DAL_SEA->attributeIs("difficulty","1.5");  

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

    SEA_NYC->attributeIs("length","1300"); 
    NYC_SEA->attributeIs("length","1300");  
    SFO_MIA->attributeIs("length","1000");  
    MIA_SFO->attributeIs("length","1000");  
    MIA_NYC->attributeIs("length","1250");  
    NYC_MIA->attributeIs("length","1250");  

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
    
    HNL_SEA->attributeIs("length","1400"); 
    SEA_HNL->attributeIs("length","1400");
    SFO_HNL->attributeIs("length","800");
    HNL_SFO->attributeIs("length","800");
    HNL_NYC->attributeIs("length","3000");
    NYC_HNL->attributeIs("length","3000");
    
    SFO_HNL->attributeIs("difficulty","1.5");
    HNL_SFO->attributeIs("difficulty","1.5");
    HNL_NYC->attributeIs("difficulty","2.0");
    NYC_HNL->attributeIs("difficulty","2.0");

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

    STAN_SFO->attributeIs("length","70"); 
    SFO_STAN->attributeIs("length","70"); 

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

void ofcTest1() {
    Ptr<Instance::Manager> m = shippingInstanceManager();
    Ptr<Instance> fleet = m->instanceNew("fleet", "Fleet");
    if(!fleet) fleet = m->instance("fleet");

    /* Branching star-like shape */
    m->instanceNew("a", "Port");
    m->instanceNew("b", "Boat terminal");
    m->instanceNew("c", "Plane terminal");
    m->instanceNew("d", "Truck terminal");
    m->instanceNew("e", "Customer");

    Ptr<Instance> s;

    s = m->instanceNew("1", "Boat segment");
    s->attributeIs("source", "a");
    s->attributeIs("length", "10");
    s->attributeIs("difficulty", "1");
    s->attributeIs("expedite support", "no");
    s = m->instanceNew("1r", "Boat segment");
    s->attributeIs("source", "b");
    s->attributeIs("length", "10");
    s->attributeIs("difficulty", "1");
    s->attributeIs("expedite support", "no");
    s->attributeIs("return segment", "1");

    s = m->instanceNew("2", "Plane segment");
    s->attributeIs("source", "a");
    s->attributeIs("length", "10");
    s->attributeIs("difficulty", "1");
    s->attributeIs("expedite support", "no");
    s = m->instanceNew("2r", "Plane segment");
    s->attributeIs("source", "c");
    s->attributeIs("length", "10");
    s->attributeIs("difficulty", "1");
    s->attributeIs("expedite support", "no");
    s->attributeIs("return segment", "2");

    s = m->instanceNew("3", "Truck segment");
    s->attributeIs("source", "a");
    s->attributeIs("length", "10");
    s->attributeIs("difficulty", "1");
    s->attributeIs("expedite support", "no");
    s = m->instanceNew("3r", "Truck segment");
    s->attributeIs("source", "d");
    s->attributeIs("length", "10");
    s->attributeIs("difficulty", "1");
    s->attributeIs("expedite support", "no");
    s->attributeIs("return segment", "3");

    s = m->instanceNew("4", "Truck segment");
    s->attributeIs("source", "d");
    s->attributeIs("length", "10");
    s->attributeIs("difficulty", "1");
    s->attributeIs("expedite support", "no");
    s = m->instanceNew("4r", "Truck segment");
    s->attributeIs("source", "e");
    s->attributeIs("length", "10");
    s->attributeIs("difficulty", "1");
    s->attributeIs("expedite support", "no");
    s->attributeIs("return segment", "4");


    fleet->attributeIs("Truck, speed", "1");
    fleet->attributeIs("Truck, capacity", "1");
    fleet->attributeIs("Truck, cost", "1");
    fleet->attributeIs("Boat, speed", "2");
    fleet->attributeIs("Boat, capacity", "2");
    fleet->attributeIs("Boat, cost", "2");
    fleet->attributeIs("Plane, speed", "3");
    fleet->attributeIs("Plane, capacity", "3");
    fleet->attributeIs("Plane, cost", "3");

    Ptr<Instance> conn = m->instanceNew("conn", "Conn");
    if(!conn) conn = m->instance("conn");
    set<string> t;

    cout << "*******DEBUG 1 : connect a : d = ***********" << endl;
    cout << conn->attribute("connect a : d"); 
    t = tokenize(conn->attribute("connect a : d"));
    ASSERT(contains(t, "10.00 10.00 no; a(3:10.00:3r) d"));
    ASSERT(t.size() == 1);
    cout << "**************End DEBUG 1 ******************" << endl;

    cout << "*******DEBUG 2 : connect c : e = ***********" << endl;
    cout << conn->attribute("connect c : e"); 
    t = tokenize(conn->attribute("connect c : e"));
    ASSERT(contains(t, "50.00 23.33 no; c(2r:10.00:2) a(3:10.00:3r) d(4:10.00:4r) e"));
    ASSERT(t.size() == 1);
    cout << "**************End DEBUG 2 ******************" << endl;

    cout << "*******DEBUG 3 : connect e : b = ***********" << endl;
    cout << conn->attribute("connect e : b"); 
    t = tokenize(conn->attribute("connect e : b"));
    ASSERT(contains(t, "40.00 25.00 no; e(4r:10.00:4) d(3r:10.00:3) a(1:10.00:1r) b"));
    ASSERT(t.size() == 1);
    cout << "**************End DEBUG 3 ******************" << endl;

    cout << "*******DEBUG 4 : break some links ***********" << endl;
    /* Break some links here */
    s = m->instance("1");
    s->attributeIs("return segment", "");
    s = m->instance("2");
    s->attributeIs("return segment", "");
    s = m->instance("3");
    s->attributeIs("return segment", "");

    ASSERT(tokenize(conn->attribute("connect a : d")).empty());
    ASSERT(tokenize(conn->attribute("connect c : e")).empty());
    ASSERT(tokenize(conn->attribute("connect e : b")).empty());
}

int main(int argc, char *argv[]) {
    int test;
    extern char *optarg;
    int c;
    while ((c = getopt(argc, argv, "t:")) != -1) {
        switch(c) {
            case 't':
                test = atoi(optarg);
                break;
            case '?':
                fprintf(stderr, "Unrecognized option: -%c\n", optopt);
        }
    }
    
    if(test == 1)      repLayerConfigTest();
    else if(test == 2) simpleConnectionsTest();
    else if(test == 3) networkTest();
    else if(test == 4) invalidOperationsTest1(); /* Testing invalid ops on fleet, stats, locations. */
    else if(test == 5) invalidOperationsTest2(); /* testing on segment-location...linking unlinking etc*/
    else if(test == 6) invalidOperationsTest3(); /* testing on segment-return segment...linking unlinking etc*/
    else if(test == 7) segmentLocationTypeCompatibilityTest(); /* Testing the type compatibility between locations and segments */
    else if(test == 8) passThroughTest(); /* Break layering to test internals*/
    else if(test == 9) finalTest(); 
    else if(test == 10) ofcTest1();
    else cout << "Invalid option: Try again!" << endl; 
    return 0;
}

