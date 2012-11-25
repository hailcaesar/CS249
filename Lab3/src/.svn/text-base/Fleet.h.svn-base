/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#ifndef _FLEET_H
#define _FLEET_H

#include <string>
#include "Defines.h"
#include "Instance.h"
#include "Nominal.h"
#include "ShippingValueTypes.h"
#include "VirtualTimeActivityManager.h"

namespace Shipping { 
    class Fleet : public Fwk::NamedInterface{
    public:
        typedef Fwk::Ptr<Fleet const> PtrConst; 
        typedef Fwk::Ptr<Fleet> Ptr; 

        enum Type {plane_ = 0, truck_ = 1, boat_ = 2};

        static Type truck() { return truck_; }
        static Type boat()  { return boat_ ; }
        static Type plane() { return plane_; }

	/* Accesors */
        MilesPerHour speed(Type _type)	const { return typeAttr[_type].speed_;}
        NumPackages capacity(Type _type)const { return typeAttr[_type].capacity_; }
        DollarsPerMile cost(Type _type) const { return typeAttr[_type].cost_; }

        MilesPerHour otherSpeed(Type _type)	const { return otherTypeAttr[_type].speed_;}
        NumPackages otherCapacity(Type _type)	const { return otherTypeAttr[_type].capacity_; }
        DollarsPerMile otherCost(Type _type)	const { return otherTypeAttr[_type].cost_; }

	HourOfDay otherAttrStartHour() const {return otherAttrStartHour_; } 
	HourOfDay otherAttrStopHour()  const {return otherAttrStopHour_; }

	Fwk::Ptr<VirtualTimeActivityManager> virtualTimeActivityManager() const { return vtam_; }

	/* Mutators */
        void speedIs(Type _type, MilesPerHour _speed);
        void capacityIs(Type _type, NumPackages _capacity);
        void costIs(Type _type, DollarsPerMile _cost); 
       
        void otherSpeedIs(Type _type, MilesPerHour _speed);
        void otherCapacityIs(Type _type, NumPackages _capacity);
        void otherCostIs(Type _type, DollarsPerMile _cost); 

	void  otherAttrHoursIs(HourOfDay _startHour, HourOfDay _stopHour);

        /* Instantiating Attributes */  
	static Fleet::Ptr FleetNew(const std::string & _name, Fwk::Ptr<VirtualTimeActivityManager> _vtam); 

	/* Notifiee definition */
	class Notifiee : public Fwk::BaseNotifiee<Fleet> {
	    public:
    	        typedef Fwk::Ptr<Fleet::Notifiee const> PtrConst;
    	        typedef Fwk::Ptr<Fleet::Notifiee> Ptr;

    	        Notifiee(const std::string& _name, Fleet* _fleet):
		    Fwk::BaseNotifiee<Fleet>(_name, _fleet) {}
    	        virtual void onOtherAttrHours() {};
		virtual ~Notifiee() {}
    	};

	void notifieeIs(const std::string& _name, Notifiee::Ptr _notifiee);
    protected:    
	Fleet(); 
	Fleet(const Fleet &); 
	Fleet(const std::string & _name, Fwk::Ptr<VirtualTimeActivityManager> _vtam); 
	
	struct attributes {
	    MilesPerHour speed_;
	    NumPackages capacity_; 
	    DollarsPerMile cost_;
	};

	Fwk::Ptr<VirtualTimeActivityManager> vtam_;
	Notifiee::Ptr notifiee_;

	/* One entry corresponding to each type of transportation */
	attributes typeAttr[3];
	attributes otherTypeAttr[3]; 

	HourOfDay otherAttrStartHour_; 
	HourOfDay otherAttrStopHour_;
    };
} 

#endif

