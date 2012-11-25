/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#ifndef _INJECTACTIVITYREACTOR_H_
#define _INJECTACTIVITYREACTOR_H_

#include "VirtualTimeActivityManager.h"
#include "fwk/Activity.h"
#include "ShippingValueTypes.h"
#include "Network.h"

namespace Shipping {
    class Location;
    class InjectActivityReactor : public Fwk::Activity::Notifiee {
    public:
        typedef Fwk::Ptr<InjectActivityReactor const> PtrConst;
        typedef Fwk::Ptr<InjectActivityReactor> Ptr;

        InjectActivityReactor(	const std::string& _iarName,
				const std::string& _srcName,
				const std::string& _dstName,
				TransferRate _transferRate,
            			NumPackages _shipmentSize,
				Fwk::Ptr<Network> _network, 	
				Fwk::Ptr<VirtualTimeActivityManager> _vtam,
				Fwk::Activity::Ptr _activity );
	/* Reactor method */
        void onStatus();

	/* Accessors */
	std::string srcName() const { return srcName_; }
        std::string dstName() const { return dstName_; }
        TransferRate transferRate() const { return transferRate_; }
        NumPackages shipmentSize() const { return shipmentSize_; }
	Fwk::Ptr<Network> network() const {return network_; }
        Fwk::Ptr<VirtualTimeActivityManager> virtualTimeActivityManager() const { return vtam_; }
        Fwk::Activity::Ptr activity() const { return activity_; }

        /* Mutators */
	void dstNameIs(const std::string& _dstName); 
        void transferRateIs(TransferRate _transferRate);
        void shipmentSizeIs(NumPackages _shipmentSize);
    
	~InjectActivityReactor() {}
    protected:
	InjectActivityReactor(); 
	InjectActivityReactor(InjectActivityReactor &); 

        std::string srcName_;  
        std::string dstName_; 
        TransferRate transferRate_;
        NumPackages shipmentSize_;
	Fwk::Ptr<Network> network_; 	
        Fwk::Ptr<VirtualTimeActivityManager> vtam_;
        Fwk::Activity::Ptr activity_;
    };
}

#endif
