// Copyright (c) 1993-2007 David R. Cheriton, all rights reserved.
// PtrInterface.h

#ifndef FWK_NAMEDINTERFACE_H
#define FWK_NAMEDINTERFACE_H

#include "Ptr.h"
#include "Types.h"
#include "String.h"
#include "PtrInterface.h"

namespace Fwk {

class NamedInterface : public PtrInterface<NamedInterface>
{
public:
	String name() const { return name_; }

protected:
	NamedInterface(const String& name) : name_(name) { }

private:
	String name_;
};

}

#endif
