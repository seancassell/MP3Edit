/* ****************************** HEADER GUARD ****************************** */
#pragma once


/* **************************** INCLUDED HEADERS **************************** */
#include <SDKDDKVer.h> // Master include file for versioning Windows SDK/DDK

// C RUNTIME COMPATIBILITY HEADERS:
#include <cinttypes>

// WINDOWS SDK HEADERS:
// For a list and description of child header files included by <Windows.h>, see
// the following entry on Wikipedia: https://en.wikipedia.org/wiki/Windows.h
#include <Windows.h>  // Master include file for Windows applications

// PROJECT-SPECIFIC HEADERS:
#include "SDimensions.h"


/* ****************************** ENUM CLASSES ****************************** */
enum class SType {
	Button, 
	ComboBox, 
	Edit, 
	Image, 
	Label, 
	Other
};


/* *************************** CLASS DECLARATION **************************** */
class SControl {
	
	public:
		SType       m_Type       = SType::Label;
		int32_t     m_ID         = 0;
		HWND        m_Handle     = nullptr;
		char*       m_ClassName  = nullptr;
		SDimensions m_Dimensions = {1,1,1,1};
		DWORD       m_Style      = WS_VISIBLE|WS_CHILD;
	
	public:
		// Constructors and destructor:
		SControl() noexcept;
		SControl(int32_t     ID, 
				 HWND        Handle, 
				 char*       ClassName, 
				 SDimensions Dimensions, 
				 DWORD       Style) noexcept;
		~SControl() noexcept;
		
		// 'Getter' member functions:
		char*       getClassName() noexcept;
		SDimensions getDimensions() noexcept;
		HWND        getHandle() noexcept;
		int32_t     getID() noexcept;
		DWORD       getStyle() noexcept;
		
		// 'Setter' member functions:
		void        setClassName(char* ClassName);
		void        setDimensions(SDimensions Dimensions);
		void        setHandle(HWND Handle);
		void        setID(int32_t ID);
		void        setStyle(DWORD Style);
	
};
