/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#include "VirtualTimeActivityManager.h"
#include "Defines.h"
#include "RealTimeActivityManager.h"
#include "RealTimeActivityReactor.h"
#include <iostream>
#include <sstream>
#include "fwk/Exception.h"

using namespace Shipping; 
using namespace std; 

VirtualTimeActivityManager::VirtualTimeActivityManager(const std::string& _name):
    Fwk::Activity::Manager(_name),
    realTimeActivityManager_(NULL){}

VirtualTimeActivityManager::Ptr VirtualTimeActivityManager::VirtualTimeActivityManagerNew
    (const string &_name) {
    VirtualTimeActivityManager::Ptr vtam = new VirtualTimeActivityManager(_name);

    return vtam;
}

Fwk::Activity::Ptr VirtualTimeActivityManager::activityNew(const string& name){
    Fwk::Activity::Ptr activity = activities_[name];
    if (activity != NULL) {
	ostringstream s; 
	s << "VTAM::ActivityNew: Activity with the name = " << name << " already exists.";
	cerr << s.str() << endl; 
        throw Fwk::NameInUseException(s.str()); 
    }
    
    activity = new Fwk::Activity(name, this);
    activities_[name] = activity;
    return activity;
}
    
Fwk::Activity::Ptr VirtualTimeActivityManager::activity(const string& _name) const {
    map<string, Fwk::Activity::Ptr>::const_iterator it = activities_.find(_name);
    
    if(it != activities_.end() ) {
        return it->second;
    }
   
    // dont throw an exception (accessor)
    DCOUT( "VTAM::activity: No activity with name = " << _name << endl); 
    return NULL; 
}

void VirtualTimeActivityManager::activityDel(const string& _name) {
    activities_.erase(_name);
}

void VirtualTimeActivityManager::lastActivityIs(Fwk::Activity::Ptr _activity) {
    scheduledActivities_.push(_activity);
    
    string rtName = string("RealTime") + _activity->name();
    Fwk::Activity::Ptr rtAct = realTimeActivityManager_->activityNew(rtName);
    
    Fwk::Time nextTime = _activity->nextTime().value() * realTimeActivityManager_->scalingFactor().value();
    rtAct->nextTimeIs(nextTime);

    RealTimeActivityReactor::Ptr rtReactor = 
	new RealTimeActivityReactor( rtName + string("Reactor"), 
	    rtAct.ptr(), realTimeActivityManager_, this, 
            _activity->nextTime()); 
	    
    rtAct->lastNotifieeIs( rtReactor.ptr()); 
    rtAct->statusIs(Fwk::Activity::nextTimeScheduled);
}

void VirtualTimeActivityManager::nowIs(Fwk::Time t) {
    while (!scheduledActivities_.empty()) {
        Fwk::Activity::Ptr nextToRun = scheduledActivities_.top();
        if (nextToRun->nextTime() > t) {
            break;
        }
        /* VTAM doesn't sleep */ 
	now_ = nextToRun->nextTime();

        scheduledActivities_.pop();
        nextToRun->statusIs(Fwk::Activity::executing);
        nextToRun->statusIs(Fwk::Activity::free);
    }
    now_ = t;
}

void VirtualTimeActivityManager::realTimeActivityManagerIs(Fwk::Ptr<RealTimeActivityManager> _rtam){
    realTimeActivityManager_ = _rtam; 
}

VirtualTimeActivityManager::~VirtualTimeActivityManager(){
    DCOUT( "VTAM: destructor" << endl);
}

