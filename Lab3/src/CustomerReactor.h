/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#ifndef _CUSTOMERREACTOR_H_
#define _CUSTOMERREACTOR_H_

#include "Location.h"
#include "InjectActivityReactor.h"

namespace Shipping {
    class Network;
    class CustomerReactor : public CustomerLocation::Notifiee {
    public:
        typedef Fwk::Ptr<CustomerReactor const> PtrConst;
        typedef Fwk::Ptr<CustomerReactor> Ptr;
	
	enum Status {notUpdated_, fullyUpdated_}; 

	static Status notUpdated() {return notUpdated_;}
	static Status fullyUpdated() {return fullyUpdated_;}

        static CustomerReactor::Ptr CustomerReactorNew(	const string& _name,
							CustomerLocation* _notifier, 
							Fwk::Ptr<VirtualTimeActivityManager> _vtam,
							Fwk::Ptr<Network> _network ); 
        void onUpdate();
	~CustomerReactor(){}

    protected:
        CustomerReactor();
        CustomerReactor(const CustomerReactor&);
        CustomerReactor(const string &_name, 
			CustomerLocation* _notifier,
			Fwk::Ptr<VirtualTimeActivityManager> _vtam,
			Fwk::Ptr<Network> _network);

	Status status_;  
        Fwk::Ptr<VirtualTimeActivityManager> vtam_;
        Fwk::Ptr<Network> network_; 
	Fwk::Ptr<InjectActivityReactor> iar_; 
	Fwk::Ptr<Fwk::Activity> activity_; 
    };   

}

#endif
