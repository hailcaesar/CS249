// Basic notifiee class template
// Copyright(c) 1993-2006, 2007, David R. Cheriton, all rights reserved.

/* Edit by Tirthankar Chatterjee and Caesar de La Paz Nov, 2012 */

#ifndef FWK_BASENOTIFIEE_H
#define FWK_BASENOTIFIEE_H

#include "PtrInterface.h"
#include "Exception.h"
#include "Ptr.h"
#include "Types.h"
#include "String.h"
#include "NamedInterface.h"

namespace Fwk {
    
    template<class Notifier>
    class BaseNotifiee  : public NamedInterface {
        public:
    	    typedef Fwk::Ptr<BaseNotifiee const> PtrConst;
    	    typedef Fwk::Ptr<BaseNotifiee> Ptr;
    	    
            BaseNotifiee(const std::string & _name, Fwk::Ptr<Notifier> _notifier) :
            	Fwk::NamedInterface(_name), notifier_(_notifier) {
                if (notifier_ != NULL) {
                    notifier_->notifieeIs(this->name(), static_cast<class Notifier::Notifiee *>(this));
                }
            }
            void notifierIs(Fwk::Ptr<Notifier> _notifier) {
                if (notifier_ == _notifier) 
        	   return;
                                                                                                     
                if (notifier_ != NULL) { 
        	   /* Make its notifiee point to NULL */
        	   notifier_->notifieeIs(this->name(), static_cast<class Notifier::Notifiee *>(NULL));
        	}
                                                                                                     
                notifier_ = _notifier;
                if (notifier_ != NULL) {
        	   /* Make "this" a notifiee of the notifier */
        	   notifier_->notifieeIs(this->name(), static_cast<class Notifier::Notifiee *>(this));
        	}
            }
                                                                                                     
            Fwk::Ptr<Notifier> notifier() const { return notifier_; }
                                                                                                     
    	    ~BaseNotifiee() {}
        private:
            Fwk::Ptr<Notifier> notifier_;
                                                                                                     
    };

}

#endif /* BASENOTIFIEE_H */
