/* **************************** INCLUDED HEADERS **************************** */
#include "SControl.hpp"


/* **************************** CLASS DEFINITION **************************** */
/*  --------  CONSTRUCTORS AND DESTRUCTOR  --------  */
SControl::SControl() {}


SControl::SControl(int32_t     ID, 
				   HWND        Handle, 
				   char*       ClassName, 
				   SDimensions Dimensions, 
				   DWORD       Style) 
					: m_ID(ID), 
					  m_Handle(Handle), 
					  m_ClassName(ClassName), 
					  m_Dimensions(Dimensions), 
					  m_Style(Style) {}


SControl::~SControl() {}


/*  --------  'GETTER' MEMBER FUNCTIONS  --------  */
char* SControl::getClassName() noexcept {
	return m_ClassName;
}


SDimensions SControl::getDimensions() noexcept {
	return m_Dimensions;
}


HWND SControl::getHandle() noexcept {
	return m_Handle;
}


int32_t SControl::getID() noexcept {
	return m_ID;
}


DWORD SControl::getStyle() noexcept {
	return m_Style;
}


/*  --------  'SETTER' MEMBER FUNCTIONS  --------  */
void SControl::setClassName(char* ClassName) {
	m_ClassName = ClassName;
}


void SControl::setDimensions(SDimensions Dimensions) {
	m_Dimensions = Dimensions;
}


void SControl::setHandle(HWND Handle) {
	m_Handle = Handle;
}


void SControl::setID(int32_t ID) {
	m_ID = ID;
}


void SControl::setStyle(DWORD Style) {
	m_Style = Style;
}
