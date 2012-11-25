/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#include "RealTimeActivityManager.h"
#include "VirtualTimeActivityManager.h"
#include "Defines.h"
#include <iostream>
#include <sstream>
#include "fwk/Exception.h"

using namespace Shipping;
using namespace std; 

RealTimeActivityManager::RealTimeActivityManager(const std::string& _name):
    Fwk::Activity::Manager(_name),
    virtualTimeActivityManager_(NULL){}

RealTimeActivityManager::Ptr RealTimeActivityManager::RealTimeActivityManagerNew
    (const string &_name) {
    RealTimeActivityManager::Ptr rtam = new RealTimeActivityManager(_name);
    
    return rtam;
}

Fwk::Activity::Ptr RealTimeActivityManager::activityNew(const string& name) {
    Fwk::Activity::Ptr activity = activities_[name];
    if (activity != NULL) {
	ostringstream s; 
	s << "RTAM::ActivityNew: Activity with the name = " << name << " already exists.";
	cerr << s.str() << endl; 
        throw Fwk::NameInUseException(s.str()); 
    }
    
    activity = new Fwk::Activity(name, this);
    activities_[name] = activity;
    return activity;
}


Fwk::Activity::Ptr RealTimeActivityManager::activity(const string& _name) const {
    map<string, Fwk::Activity::Ptr>::const_iterator it = activities_.find(_name);
    
    if(it != activities_.end() ) {
        return it->second;
    }
   
    // dont throw an exception (accessor)
    DCOUT( "RTAM::activity: No activity with name = " << _name << endl); 
    return NULL; 
}

void RealTimeActivityManager::activityDel(const string& _name) {
    activities_.erase(_name);
}

void RealTimeActivityManager::lastActivityIs(Fwk::Activity::Ptr _activity) {
    scheduledActivities_.push(_activity);
}

void RealTimeActivityManager::scalingFactorIs(Fwk::ScalingFactor _sf){
    if(scalingFactor_ == _sf)
	return; 
    scalingFactor_ = _sf; 
} 

void RealTimeActivityManager::nowIs(Fwk::Time t) {
    while (!scheduledActivities_.empty()) {
        Fwk::Activity::Ptr nextToRun = scheduledActivities_.top();
        if (nextToRun->nextTime() > t) {
            break;
        }
	Fwk::Time diff = Fwk::Time(nextToRun->nextTime().value()-now_.value());
	/* scalingFactor_ seconds of real time sleep per hour of virtual time */
	usleep((int)(diff.value() *  scalingFactor_.value() * 1000000.0));

        now_ = nextToRun->nextTime();
        scheduledActivities_.pop();
        nextToRun->statusIs(Fwk::Activity::executing);
    }
    now_ = t;
}

void RealTimeActivityManager::virtualTimeActivityManagerIs (VirtualTimeActivityManager::Ptr _vtam) {
    virtualTimeActivityManager_ = _vtam;
}

RealTimeActivityManager::~RealTimeActivityManager(){
    DCOUT( "RTAM::~RealTimeActivityManager destructor" << endl); 
}
