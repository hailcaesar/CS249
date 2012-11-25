/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu

    Original file from: Assignment 3 starter code. 
    Edited: Nov 2012
*/

#ifndef __ACTIVITY_H__
#define __ACTIVITY_H__

#include <string>
#include "PtrInterface.h"
#include "Ptr.h"
#include "Nominal.h"
#include "BaseNotifiee.h"
#include <vector>
#include <queue>
#include <map>

using std::string;

namespace Fwk {
    class Time : public Ordinal<Time,double> {
    public:
        Time() : Ordinal<Time, double>(0.00){}
	Time(double time) : Ordinal<Time,double>(time){}
	static double min() { return 0.00; }
    };

    class ScalingFactor : public Ordinal<ScalingFactor, double> {
    public:
        ScalingFactor() : Ordinal<ScalingFactor, double>(1.00) {}
        ScalingFactor(double value) : Ordinal<ScalingFactor, double>(value) {
            if (value < 1.00){
                std::cerr << "Invalid scaling factor value = " << value << std::endl;
                throw new std::bad_alloc(); //TODO : use Exception class
            }
        }
	static double min() { return 1.00; }
    };
     
    class Activity : public Fwk::PtrInterface<Activity> {
    public:
        typedef Fwk::Ptr<Activity> Ptr;
        class Manager;

        enum Status {
            free, waiting, ready, executing, nextTimeScheduled, deleted
        };
    
	class Notifiee : public Fwk::BaseNotifiee<Activity> {
        public:
	    typedef Fwk::Ptr<Notifiee> Ptr;
    
            Notifiee(const std::string& name, Activity* act) : Fwk::BaseNotifiee<Activity>(name, act) {}
    
            virtual void onNextTime() {}
	    virtual void onStatus() {}
        };
    
	Activity(const std::string& name, Fwk::Ptr<Manager> manager) :
	    name_(name),
	    status_(free),
	    nextTime_(0.0),
	    notifiee_(NULL),
	    manager_(manager) {}
	    
    	Fwk::Ptr<Manager> manager() const { return manager_; }
    
        virtual Status status() const {return status_; }
	virtual void statusIs(Status s) {
	    status_ = s;
	    if (notifiee_ != NULL) {
		notifiee_->onStatus();
	    }
	}
        
        virtual Time nextTime() const {return nextTime_;}
	virtual void nextTimeIs(Time t) {
	    nextTime_ = t;
	    if (notifiee_ != NULL) {
	    notifiee_->onNextTime();
	    }
	}
    
        virtual Fwk::Ptr<Notifiee> notifiee() const {return notifiee_;}
    
        virtual void notifieeIs(const std::string& name, Notifiee* n) {
	    Activity* me = const_cast<Activity*>(this);
	    me->notifiee_ = n;
	}
	
	virtual void lastNotifieeIs(Notifiee* n) {
	    Activity* me = const_cast<Activity*>(this);
	    me->notifiee_ = n;
	}
    
        virtual string name() const { return name_; }
	virtual ~Activity(){} 
    protected:
	Activity();
	Activity(const Activity &);

    private:
        string name_;
	Status status_; 
	Time nextTime_; 
	Notifiee* notifiee_;
	Fwk::Ptr<Manager> manager_; 
    };
    
    class ActivityComp : public std::binary_function<Fwk::Ptr<Activity>, Fwk::Ptr<Activity>, bool> {
    public:
        ActivityComp() {}
	
        bool operator()(Fwk::Ptr<Activity> a, Fwk::Ptr<Activity> b) const {
            return (a->nextTime() > b->nextTime());
        }
    };
    
    class Activity::Manager : public Fwk::PtrInterface<Activity::Manager> {
    public:
        typedef Fwk::Ptr<Activity::Manager> Ptr;
	
	Manager(const std::string &_name) : name_(_name), now_(0.0){}

        virtual Fwk::Ptr<Activity> activityNew(const string &name) = 0;
        virtual Fwk::Ptr<Activity> activity(const string &name) const = 0;
        virtual void activityDel(const string &name) = 0;
        virtual void lastActivityIs(Activity::Ptr) = 0;
        virtual Time now() const = 0;
        virtual void nowIs(Time) = 0;

	virtual ~Manager() {}
    protected:
	Manager(); 
	Manager(const Manager &); 

	std::string name_; 
        std::priority_queue<Activity::Ptr,
	    std::vector<Activity::Ptr>, 
	    ActivityComp> scheduledActivities_;
        std::map<string, Activity::Ptr> activities_; 
        Time now_;
    };
}

#endif
