/*
    Tirthankar Chatterjee - tirth@stanford.edu
    Caesar De La Paz - cdelapaz@stanford.edu
*/
#include "ShippingValueTypes.h"
#include <iostream>
#include <sstream>
#include "Defines.h"
#include "fwk/Exception.h"

using namespace Shipping;
using namespace std;

Dollars::Dollars() : Ordinal<Dollars, double>(Dollars::max()) {}
Dollars::Dollars(double _val) : Ordinal<Dollars, double>(_val) {}

Hours::Hours() : Ordinal<Hours, double>(Hours::max()) {}
Hours::Hours(double _val) : Ordinal<Hours, double>(_val) {}

MilesPerHour::MilesPerHour() : Ordinal<MilesPerHour, double>(MilesPerHour::max()){}
MilesPerHour::MilesPerHour(double _val) : Ordinal<MilesPerHour, double>(_val){
    if(_val < MilesPerHour::min()){
	ostringstream s;
	s.precision(2);
	s << fixed; 
	
	s << "Invalid MilesPerHour value = " << _val << " Value is = " << value_;
	cerr << s.str() << endl;
	throw Fwk::RangeException(s.str()); 
    }
}

Miles::Miles() : Ordinal<Miles, double>(Miles::max()) {}
Miles::Miles(double _val) : Ordinal<Miles, double>(_val) {
    if(_val < Miles::min()) {
	ostringstream s;
	s.precision(2);
	s << fixed; 
	
	s << "Invalid Miles value = " << _val << " Value is = " << value_;
	cerr << s.str() << endl;
	throw Fwk::RangeException(s.str()); 
    }
}


DifficultyLevel::DifficultyLevel() : Ordinal<DifficultyLevel, double>(DifficultyLevel::min()){}
DifficultyLevel::DifficultyLevel(double _val) : Ordinal<DifficultyLevel, double>(_val){
    if(_val < DifficultyLevel::min() || _val > DifficultyLevel::max()) {
	ostringstream s;
	s.precision(2);
	s << fixed; 
	
	s << "Invalid DifficultyLevel value = " << _val << " Value is = " << value_;
	cerr << s.str() << endl;
	throw Fwk::RangeException(s.str()); 
    }
}

NumPackages::NumPackages() : Ordinal<NumPackages, unsigned int>(NumPackages::min()){}
NumPackages::NumPackages(unsigned int _val) : Ordinal<NumPackages, unsigned int>(_val){
    if(_val < NumPackages::min()) {
	ostringstream s;
	s.precision(2);
	s << fixed; 
	
	s << "Invalid NumPackages value = " << _val << " Value is = " << value_;
	cerr << s.str() << endl;
	throw Fwk::RangeException(s.str()); 
    }
}

DollarsPerMile::DollarsPerMile() : Ordinal<DollarsPerMile, double>(DollarsPerMile::min()){}
DollarsPerMile::DollarsPerMile(double _val) : Ordinal<DollarsPerMile, double>(_val){
    if(_val < DollarsPerMile::min()) {
	ostringstream s;
	s.precision(2);
	s << fixed; 
	
	s << "Invalid DollarsPerMile value = " << _val << " Value is = " << value_;
	cerr << s.str() << endl;
	throw Fwk::RangeException(s.str()); 
    }
}

NumShipments::NumShipments() : Ordinal<NumShipments, unsigned int>(NumShipments::min()){}
NumShipments::NumShipments(unsigned int _val) : Ordinal<NumShipments, unsigned int>(_val){
    if(_val < NumShipments::min()) {
	ostringstream s;
	s.precision(2);
	s << fixed; 
	
	s << "Invalid NumShipments value = " << _val << " Value is = " << value_;
	cerr << s.str() << endl;
	throw Fwk::RangeException(s.str()); 
    }
}

TransferRate::TransferRate() : Ordinal<TransferRate, double>(TransferRate::min()){}
TransferRate::TransferRate(double _val) : Ordinal<TransferRate, double>(_val){
    if(_val < TransferRate::min()) {
	ostringstream s;
	s.precision(2);
	s << fixed; 
	
	s << "Invalid TransferRate value = " << _val << " Value is = " << value_;
	cerr << s.str() << endl;
	throw Fwk::RangeException(s.str()); 
    }
}

HourOfDay::HourOfDay() : Ordinal<HourOfDay, unsigned int>(HourOfDay::min()) {}
HourOfDay::HourOfDay(unsigned int _val) : Ordinal<HourOfDay, unsigned int>(_val){
     if (_val < HourOfDay::min() || _val > HourOfDay::max()){
	ostringstream s;
	s.precision(2);
	s << fixed; 
	
	s << "Invalid HourOfDay value = " << _val << " Value is = " << value_;
	cerr << s.str() << endl;
	throw Fwk::RangeException(s.str()); 
    }
}
