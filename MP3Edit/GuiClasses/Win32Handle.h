/* ****************************** HEADER GUARD ****************************** */
#pragma once
#ifndef WIN32HANDLE_H
#define WIN32HANDLE_H


/* **************************** INCLUDED HEADERS **************************** */
#include <sdkddkver.h> // Master include file for versioning windows SDK/DDK
#include <Windows.h>  // Master include file for Windows applications
#include <tchar.h>    // Definitions for generic international text functions


/* *********************  CLASS DECLARATION/DEFINITION  ********************* */
class Win32Handle {
	
	public:
		Win32Handle() : m_Handle(nullptr) {}
		
		~Win32Handle() {
			if (m_Handle != nullptr) {
				CloseHandle(m_Handle);
			}
			m_Handle = nullptr;
		}
		
		void set(HANDLE _Handle) {
			m_Handle = _Handle;
		}
		
		HANDLE get() {
			return m_Handle;
		}
	
	private:
		HANDLE m_Handle;
	
};


#endif  //!WIN32HANDLE_H
