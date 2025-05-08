#include <TelescopeImpl.h>
 
TelescopeImpl::TelescopeImpl(const ACE_CString& name, maci::ContainerServices * containerServices) : ACSComponentImpl(name, containerServices) {
}
 
TelescopeImpl::~TelescopeImpl() {
}
 
char* TelescopeImpl::printHello() {
    std::cout << "Just printing 'Hello World!'" << std::endl;
    return CORBA::string_dup("Hello World!");
}
 
/* --------------- [ MACI DLL support functions ] -----------------*/
#include <maciACSComponentDefines.h>
MACI_DLL_SUPPORT_FUNCTIONS(TelescopeImpl)
/* ----------------------------------------------------------------*/