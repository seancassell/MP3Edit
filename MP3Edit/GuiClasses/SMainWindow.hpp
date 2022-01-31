/* ****************************** HEADER GUARD ****************************** */
#pragma once


/* **************************** INCLUDED HEADERS **************************** */
#include <SDKDDKVer.h> // Master include file for versioning Windows SDK/DDK

// C++17 STANDARD LIBRARY/STL HEADERS:
#include <vector>

// C RUNTIME COMPATIBILITY HEADERS:
#include <cinttypes>

// WINDOWS SDK HEADERS:
// For a list and description of child header files included by <Windows.h>, see
// the following entry on Wikipedia: https://en.wikipedia.org/wiki/Windows.h
#include <Windows.h>  // Master include file for Windows applications

// PROJECT-SPECIFIC HEADERS:
#include "SControl.hpp"


/* *************************** CLASS DECLARATION **************************** */
class SMainWindow {
	
	private:
		int32_t     m_ID         = 0;
		HWND        m_Handle     = nullptr;
		char*       m_ClassName  = nullptr;
		SDimensions m_Dimensions = {1,1,1,1};
		DWORD       m_Style      = WS_VISIBLE | WS_CHILD;
		std::vector<SControl> m_Controls;
	
	public:
		SMainWindow() noexcept;
		SMainWindow(int32_t     ID, 
					HWND        Handle, 
					char*       ClassName, 
					SDimensions Dimensions, 
					DWORD       Style, 
					std::vector<SControl> Controls) noexcept;
		~SMainWindow() noexcept;
		
		// 'Getter' member functions:
		char*       getClassName() noexcept;
		SDimensions getDimensions() noexcept;
		HWND        getHandle() noexcept;
		int32_t     getID() noexcept;
		DWORD       getStyle() noexcept;
		std::vector<SControl> getControls() noexcept;
		
		// 'Setter' member functions:
		void        setClassName(char* ClassName);
		void        setDimensions(SDimensions Dimensions);
		void        setHandle(HWND Handle);
		void        setID(int32_t ID);
		void        setStyle(DWORD Style);
		void        addControl(SControl Control) noexcept;
	
};
