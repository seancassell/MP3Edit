// SPDX-License-Identifier: GPL-2.0-only
// PROJECT NAME:  MP3Edit
// COPYRIGHT:     Copyright © 2022 Sean Cassell <sean.cassell@outlook.com>
// FILENAME:      FileDlgFactory.h
// FILE PURPOSE:  Defines several data types and structures, as well as the 
//                prototypes of functions that interact with a SQLite3 database.


/* ****************************** HEADER GUARD ****************************** */
#pragma once


/* **************************** INCLUDED HEADERS **************************** */
// C++17 STANDARD LIBRARY/STL HEADERS:
#include <string>
#include <vector>

// C RUNTIME COMPATIBILITY HEADERS:
#include <cinttypes>

// WINDOWS SDK HEADERS:
// For a list and description of child header files included by <Windows.h>, see
// the following entry on Wikipedia: https://en.wikipedia.org/wiki/Windows.h
#include <minwindef.h>// Basic Windows Type Definitions


/* ************************** FUNCTION PROTOTYPES *************************** */
std::string GetPosterFilename();
HRESULT     _WriteDataToFile(HANDLE hFile, PCWSTR pszDataIn);
PWSTR       BasicFileOpen();
