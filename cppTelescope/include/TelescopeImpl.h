#ifndef _TELESCOPE_IMPL_H
#define _TELESCOPE_IMPL_H

#ifndef __cplusplus
#error This is a C++ include file and cannot be used from plain C
#endif
 
//Base component implementation, including container services and component lifecycle infrastructure
#include <acscomponentImpl.h>
 
//Skeleton interface for server implementation
#include <TelescopeS.h>
#include <TypesC.h>
#include <TelescopeControlC.h>
#include <InstrumentC.h>

//Error definitions for catching and raising exceptions
class TelescopeImpl : public virtual acscomponent::ACSComponentImpl, public virtual POA_TELESCOPE_MODULE::Telescope {
  public:
    TelescopeImpl(const ACE_CString& name, maci::ContainerServices * containerServices);
    virtual ~TelescopeImpl();
    char* printHello();
    inline TYPES::Position getCurrentPosition() { return pos; };
    void moveTo(TYPES::Position const&);
    TYPES::ImageType* observe(const TYPES::Position&, CORBA::Long);

  private:
    TYPES::Position pos;
};
 
#endif
