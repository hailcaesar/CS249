#CXXFLAGS = -Wall -g -DDEBUG=1 
CXXFLAGS = -Wall -g 
OBJECTS += fwk/Exception.o
OBJECTS += Instance.o ShippingValueTypes.o Fleet.o Segment.o Location.o Network.o Stats.o Conn.o Graph.o ConnectGraph.o ExploreGraph.o 
OBJECTS += ManagerImpl.o LocationRep.o FleetRep.o SegmentRep.o StatsRep.o ConnRep.o TimeManagerRep.o 
OBJECTS += VirtualTimeActivityManager.o RealTimeActivityManager.o RealTimeActivityReactor.o CustomerReactor.o SegmentReactor.o Shipment.o InjectActivityReactor.o
OBJECTS += FleetReactor.o FleetUpdateActivityReactor.o

default:	test1 example tests usaTest officialTests

test1:	test1.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

example:	example.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

tests: tests.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

usaTest: usaTest.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

officialTests: officialTests.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^
clean:
	    rm -rf test1 test1.o example example.o tests tests.o usaTest usaTest.o officialTests officialTests.o $(OBJECTS) *~
                                                                                                 
cleanall:                                                                                        
	    rm -rf test1 test1.o example example.o tests tests.o usaTest usaTest.o officialTests officialTests.o $(OBJECTS) *~

# Framework Exception class
fwk/Exception.o: fwk/Exception.h fwk/Exception.cpp

# Rep layer
Instance.o    : Instance.cpp Instance.h PtrInterface.h Ptr.h
ManagerImpl.o : ManagerImpl.h ManagerImpl.cpp
LocationRep.o : LocationRep.h LocationRep.cpp
FleetRep.o    : FleetRep.h FleetRep.cpp
SegmentRep.o  : SegmentRep.h SegmentRep.cpp
StatsRep.o    : StatsRep.h StatsRep.cpp 
ConnRep.o     : ConnRep.h ConnRep.cpp
TimeManagerRep.o : TimeManagerRep.h TimeManagerRep.cpp

# Engine layer
ShippingValueTypes.o: ShippingValueTypes.h ShippingValueTypes.cpp
Fleet.o	    : Fleet.h Fleet.cpp
Segment.o   : Segment.h Segment.cpp
Location.o  : Location.h Location.cpp
Network.o   : Network.h Network.cpp
Conn.o	    : Conn.h Conn.cpp
Stats.o	    : Stats.h Stats.cpp
Graph.o     : Graph.h Graph.cpp
Shipment.o  : Shipment.cpp Shipment.h
ConnectGraph.o		    : ConnectGraph.cpp ConnectGraph.h
ExploreGraph.o		    : ExploreGraph.cpp ExploreGraph.h
VirtualTimeActivityManager.o: VirtualTimeActivityManager.h VirtualTimeActivityManager.cpp
RealTimeActivityManager.o   : RealTimeActivityManager.h RealTimeActivityManager.cpp
RealTimeActivityReactor.o   : RealTimeActivityReactor.h RealTimeActivityReactor.cpp
CustomerReactor.o	    : CustomerReactor.cpp CustomerReactor.h
SegmentReactor.o	    : SegmentReactor.cpp SegmentReactor.h
InjectActivityReactor.o	    : InjectActivityReactor.cpp InjectActivityReactor.h
FleetReactor.o		    : FleetReactor.h FleetReactor.cpp
FleetUpdateActivityReactor.o: FleetUpdateActivityReactor.h FleetUpdateActivityReactor.cpp

# Test file : Client Layer
test1.o: test1.cpp Instance.h PtrInterface.h Ptr.h Defines.h Fwk.h
tests.o: tests.cpp Instance.h PtrInterface.h Ptr.h Defines.h Fwk.h
usaTest.o: usaTest.cpp Instance.h PtrInterface.h Ptr.h Defines.h Fwk.h
officialTests.o: officialTests.cpp Instance.h PtrInterface.h Ptr.h Defines.h Fwk.h
