/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#ifndef _REALTIMEACTIVITYREACTOR_H
#define _REALTIMEACTIVITYREACTOR_H

#include "fwk/Activity.h"

namespace Shipping {
    class RealTimeActivityManager;
    class VirtualTimeActivityManager;
    class RealTimeActivityReactor : public Fwk::Activity::Notifiee {
    public:
	RealTimeActivityReactor(const std::string& _name, Fwk::Activity*,
            Fwk::Ptr<RealTimeActivityManager>, 
	    Fwk::Ptr<VirtualTimeActivityManager>, 
	    Fwk::Time _vNextTime);
        
	void onStatus();
	~RealTimeActivityReactor(); 
    protected:
	RealTimeActivityReactor(); 
	RealTimeActivityReactor(const RealTimeActivityReactor &); 

        Fwk::Activity::Ptr activity_;
        Fwk::Ptr<RealTimeActivityManager> rtam_;
        Fwk::Ptr<VirtualTimeActivityManager> vtam_;
        Fwk::Time vNextTime_;
    };
}

#endif

