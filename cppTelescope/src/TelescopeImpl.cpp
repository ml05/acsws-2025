#include <TelescopeImpl.h>
#include <TelescopeControlC.h>
#include <InstrumentC.h>
#include <SYSTEMErr.h>

TelescopeImpl::TelescopeImpl(const ACE_CString& name, maci::ContainerServices * containerServices) : ACSComponentImpl(name, containerServices) {

	pos.az = 0.;
	pos.el = 0.;

}
 
TelescopeImpl::~TelescopeImpl() {
}
 
char* TelescopeImpl::printHello() {
    std::cout << "Just printing 'Hello World!'" << std::endl;
    return CORBA::string_dup("Hello World!");
}
// PositionOutOfLimitsEx
void TelescopeImpl::moveTo(TYPES::Position const& coordinates) {
    if (coordinates.az < 0 || coordinates.az > 360 || coordinates.el > 90 || coordinates.el < 0) {
        throw SYSTEMErr::PositionOutOfLimitsExImpl(__FILE__, __LINE__, "TelescopeImpl::moveTo").getPositionOutOfLimitsEx();
    }
    // Request the TelescopeControl Component
    TELESCOPE_MODULE::TelescopeControl *comp = this->getContainerServices()->getComponent<TELESCOPE_MODULE::TelescopeControl>("TELESCOPE_CONTROL");

    comp->objfix(coordinates.el, coordinates.az);

    // Release Component
    this->getContainerServices()->releaseComponent(comp->name());

    // Update the internal coordinates
    pos.az = coordinates.az;
    pos.el = coordinates.el;

}

TYPES::ImageType* TelescopeImpl::observe(const TYPES::Position& coordinates, CORBA::Long exposureTime) {
    try {
        moveTo(coordinates);
        // Request the Instrument Component
        INSTRUMENT_MODULE::Instrument *comp = this->getContainerServices()->getComponent<INSTRUMENT_MODULE::Instrument>("INSTRUMENT");
        TYPES::ImageType* result = comp->takeImage(exposureTime);
        // Release Component
        this->getContainerServices()->releaseComponent(comp->name());
        return result;
    } catch(SYSTEMErr::PositionOutOfLimitsEx &_ex) {
        ACS_SHORT_LOG((LM_ERROR, "Coordinates out of limits"));
        throw SYSTEMErr::PositionOutOfLimitsExImpl(_ex, __FILE__, __LINE__, "TelescopeImpl::observe").getPositionOutOfLimitsEx();
    } catch(SYSTEMErr::CameraIsOffEx &_ex) {
        ACS_SHORT_LOG((LM_ERROR, "Error taking the picture: Camera is off"));
        throw SYSTEMErr::PositionOutOfLimitsExImpl(_ex, __FILE__, __LINE__, "TelescopeImpl::observe").getPositionOutOfLimitsEx();
    }
}
 
/* --------------- [ MACI DLL support functions ] -----------------*/
#include <maciACSComponentDefines.h>
MACI_DLL_SUPPORT_FUNCTIONS(TelescopeImpl)
/* ----------------------------------------------------------------*/
