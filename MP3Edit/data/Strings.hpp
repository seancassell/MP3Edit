// SPDX-License-Identifier: GPL-2.0-only
// PROJECT NAME:  MP3Edit
// COPYRIGHT:     Copyright © 2022 Sean Cassell <sean.cassell@outlook.com>
// FILENAME:      Strings.hpp
// FILE PURPOSE:  Defines string constants that are used by the program.


/* ****************************** HEADER GUARD ****************************** */
#pragma once


/* **************************** INCLUDED HEADERS **************************** */
// C++17 STANDARD LIBRARY/STL HEADERS:
#include <string>
#include "../BuildNumber.h"


/* **************** IMPORTED NAMESPACES / NAMESPACE ALIASES ***************** */
using namespace std::string_literals; // Enable s-suffix for std::string litrl's


/* **************************** STRING CONSTANTS **************************** */
namespace str {
	
	// Program information;
	const std::string PROGRAM_NAME      = "MP3Edit"s;
	const std::string PROGRAM_VERSION   = "1.0.028.1"s;
	const std::string BUILD_NUMBER      = VAL_VER_BUILDNUM_S;
	const std::string PROGRAM_DESCRIPT  = 
		"Native Win32 GUI program to easily manage MP3s."s;
	const std::string PROGRAM_COPYRIGHT = 
		"Copyright (c) 2022 Sean Cassell <sean.cassell@outlook.com>"s;
	constexpr const char BUILT_ON[12]   = __DATE__;
	constexpr const char BUILT_AT[9]    = __TIME__;
	
}
