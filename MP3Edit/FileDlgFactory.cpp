// SPDX-License-Identifier: GPL-2.0-only
// PROJECT NAME:  MP3Edit
// COPYRIGHT:     Copyright © 2022 Sean Cassell <sean.cassell@outlook.com>
// FILENAME:      FileDlgFactory.cpp
// FILE PURPOSE:  Implements the class and functions that display a file select-
//                ion dialog. Adapted from the example program at:
// https://github.com/microsoft/Windows-classic-samples/tree/main/Samples/Win7Samples/winui/shell/appplatform/commonfiledialog


/* **************************** INCLUDED HEADERS **************************** */
#include <SDKDDKVer.h> // Master include file for versioning Windows SDK/DDK

// PROJECT-SPECIFIC HEADERS:
#include "FileDlgFactory.h"

// C++17 STANDARD LIBRARY/STL HEADERS:
#include <bitset>
#include <new>

// C RUNTIME COMPATIBILITY HEADERS:
#include <cstdio>
#include <cstdlib>

// WINDOWS SDK HEADERS:
// For a list and description of child header files included by <Windows.h>, see
// the following entry on Wikipedia: https://en.wikipedia.org/wiki/Windows.h
#include <Windows.h>  // Master include file for Windows applications
//#define STRICT_TYPED_ITEMIDS
#include <ShlObj.h>   // Used by Windows Controls (see: https://bit.ly/2BPtpXj)
#include <Objbase.h>  // Component object model definitions.
#include <ShObjIdl.h> // IFileDialogEvents and IFileDialogControlEvents
#include <Shlwapi.h>  // Interface for the Windows light-weight utility APIs
#include <KnownFolders.h> // KnownFolder APIs/datatypes/function headers
#include <propvarutil.h>  // PROPVAR-related functions
#include <propkey.h>  // Property key APIs/datatypes
#include <PropIdl.h>  // Property System APIs
#include <strsafe.h>  // Safer C library string functions
#include <shtypes.h>  // COMDLG_FILTERSPEC

// THIRD-PARTY LIBRARY HEADERS:
// fmt:
#include <fmt/format.hpp>


/* ******************** PREPROCESSOR DEFINITIONS/MACROS ********************* */
// Indices of file types:
#define INDEX_JPGIMG                              1
#define INDEX_PNGIMG                              2

// IDs for Task Dialog Buttons:
#define IDC_BASICFILEOPEN                       100
#define IDC_ADDITEMSTOCUSTOMPLACES              101
#define IDC_ADDCUSTOMCONTROLS                   102
#define IDC_SETDEFAULTVALUESFORPROPERTIES       103
#define IDC_WRITEPROPERTIESUSINGHANDLERS        104
#define IDC_WRITEPROPERTIESWITHOUTUSINGHANDLERS 105


/* ************************** CONSTEXPR CONSTANTS *************************** */
constexpr const COMDLG_FILTERSPEC c_rgSaveTypes[] = {
	{L"JPEG/JPG Image (*.jpg/*.jpeg)", L"*.jpg;*.jpeg"}, 
	{L"PNG Image (*.png)",             L"*.png"}, 
	{L"All Documents (*.*)",           L"*.*"}
};


/* ************************ STATIC GLOBAL VARIABLES ************************* */


/* *********************  CLASS DECLARATION/DEFINITION  ********************* */
// CLASS NAME:    CDialogEventHandler
// INHERITS:      public IFileDialogEvents, public IFileDialogControlEvents
// CLASS PURPOSE: File Dialog Event Handler
class CDialogEventHandler : public IFileDialogEvents, 
                            public IFileDialogControlEvents {
	
	public:
		// IUnknown methods:
		IFACEMETHODIMP QueryInterface(REFIID riid, void** ppv) {
			static const QITAB qit[] = {
				QITABENT(CDialogEventHandler, IFileDialogEvents), 
				QITABENT(CDialogEventHandler, IFileDialogControlEvents), 
				{ 0 }, 
#pragma warning(suppress:4838)
			};
			return QISearch(this, qit, riid, ppv);
		}
		
		IFACEMETHODIMP_(ULONG) AddRef() {
			return InterlockedIncrement(&_cRef);
		}
		
		IFACEMETHODIMP_(ULONG) Release() {
			long cRef = InterlockedDecrement(&_cRef);
			if (!cRef) {
				delete this;
			}
			return cRef;
		}
		
		// IFileDialogEvents methods
		IFACEMETHODIMP OnFileOk(IFileDialog*) {
			return S_OK;
		};
		IFACEMETHODIMP OnFolderChange(IFileDialog*) {
			return S_OK;
		};
		IFACEMETHODIMP OnFolderChanging(IFileDialog*, IShellItem*) {
			return S_OK;
		};
		IFACEMETHODIMP OnHelp(IFileDialog*) {
			return S_OK;
		};
		IFACEMETHODIMP OnSelectionChange(IFileDialog*) {
			return S_OK;
		};
		IFACEMETHODIMP OnShareViolation(IFileDialog*, IShellItem*, FDE_SHAREVIOLATION_RESPONSE*) {
			return S_OK;
		};
		IFACEMETHODIMP OnTypeChange(IFileDialog* pfd);
		IFACEMETHODIMP OnOverwrite(IFileDialog*, IShellItem*, FDE_OVERWRITE_RESPONSE*) {
			return S_OK;
		};
		
		// IFileDialogControlEvents methods
		IFACEMETHODIMP OnItemSelected(IFileDialogCustomize* pfdc, DWORD dwIDCtl, DWORD dwIDItem);
		IFACEMETHODIMP OnButtonClicked(IFileDialogCustomize*, DWORD) {
			return S_OK;
		};
		IFACEMETHODIMP OnCheckButtonToggled(IFileDialogCustomize*, DWORD, BOOL) {
			return S_OK;
		};
		IFACEMETHODIMP OnControlActivating(IFileDialogCustomize*, DWORD) {
			return S_OK;
		};
		
		CDialogEventHandler() : _cRef(1) {};
	
	private:
		~CDialogEventHandler() { };
		long _cRef;
	
};


// IFileDialogEvents methods
// NAME:    CDialogEventHandler::OnTypeChange(IFileDialog*)
// RETURNS: HRESULT
// PURPOSE: This method gets called when the file-type is changed (combo-box 
//          selection changes). For sample sake, let's react to this event by 
//          changing the properties show.
HRESULT CDialogEventHandler::OnTypeChange(IFileDialog* pfd) {
	IFileSaveDialog* pfsd;
	HRESULT          hr = pfd->QueryInterface(&pfsd);
	if (SUCCEEDED(hr)) {
		// Get the index of the current file-type:
		UINT uIndex;
		hr = pfsd->GetFileTypeIndex(&uIndex);
		if (SUCCEEDED(hr)) {
			IPropertyDescriptionList* pdl = nullptr;
			
			switch (uIndex) {
				case INDEX_JPGIMG:
					{
						// When .jpg is selected, let's ask for some arbitrary 
						// property, say Title:
						hr = PSGetPropertyDescriptionListFromString(L"prop:System.Title", 
																	IID_PPV_ARGS(&pdl));
						if (SUCCEEDED(hr)) {
							// FALSE as second param == do not show default properties.
							hr = pfsd->SetCollectedProperties(pdl, FALSE);
							pdl->Release();
						}
					}
					break;
				case INDEX_PNGIMG:
					{
						// When .png is selected, let's ask for some other 
						// arbitrary property, say Keywords:
						hr = PSGetPropertyDescriptionListFromString(L"prop:System.Keywords", 
																	IID_PPV_ARGS(&pdl));
						if (SUCCEEDED(hr)) {
							// FALSE as second param == do not show default properties.
							hr = pfsd->SetCollectedProperties(pdl, FALSE);
							pdl->Release();
						}
					}
					break;
			}
		}
		pfsd->Release();
	}
	return hr;
}


// IFileDialogControlEvents
// NAME:    CDialogEventHandler::OnItemSelected(IFileDialogCustomize*, DWORD, DWORD)
// RETURNS: HRESULT
// PURPOSE: This method gets called when an dialog control item selection 
//          happens (radio-button selection. etc). For sample sake, let's react 
//          to this event by changing the dialog title.
HRESULT CDialogEventHandler::OnItemSelected(IFileDialogCustomize* pfdc, 
											DWORD                 dwIDCtl, 
											DWORD                 dwIDItem) {
	IFileDialog* pfd = nullptr;
	HRESULT      hr  = pfdc->QueryInterface(&pfd);
	if (SUCCEEDED(hr)) {
		/* if (dwIDCtl == CONTROL_RADIOBUTTONLIST) {
			switch (dwIDItem) {
				case CONTROL_RADIOBUTTON1:
					hr = pfd->SetTitle(L"Longhorn Dialog");
					break;
				case CONTROL_RADIOBUTTON2:
					hr = pfd->SetTitle(L"Vista Dialog");
					break;
			}
		} */
		pfd->Release();
	}
	return hr;
}


// NAME:    CDialogEventHandler_CreateInstance(REFIID, void**)
// RETURNS: HRESULT
// PURPOSE: Instance creation helper.
HRESULT CDialogEventHandler_CreateInstance(REFIID riid, void** ppv) {
	*ppv = nullptr;
	CDialogEventHandler* pDialogEventHandler = new (std::nothrow) CDialogEventHandler();
	HRESULT hr = (pDialogEventHandler) ? (S_OK) : (E_OUTOFMEMORY);
	if (SUCCEEDED(hr)) {
		hr = pDialogEventHandler->QueryInterface(riid, ppv);
		pDialogEventHandler->Release();
	}
	return hr;
}


/* **************************** STATIC FUNCTIONS **************************** */
// NAME:    ConvertWideStringToNarrow(PWSTR)
// RETURNS: std::string
// PURPOSE: Converts a wide string to a narrow string, represented as an 
//          'std::string' ('std::basic_string<char>').
std::string ConvertWideStringToNarrow(PWSTR InputStr_) {
	std::string strNarrow = "Poster.png";
	// First, figure out our required buffer size:
	DWORD   cbData = WideCharToMultiByte(CP_ACP, 
										 0, 
		InputStr_,
										 -1, 
										 nullptr, 
										 0, 
										 nullptr, 
										 nullptr);
	HRESULT hr     = (cbData == 0) ? HRESULT_FROM_WIN32(GetLastError()) : S_OK;
	if (SUCCEEDED(hr)) {
		// Now allocate a buffer of the required size, and call 
		// 'WideCharToMultiByte()' again to do the actual conversion:
		char* pszData = new (std::nothrow) CHAR[cbData]();
		hr = pszData ? S_OK : E_OUTOFMEMORY;
		if (SUCCEEDED(hr)) {
			hr = WideCharToMultiByte(CP_ACP, 
									 0, 
				InputStr_,
									 -1, 
									 pszData, 
									 cbData, 
									 nullptr, 
									 nullptr) 
				? S_OK 
				: HRESULT_FROM_WIN32(GetLastError());
			if (SUCCEEDED(hr)) {
				strNarrow = pszData;
			}
			delete[] pszData;
		}
	}
	return strNarrow;
}


/* ************************** FUNCTION DEFINITIONS ************************** */
// NAME:    GetPosterFilename()
// RETURNS: std::string
// PURPOSE: 
std::string GetPosterFilename() {
	std::string strPosterFilename = "Poster.png";
	PWSTR       pszFilePath       = BasicFileOpen();
	strPosterFilename = ConvertWideStringToNarrow(pszFilePath);
	return strPosterFilename;
}


// NAME:    _WriteDataToFile(HANDLE, PCWSTR)
// RETURNS: HRESULT
// PURPOSE: Helper function that converts UNICODE data to ANSI and writes it to 
//          the given file. We write in ANSI format to make it easier to open 
//          the output file in Notepad.
HRESULT _WriteDataToFile(HANDLE hFile, PCWSTR pszDataIn) {
	// First, figure out our required buffer size:
	DWORD   cbData = WideCharToMultiByte(CP_ACP, 
										 0, 
										 pszDataIn, 
										 -1, 
										 nullptr, 
										 0, 
										 nullptr, 
										 nullptr);
	HRESULT hr     = (cbData == 0) ? HRESULT_FROM_WIN32(GetLastError()) : S_OK;
	if (SUCCEEDED(hr)) {
		// Now allocate a buffer of the required size, and call 
		// 'WideCharToMultiByte()' again to do the actual conversion:
		char* pszData = new (std::nothrow) CHAR[cbData]();
		hr = pszData ? S_OK : E_OUTOFMEMORY;
		if (SUCCEEDED(hr)) {
			hr = WideCharToMultiByte(CP_ACP, 
									 0, 
									 pszDataIn, 
									 -1, 
									 pszData, 
									 cbData, 
									 nullptr, 
									 nullptr) 
				? S_OK 
				: HRESULT_FROM_WIN32(GetLastError());
			if (SUCCEEDED(hr)) {
				DWORD dwBytesWritten = 0;
				hr = WriteFile(hFile, 
							   pszData, 
							   cbData - 1, 
							   &dwBytesWritten, 
							   nullptr) 
					? S_OK 
					: HRESULT_FROM_WIN32(GetLastError());
			}
			delete [] pszData;
		}
	}
	return hr;
}


// NAME:    BasicFileOpen()
// RETURNS: HRESULT
// PURPOSE: 
PWSTR BasicFileOpen() {
	// CoCreate the File Open Dialog object:
	PWSTR        pszFilePath = nullptr;
	IFileDialog* pfd = nullptr;
	HRESULT      hr  = CoCreateInstance(CLSID_FileOpenDialog, 
										nullptr, 
										CLSCTX_INPROC_SERVER, 
										IID_PPV_ARGS(&pfd));
	if (SUCCEEDED(hr)) {
		// Create an event handling object, and hook it up to the dialog:
		IFileDialogEvents* pfde = nullptr;
		hr = CDialogEventHandler_CreateInstance(IID_PPV_ARGS(&pfde));
		if (SUCCEEDED(hr)) {
			// Hook up the event handler:
			DWORD dwCookie;
			hr = pfd->Advise(pfde, &dwCookie);
			if (SUCCEEDED(hr)) {
				// Set the options on the dialog:
				DWORD dwFlags;
				
				// Before setting, always get the options first in order not to 
				// override existing options:
				hr = pfd->GetOptions(&dwFlags);
				if (SUCCEEDED(hr)) {
					// In this case, get shell items only for file system items:
					hr = pfd->SetOptions(dwFlags | FOS_FORCEFILESYSTEM);
					if (SUCCEEDED(hr)) {
						// Set the file types to display only. Notice that this 
						// is a 1-based array:
						hr = pfd->SetFileTypes(ARRAYSIZE(c_rgSaveTypes), c_rgSaveTypes);
						if (SUCCEEDED(hr)) {
							// Set the selected file type index to JPEG images 
							// for this example:
							hr = pfd->SetFileTypeIndex(INDEX_JPGIMG);
							if (SUCCEEDED(hr)) {
								// Set the default extension to be ".jpg" file:
								hr = pfd->SetDefaultExtension(L"jpg");
								if (SUCCEEDED(hr)) {
									// Show the dialog
									hr = pfd->Show(nullptr);
									if (SUCCEEDED(hr)) {
										// Obtain the result, once the user 
										// clicks the 'Open' button. The result 
										// is an IShellItem object:
										IShellItem* psiResult;
										hr = pfd->GetResult(&psiResult);
										if (SUCCEEDED(hr)) {
											hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
											if (SUCCEEDED(hr)) {
												/* TaskDialog(nullptr, 
														   nullptr, 
														   L"CommonFileDialogApp", 
														   pszFilePath, 
														   nullptr, 
														   TDCBF_OK_BUTTON, 
														   TD_INFORMATION_ICON, 
														   nullptr); */
												//CoTaskMemFree(pszFilePath);
											}
											psiResult->Release();
										}
									}
								}
							}
						}
					}
				}
				// Unhook the event handler:
				pfd->Unadvise(dwCookie);
			}
			pfde->Release();
		}
		pfd->Release();
	}
	return pszFilePath;
}
