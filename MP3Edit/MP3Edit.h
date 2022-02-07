// SPDX-License-Identifier: GPL-2.0-only
// PROJECT NAME:  MP3Edit
// COPYRIGHT:     Copyright © 2022 Sean Cassell <sean.cassell@outlook.com>
// FILENAME:      MP3Edit.h
// FILE PURPOSE:  Declares the function prototypes, etc. that are used by the 
//                program.


/* ****************************** HEADER GUARD ****************************** */
#pragma once


/* **************************** INCLUDED HEADERS **************************** */
#include "StdAfx.hpp"


/* ************************** CONSTEXPR CONSTANTS *************************** */
constexpr const ULONG HEAP_TYPE_STANDARD{0ui32};
constexpr const ULONG HEAP_TYPE_LAL{1ui32};
constexpr const ULONG HEAP_TYPE_LFH{2ui32};


/* **************************** GLOBAL VARIABLES **************************** */
HINSTANCE    hInst;                         // Handle of current instance
HANDLE       hHeap;                         // Handle for a heap
CHAR         szTitle[MAX_LOADSTRING];       // Title bar text
CHAR         szWindowClass[MAX_LOADSTRING]; // Main window's class name
HFONT        hfSegoeUI;                     // Font for the window & controls
HWND         g_hWnd;                        // Global window handle
OPENFILENAMEA ofn;                          // Common dialog box structure
LPSTR        fname;                         // Stores the selected filename
CHAR         szFilePath[256];               // Buffer for file name
HANDLE       hfOpenFileDlg;                 // File handle


/* ************************** FUNCTION PROTOTYPES *************************** */
int     APIENTRY WinMain(_In_     HINSTANCE hInstance, 
						 _In_opt_ HINSTANCE hPrevInstance, 
						 _In_     LPSTR     lpCmdLine, 
						 _In_     int       nCmdShow);
ATOM             MyRegisterClass(HINSTANCE hInstance);
BOOL             InitInstance(HINSTANCE, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
INT     APIENTRY OnCreate(const HWND hWnd, CREATESTRUCT* cs);
INT_PTR CALLBACK AboutDialogProc(HWND, UINT, WPARAM, LPARAM);
VOID    APIENTRY ShowMsgBox(std::string& Title, std::string& Message);
VOID    APIENTRY ShowErrorMessage(std::string& ErrorDetails);
HFONT   APIENTRY ConfigWindowFont();
BOOL    APIENTRY EnableDialogTheme(HWND hWnd);
VOID    APIENTRY GetTextFromTextboxes();
string  APIENTRY GetWindowTitle() noexcept;
VOID    APIENTRY DisplayWin32ApiError(WORD, LPCSTR, const char*);
UINT    APIENTRY AddString(const HWND, const string&);
VOID    APIENTRY GetFilenameFromDlg(HWND&);
string  APIENTRY DeduceFilename(std::string&);
BOOL    APIENTRY DoesFileExist(std::string&);
