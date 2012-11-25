/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#ifndef _REALTIMEACTIVITYMANAGER_H
#define _REALTIMEACTIVITYMANAGER_H

#include "fwk/Activity.h"

namespace Shipping {
    class VirtualTimeActivityManager; 
    class RealTimeActivityManager : public Fwk::Activity::Manager {
    public:
	typedef Fwk::Ptr<RealTimeActivityManager> Ptr;
    	typedef Fwk::Ptr<RealTimeActivityManager const> PtrConst;

    	static Ptr RealTimeActivityManagerNew(const std::string& _name);

    	Fwk::Activity::Ptr activityNew(const std::string& _name);
    	Fwk::Activity::Ptr activity(const std::string& _name) const;
    	void activityDel(const std::string& _name);

    	void lastActivityIs(Fwk::Activity::Ptr _activity);

    	Fwk::ScalingFactor scalingFactor() const { return scalingFactor_; }
	/* scalingFactor is number of seconds of Real time 
	   per hour of virtual time. */
	void scalingFactorIs(Fwk::ScalingFactor _sf); 
	
	Fwk::Time now() const { return now_; }
    	void nowIs(Fwk::Time _time);

    	void virtualTimeActivityManagerIs(Fwk::Ptr<VirtualTimeActivityManager> _vtam);
    	Fwk::Ptr<VirtualTimeActivityManager> virtualTimeActivityManager() const {
	    return virtualTimeActivityManager_;
	}

	~RealTimeActivityManager();
    protected:
	RealTimeActivityManager();
	RealTimeActivityManager(const RealTimeActivityManager &);
	RealTimeActivityManager(const std::string& _name);

	Fwk::ScalingFactor scalingFactor_; 

    	Fwk::Ptr<VirtualTimeActivityManager> virtualTimeActivityManager_;
    };
}

#endif

