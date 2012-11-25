/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#ifndef _VIRTUALTIMEACTIVITYMANAGER_H
#define _VIRTUALTIMEACTIVITYMANAGER_H

#include "Fwk.h"

namespace Shipping {
    class RealTimeActivityManager;
    
    class VirtualTimeActivityManager : public Fwk::Activity::Manager {
    public:
	typedef Fwk::Ptr<VirtualTimeActivityManager> Ptr;
    	typedef Fwk::Ptr<VirtualTimeActivityManager const> PtrConst;

    	static Ptr VirtualTimeActivityManagerNew(const std::string &_name);

    	Fwk::Activity::Ptr activityNew(const std::string& _name);
    	Fwk::Activity::Ptr activity(const std::string& _name) const;
    	void activityDel(const std::string& _name);

    	void lastActivityIs(Fwk::Activity::Ptr _activity);

    	Fwk::Time now() const { return now_; }
    	void nowIs(Fwk::Time _time);

    	void realTimeActivityManagerIs(Fwk::Ptr<RealTimeActivityManager> _r);
	~VirtualTimeActivityManager();
    protected:
	VirtualTimeActivityManager();
	VirtualTimeActivityManager(const VirtualTimeActivityManager &);
	VirtualTimeActivityManager(const std::string &_name);

    	Fwk::Ptr<RealTimeActivityManager> realTimeActivityManager_;
    };
}

#endif

