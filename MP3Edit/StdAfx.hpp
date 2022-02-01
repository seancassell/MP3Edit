// SPDX-License-Identifier: GPL-2.0-only
// PROJECT NAME:  MP3Edit
// COPYRIGHT:     Copyright © 2022 Sean Cassell <sean.cassell@outlook.com>
// FILENAME:      StdAfx.hpp
// FILE PURPOSE:  Includes the headers, imports the namespaces, etc. that are 
//                used by the program.


/* ***************************** ENABLE THEMES ****************************** */
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


/* ****************************** HEADER GUARD ****************************** */
#pragma once


/* **************************** INCLUDED HEADERS **************************** */
// C++ STANDARD LIBRARY/STL HEADERS:
#include <algorithm>
#include <array>
#include <charconv>
#include <codecvt>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <locale> // std::locale, std::tolower, std::toupper
#include <memory>
#include <new>
#include <random>
#include <string>
#include <system_error>
#include <thread>
#include <utility>
#include <vector>

// C COMPATIBILITY HEADERS:
#include <cinttypes>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// COMPILER INTRINSICS HEADERS:
#include <intrin.h>

// WINDOWS SDK HEADERS:
// For a list and description of child header files included by <Windows.h>, see
// the following entry on Wikipedia: https://en.wikipedia.org/wiki/Windows.h
#include <Windows.h>  // Master include file for Windows applications
#include <CommCtrl.h> // Windows common controls
#include <windowsx.h> // Macro APIs, window message crackers, and control APIs
#include <Uxtheme.h>  // Theming API header
#include <tchar.h>    // Definitions for generic international text functions
#include <CommDlg.h>  // Defines the 32-Bit Common Dialog APIs
#include <cderr.h>    // CommDlgExtendedError function error codes
#include <Objbase.h>  // Component object model definitions.

// THIRD-PARTY LIBRARY HEADERS:
// fmt:
#include <fmt/format.hpp>

// id3v2lib:
#include <id3v2lib.h>

// UTF8 for C++:
#include <UTF8.hpp>

// Win32Handle:
#include <Win32Handle.h>

// PROJECT-SPECIFIC HEADERS:
#include "BuildInfo.h"
#include "FileDlgFactory.h"
#include "Utilities.hpp"
#include "data/Strings.hpp"
#include "genres/GenreList.hpp"
#include "GuiClasses/SMainWindow.hpp"
#include "res/Resources.h"


/* **************** IMPORTED NAMESPACES / NAMESPACE ALIASES ***************** */
namespace fs = std::filesystem;
using namespace std::string_literals; // Enable s-suffix for std::string litrl's
using namespace fmt::literals; // Enables use of the '_a' and '_format' literals


/* ******************** PREPROCESSOR DEFINITIONS/MACROS ********************* */
#define RC_MENU(x)       reinterpret_cast<HMENU>(x)
#define SHOW_MSG(x,y)    MessageBoxA(0, x, y, MB_OK | MB_ICONINFORMATION);


/* ************************** CONSTEXPR CONSTANTS *************************** */
constexpr static const size_t  MAX_LOADSTRING        =  100ui64;
constexpr static const INT     STARTUP_X_COORD       =    32i32;
constexpr static const INT     STARTUP_Y_COORD       =    32i32;
constexpr static const INT     CONTROL_SEPARATOR     =    16i32;
constexpr static const INT     LABEL_WIDTH           =   128i32;
constexpr static const INT     LABEL_HEIGHT          =    32i32;
constexpr static const INT     TEXTBOX_WIDTH         =   384i32;
constexpr static const INT     TEXTBOX_HEIGHT        =    32i32;
constexpr static const INT     DROPDOWN_WIDTH        =   384i32;
constexpr static const INT     DROPDOWN_HEIGHT       =    32i32;
constexpr static const INT     BUTTON_WIDTH_WIDE     =   160i32;
constexpr static const INT     BUTTON_WIDTH          =   100i32;
constexpr static const INT     BUTTON_WIDTH_NARROW   =    72i32;
constexpr static const INT     BUTTON_HEIGHT         =    32i32;
constexpr static const INT     IMAGE_WIDTH           =    32i32;
constexpr static const INT     IMAGE_HEIGHT          =    32i32;


/* ******************************* DATA TYPES ******************************* */
//typedef HRESULT (WINAPI * ETDTProc) (HWND, DWORD);
