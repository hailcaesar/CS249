/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/

#ifndef _SHIPPINGVALUETYPES_H_
#define _SHIPPINGVALUETYPES_H_

#include "Nominal.h"
#include <limits>

#define MIN_DOLLARS 0.0
#define MIN_HOURS 0.0
#define MIN_MILES_PER_HOUR 0.0
#define MIN_MILES 0.0
#define MIN_DIFFICULTY_LEVEL 1.0
#define MAX_DIFFICULTY_LEVEL 5.0
#define MIN_NUM_PACKAGES 0
#define MIN_NUM_SHIPMENTS 0
#define MIN_DOLLARS_PER_MILE 0.0
#define MIN_TRANSFER_RATE 0.0
#define MAX_TRANSFER_RATE 10000000
#define HOURS_PER_DAY 24.0
#define MIN_HOUR_OF_DAY 0
#define MAX_HOUR_OF_DAY 24

namespace Shipping {
    
    class Dollars : public Ordinal<Dollars, double>{ 
	public:
	    Dollars(); 
	    Dollars(double _val); 
	    static double min() {return MIN_DOLLARS;}
	    static double max() {return std::numeric_limits<double>::max();}
    };

    class Hours : public Ordinal<Hours, double>{ 
	public: 
	    Hours(); 
	    Hours(double _val); 
	    static double min() {return MIN_HOURS;}
	    static double max() {return std::numeric_limits<double>::max();}
    };
    
    class MilesPerHour : public Ordinal<MilesPerHour, double>{ 
	public: 
	    MilesPerHour(); 
	    MilesPerHour(double _val);  
	    static double min() {return MIN_MILES_PER_HOUR;}
	    static double max() {return std::numeric_limits<double>::max();}
    };
    
    class Miles : public Ordinal<Miles, double>{ 
	public: 
	    Miles(); 
	    Miles(double _val); 
	    static double min() {return MIN_MILES;}
	    static double max() {return std::numeric_limits<double>::max();}
    };

    class DifficultyLevel : public Ordinal<DifficultyLevel, double> { 
	public:
	    DifficultyLevel(); 
	    DifficultyLevel(double _val); 
	    static double min() {return MIN_DIFFICULTY_LEVEL;}
	    static double max() {return MAX_DIFFICULTY_LEVEL;}
    };

    class NumPackages : public Ordinal<NumPackages, unsigned int> {
	public:
	    NumPackages(); 
	    NumPackages(unsigned int _val);
	    static unsigned int min() {return MIN_NUM_PACKAGES;} 
	    static double max() {return std::numeric_limits<unsigned int>::max();}
    };

    class DollarsPerMile : public Ordinal<DollarsPerMile, double> {
	public:
	    DollarsPerMile(); 
	    DollarsPerMile(double _val);
	    static double min(){return MIN_DOLLARS_PER_MILE;}
	    static double max() {return std::numeric_limits<double>::max();}
    };
    
    class NumShipments : public Ordinal<NumShipments, unsigned int> {
	public:
	    NumShipments();
	    NumShipments(unsigned int _val);
	    static unsigned int min() {return MIN_NUM_SHIPMENTS;}
	    static double max() {return std::numeric_limits<unsigned int>::max();}
    };
    
    
    class TransferRate : public Ordinal<TransferRate, double> {
	public:
	    TransferRate();
	    TransferRate(double _val);
	    static double min() {return MIN_TRANSFER_RATE;}
	    static double max() {return std::numeric_limits<double>::max();}
    };

    class HourOfDay : public Ordinal<HourOfDay, unsigned int> {
	public:
    	    HourOfDay();
    	    HourOfDay(unsigned int _val);
	    static unsigned int min() {return MIN_HOUR_OF_DAY;}
	    static unsigned int max() {return(MAX_HOUR_OF_DAY - 1);}
    };

}


#endif
