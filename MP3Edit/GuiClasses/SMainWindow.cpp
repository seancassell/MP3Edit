/* **************************** INCLUDED HEADERS **************************** */
#include "SMainWindow.hpp"


/* **************************** CLASS DEFINITION **************************** */
/*  --------  CONSTRUCTORS AND DESTRUCTOR  --------  */
SMainWindow::SMainWindow() noexcept {}


SMainWindow::SMainWindow(int32_t     ID, 
						 HWND        Handle, 
						 char*       ClassName, 
						 SDimensions Dimensions, 
						 DWORD       Style, 
						 std::vector<SControl> Controls) noexcept 
							: m_ID(ID), 
							  m_Handle(Handle), 
							  m_ClassName(ClassName), 
							  m_Dimensions(Dimensions), 
							  m_Style(Style), 
							  m_Controls(Controls) {}


SMainWindow::~SMainWindow() noexcept {
	m_ClassName = nullptr;
	m_Handle    = nullptr;
	m_Controls.~vector();
}


/*  --------  'GETTER' MEMBER FUNCTIONS  --------  */
char* SMainWindow::getClassName() noexcept {
	return m_ClassName;
}


SDimensions SMainWindow::getDimensions() noexcept {
	return m_Dimensions;
}


HWND SMainWindow::getHandle() noexcept {
	return m_Handle;
}


int32_t SMainWindow::getID() noexcept {
	return m_ID;
}


DWORD SMainWindow::getStyle() noexcept {
	return m_Style;
}


std::vector<SControl> SMainWindow::getControls() noexcept {
	return m_Controls;
}


/*  --------  'SETTER' MEMBER FUNCTIONS  --------  */
void SMainWindow::setClassName(char* ClassName) {
	m_ClassName = ClassName;
}


void SMainWindow::setDimensions(SDimensions Dimensions) {
	m_Dimensions = Dimensions;
}


void SMainWindow::setHandle(HWND Handle) {
	m_Handle = Handle;
}


void SMainWindow::setID(int32_t ID) {
	m_ID = ID;
}


void SMainWindow::setStyle(DWORD Style) {
	m_Style = Style;
}


void SMainWindow::addControl(SControl Control) noexcept {
	m_Controls.push_back(Control);
}
