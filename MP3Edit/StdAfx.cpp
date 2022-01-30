// SPDX-License-Identifier: GPL-2.0-only
// PROJECT NAME:  MP3Edit
// COPYRIGHT:     Copyright © 2022 Sean Cassell <sean.cassell@outlook.com>
// FILENAME:      StdAfx.cpp
// FILE PURPOSE:  This file is the central (typically the only) place where any 
//                .lib files are included in the project (e.g. Windows SDK). 
//                Other .lib files may/will be included automatically by the 
//                linker.


/* **************************** INCLUDED HEADERS **************************** */
#include "StdAfx.hpp"


/* ************************** IMPORTED .LIB FILES *************************** */
// The Windows Kit .lib files are located in:
// C:\Program Files (x86)\Windows Kits\10\Lib\10.0.xxxxx.0\um\x64\

#pragma comment(lib, "ComDlg32.Lib")
#pragma comment(lib, "ComCtl32.Lib")
#pragma comment(lib, "propsys.lib")
#pragma comment(lib, "ShLwApi.Lib")
#pragma comment(lib, "strsafe.lib")
#pragma comment(lib, "Uxtheme.lib")
