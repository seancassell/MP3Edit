// SPDX-License-Identifier: GPL-2.0-only
// PROJECT NAME:  MP3Edit
// COPYRIGHT:     Copyright © 2021 Sean Cassell <sean.cassell@outlook.com>
// FILENAME:      MP3Edit.cpp
// FILE PURPOSE:  Contains the program entry point and some of the functions 
//                that control program operation.


/* **************************** INCLUDED HEADERS **************************** */
// PROJECT-SPECIFIC HEADERS:
#include "MP3Edit.h"
#include "ControlVars.h"
#include "GuiClasses/GetControlsVector.hpp"


/* ******************************* INTRINSICS ******************************* */
// Use the intrinsic forms of 'memcmp()', 'memcpy()', 'memmove()', 'memset()', 
// 'strcat()', 'strcmp()', 'strcpy()', and 'strlen()':
#pragma intrinsic(memcmp, memcpy, memmove, memset, strcat, strcmp, strcpy, strlen)


/* ************************** CONSTEXPR CONSTANTS *************************** */
constexpr static const size_t kCONTROL_VEC_SIZE = 23ui64;


/* ************************ STATIC GLOBAL VARIABLES ************************* */
// Window controls:
std::vector<SControl> g_Controls;

/* Text of Textboxes (EDIT): */
static std::string g_Title       = "placeholder"s;
static std::string g_Artist      = "placeholder"s;
static std::string g_Album       = "placeholder"s;
static std::string g_Year        = "placeholder"s;
static std::string g_Track       = "placeholder"s;
static std::string g_Comment     = "placeholder"s;
static std::string g_AlbumArtist = "placeholder"s;
static std::string g_Composer    = "placeholder"s;
static std::string g_DiscNumber  = "placeholder"s;

/* Text of ComboBoxes (COMBOBOX): */
static std::string g_Genre       = "placeholder"s;


/* **************************** STATIC FUNCTIONS **************************** */
//
//    FUNCTION: ConvertPixelsToDIPs(const size_t, HWND)
//    
//    RETURNS:  int32_t
//    
//    PURPOSE:  
//
auto inline ConvertPixelsToDIPs(const size_t Pixels, HWND hWnd)->int32_t {
	int32_t result_ = 0;
	__m128i temp;
	temp.m128i_u64[0] = Pixels;
	result_ = temp.m128i_i32[0];
	return result_;
}


/* ************************** FUNCTION DEFINITIONS ************************** */
//
//    FUNCTION: WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
//    
//    RETURNS:  int
//    
//    PURPOSE:  Program entry point.
//
int APIENTRY WinMain(_In_     HINSTANCE hInstance, 
					 _In_opt_ HINSTANCE hPrevInstance, 
					 _In_     LPSTR     lpCmdLine, 
					 _In_     int       nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	
	// Store instance handle in our global variable:
	hInst = hInstance;
	
	// Setup the program's heap:
	bool  bHeapCorruption;
	ULONG ulHeapInformation;
	
	// Enable heap terminate-on-corruption. 
	// A correct application can continue to run even if this call fails, 
	// so it is safe to ignore the return value. Call the function as follows:
	//  'HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0)'
	// Note that after a process enables this feature, it cannot be disabled.
	bHeapCorruption = HeapSetInformation(nullptr, 
										 HeapEnableTerminationOnCorruption, 
										 nullptr, 
										 0ui64);
	if (!bHeapCorruption) {
		// Enabling of heap terminate-on-corruption failed, so exit:
		static std::string msg1_ = 
			fmt::format("Error:\nFailed to enable heap terminate-on-corruption"
						" ({0})", 
						GetLastError());
		ShowErrorMessage(msg1_);
		std::exit(EXIT_FAILURE);
	}
	
	// Initialise the heap for the program:
	hHeap = HeapCreate(0, 0, 0);
	if (hHeap == nullptr) {
		// Heap initialisation failed, so exit:
		static std::string msg2_ = 
			fmt::format("Error:\nHeap initialisation failed ({0})", 
						GetLastError());
		ShowErrorMessage(msg2_);
		std::exit(EXIT_FAILURE);
	}
	
	// Enable the low-fragmentation heap (LFH). Starting with Windows Vista, 
	// the LFH is enabled by default but this call does not cause an error:
	ulHeapInformation = HEAP_TYPE_LFH;
	bHeapCorruption   = HeapSetInformation(hHeap, 
										   HeapCompatibilityInformation, 
										   &ulHeapInformation, 
										   sizeof(ulHeapInformation));
	if (!bHeapCorruption) {
		// Failed to enable the low-fragmentation heap, so exit:
		static std::string msg3_ = 
			fmt::format("Error:\nFailed to enable the low-fragmentation heap"
						" ({0})", 
						GetLastError());
		ShowErrorMessage(msg3_);
		std::exit(EXIT_FAILURE);
	}
	
	// Try to enable the use of the Windows dark theme:
	// Based off of the following StackOverflow answer, and the GitHub project, 
	// attempt to enable the dark Windows 10 theme for the window:
	//    - https://stackoverflow.com/a/53545935
	//    - https://github.com/ysc3839/win32-darkmode/blob/master/win32-darkmode/win32-darkmode.cpp
	//SetWindowTheme(hWnd, L"53545935", nullptr);
	//SendMessageA(hWnd, WM_THEMECHANGED, 0, 0);

	// Populate 'g_Controls':
	g_Controls = Utils::GetControlsVector();
	
	// Initialize Common Controls:
	INITCOMMONCONTROLSEX InitCtrlEx;
	InitCtrlEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
	InitCtrlEx.dwICC  = ICC_STANDARD_CLASSES|ICC_USEREX_CLASSES|ICC_LISTVIEW_CLASSES;
	BOOL ccinit       = InitCommonControlsEx(&InitCtrlEx);
	if (!ccinit) {
		// Call 'GetLastError()' to get the error code:
		int nResult = GetLastError();
		
		// Call 'ShowErrorMessage()' to display information about the error to 
		// the user:
		std::string ErrorDetails = fmt::format("Could not initialize common controls"
											   " (call to 'InitCommonControlsEx()'"
											   " failed; error code: {0})", 
											   nResult);
		ShowErrorMessage(ErrorDetails);
		
		// Don't exit; try to carry on and allow the application to attempt to 
		// work.
	}
	
	// Initialise global strings:
	LoadStringA(hInstance, IDS_APP_TITLE, szTitle,       MAX_LOADSTRING);
	LoadStringA(hInstance, IDC_MP3EDIT,   szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	
	// Perform application initialisation:
	if (!InitInstance(hInstance, nCmdShow)) {
		return FALSE;
	}
	MSG    msg;
	HACCEL hAccelTable = LoadAcceleratorsA(hInstance, 
										   MAKEINTRESOURCEA(IDC_MP3EDIT));
	
	// Main message loop:
	while (GetMessageA(&msg, nullptr, 0, 0)) {
		if (!TranslateAcceleratorA(msg.hwnd, hAccelTable, &msg)) {
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}
	
	// Destroy the heap:
	//  NOTE: The heap is destroyed in 'MainWndProc()' when the 'WM_DESTROY' is 
	//        handled. Calling it here causes an exception to be thrown.
	// HeapDestroy(hHeap);
	
	// Return the value of 'msg.wParam' (casted to an 'int'):
	return static_cast<int>(msg.wParam);
}


/* -------------------------------------------------------------------------- */


//
//    FUNCTION: MyRegisterClass(HINSTANCE)
//    
//    RETURNS:  ATOM
//    
//    PURPOSE:  Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance) {
	// Declare and initialise a 'WNDCLASSEXA' to store information about the 
	// 'wnd' class:
	WNDCLASSEXA wcex;
	SecureZeroMemory(&wcex, sizeof wcex);
	wcex.cbSize = sizeof(WNDCLASSEXA);
	
	// Create an 'HBRUSH' that will specify the window's background colour:
	COLORREF clrWhite  = RGB(255, 255, 255);
	HBRUSH   hbrWhite  = CreateSolidBrush(clrWhite);
	wcex.hbrBackground = hbrWhite;
	wcex.style         = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc   = MainWndProc;
	wcex.cbClsExtra    = 0i32;
	wcex.cbWndExtra    = 0i32;
	wcex.hInstance     = hInstance;
	
	// Use 'LoadImage' to load 'wnd' class icon and cursor as it supersedes the 
	// obsolete functions 'LoadIcon' and 'LoadCursor', although these functions 
	// will still work. Because the icon and cursor are loaded from system 
	// resources (i.e. they are shared), it is not necessary to free the image 
	// resources with either 'DestroyIcon' or 'DestroyCursor':
	wcex.hIcon         = LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_MP3EDIT));
	wcex.hIconSm       = LoadIconA(wcex.hInstance, MAKEINTRESOURCEA(IDI_MP3EDIT));
	wcex.hCursor       = LoadCursorA(nullptr, IDC_ARROW);
	wcex.lpszMenuName  = MAKEINTRESOURCEA(IDC_MP3EDIT);
	wcex.lpszClassName = szWindowClass;
	
	// Return the 'WNDCLASSEXA' that we just constructed to the calling function:
	return RegisterClassExA(&wcex);
}


/* -------------------------------------------------------------------------- */


//
//    FUNCTION: InitInstance(HINSTANCE, int)
//    
//    RETURNS:  BOOL
//    
//    PURPOSE:  Saves instance handle and creates main window
//    
//    COMMENTS:
//        
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
	// Store instance handle in our global variable:
	hInst = hInstance;
	
	// We need a 'HWND' variable, so declare it here while we figure out how to 
	// retrieve the value:
	//HWND tmp = GetActiveWindow();
	HWND tmp = g_hWnd;
	
	// 'g_WinXCoord', 'g_WinYCoord', 'MAIN_WINDOW_WIDTH', and 'MAIN_WINDOW_HEIGHT' all
	// define the number of physical pixels. Convert them to the number of 
	// device-independent pixels (DIPs) that they should be:
	int32_t dipWinXCoord = ConvertPixelsToDIPs(STARTUP_X_COORD,    tmp);
	int32_t dipWinYCoord = ConvertPixelsToDIPs(STARTUP_Y_COORD,    tmp);
	int32_t dipWinWidth  = ConvertPixelsToDIPs(MAIN_WINDOW_WIDTH,  tmp);
	int32_t dipWinHeight = ConvertPixelsToDIPs(MAIN_WINDOW_HEIGHT, tmp);
	int32_t WINDOW_HEIGHT_V3{
		(CONTROL_SEPARATOR * 6) 
		+ (LABEL_HEIGHT    * 4) 
		+ (TEXTBOX_HEIGHT  * 2)
	};
	int32_t dipWinHeightV3 = ConvertPixelsToDIPs(WINDOW_HEIGHT_V3, tmp);
	
	// Get the window's title 
	// (Title format: "[Program Name] [version] (build: [build])")
	std::string strWindowTitle = GetWindowTitle();
	//LPCSTR szWindowTitle = reinterpret_cast<LPCSTR>(strWindowTitle.c_str());
	LPCSTR szWindowTitle = strWindowTitle.c_str();
	
	// Note: 'WS_OVERLAPPEDWINDOW' was changed to:
	// 'WS_MINIMIZEBOX|WS_VISIBLE|WS_CAPTION|WS_BORDER|WS_SYSMENU'
	HWND hWnd;
	hWnd = CreateWindowA(szWindowClass, 
						 szWindowTitle, 
						 WS_MINIMIZEBOX|WS_VISIBLE|WS_CAPTION
							|WS_BORDER|WS_SYSMENU
							|WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN, 
						 dipWinXCoord, 
						 dipWinYCoord, 
						 dipWinWidth, 
						 dipWinHeightV3, 
						 nullptr, 
						 nullptr, 
						 hInstance, 
						 nullptr);
	if (!hWnd) {
		return FALSE;
	}
	
	// Set the text of the window's title bar:
	SetWindowTextA(hWnd, szWindowTitle);
	
	// Enable themes by trying to call 'EnableThemeDialogTexture()', if 
	// 'Uxtheme.dll' is present:
	BOOL bThemeEnabled = EnableDialogTheme(hWnd);
	
	// Show the main window:
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	return TRUE;
}


/* -------------------------------------------------------------------------- */


//
//    FUNCTION: MainWndProc(HWND, UINT, WPARAM, LPARAM)
//    
//    RETURNS:  LRESULT
//    
//    PURPOSE:  Processes messages for the main window.
//    
//    WM_CTLCOLORSTATIC - Make the label backgrounds transparent
//    WM_COMMAND        - Process the application menu
//    WM_PAINT          - Paint the main window
//    WM_DESTROY        - Post a quit message and return
//
LRESULT CALLBACK MainWndProc(HWND   hWnd, 
							 UINT   message, 
							 WPARAM wParam, 
							 LPARAM lParam) {
	// Set the value of 'g_hWnd':
	g_hWnd = hWnd;
	
	// Define colours and brushes for the window background and controls:
	COLORREF clrOldBkColour = RGB(  0,   0,   0);
	COLORREF clrBlack       = RGB(  0,   0,   0);
	COLORREF clrWhite       = RGB(255, 255, 255);
	COLORREF clrGray        = RGB(211, 211, 211);
	HBRUSH   hbrBlack       = CreateSolidBrush(clrBlack);
	HBRUSH   hbrWhite       = CreateSolidBrush(clrWhite);
	HBRUSH   hbrGray        = CreateSolidBrush(clrGray);
	static std::string MsgBoxTitle_ = "Button Clicked"s;
	switch (message) {
		case WM_CTLCOLORSTATIC:
			{
				// Change the background colour of the static controls to 
				// be transparent:
				// SEE: https://stackoverflow.com/a/4495814
				HWND hwLParam = reinterpret_cast<HWND>(lParam);
				if ((hLblInstructions == hwLParam) 
					|| (hLblTitle == hwLParam) 
					|| (hLblArtist == hwLParam) 
					|| (hLblAlbum == hwLParam) 
					|| (hLblYear == hwLParam) 
					|| (hLblTrack == hwLParam) 
					|| (hLblComment == hwLParam) 
					|| (hLblAlbumArtist == hwLParam) 
					|| (hLblGenre == hwLParam) 
					|| (hLblComposer == hwLParam) 
					|| (hLblDiscNumber == hwLParam)) {
						static HBRUSH hBrush    = CreateSolidBrush(clrWhite);
						static HDC    hdcStatic = reinterpret_cast<HDC>(wParam);
						SetTextColor(hdcStatic, clrBlack);
						SetBkMode(hdcStatic,    TRANSPARENT);
						return reinterpret_cast<INT_PTR>(hBrush);
					}
				}
				break;
		case WM_COMMAND:
			{
				// Parse the menu selections & button clicks:
				int wmId = LOWORD(wParam);
				switch (wmId) {
					case IDM_FILE_OPEN:
						break;
					case IDM_FILE_SAVE:
						break;
					case IDM_FILE_SAVEAS:
						break;
					case IDM_FILE_EXIT:
						//std::exit(EXIT_SUCCESS);
						DestroyWindow(hWnd);
						break;
					case IDM_SETTINGS:
						break;
					case IDM_HELP_HELP:
						break;
					case IDM_HELP_CHECKFORUPDATE:
						break;
					case IDM_HELP_ABOUT:
						{
							DialogBoxA(hInst, 
									   MAKEINTRESOURCEA(IDD_DLG_ABOUTBOX), 
									   hWnd, 
									   AboutDialogProc);
						}
						break;
					/* ---- Button clicks: ---- */
					/* case ID_BTN_SELECT_IMAGE:
						{
							// Handle the click event of 'btnSelectImage':
							btnSelectImageClick();
						}
						break; */
					default:
						return DefWindowProc(hWnd, message, wParam, lParam);
				}
			}
			break;
		case WM_CREATE:
			return OnCreate(hWnd, reinterpret_cast<CREATESTRUCT*>(lParam));
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				// TODO: Add any drawing code that uses hdc here...
				EndPaint(hWnd, &ps);
			}
			break;
		case WM_DESTROY:
			{
				// Release 'hfSegoeUI':
				DeleteObject(hfSegoeUI);
				// Destroy the heap:
				HeapDestroy(hHeap);
				// Call 'PostQuitMessage()':
				PostQuitMessage(EXIT_SUCCESS);
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


/* -------------------------------------------------------------------------- */


//
//    FUNCTION: OnCreate(const HWND, CREATESTRUCT*)
//    
//    RETURNS:  INT
//    
//    PURPOSE:  Helper function that adds the controls to the main window.
//
INT APIENTRY OnCreate(const HWND hWnd, CREATESTRUCT* cs) {
	// Set the font the window will use (Segoe UI, size 10):
	// Note - Refer to: - https://stackoverflow.com/a/225733
	//                  - https://stackoverflow.com/a/224457
	//HFONT hfSegoeUI = ConfigWindowFont();
	/* hfSegoeUI = CreateFontA(24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, 
							ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, 
							CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, 
							TEXT("Segoe UI")); */
	hfSegoeUI = ConfigWindowFont();
	SendMessageA(hWnd, WM_SETFONT, reinterpret_cast<WPARAM>(hfSegoeUI), TRUE);
	
	// Declare variables to hold the [X,Y] coordinates, the height & width, and  
	// various other values that are converted from physical pixels to device-
	// independent pixels:
	int32_t X_coord           = CONTROL_SEPARATOR;
	int32_t Y_coord           = CONTROL_SEPARATOR;
	int32_t dipXCoord         = ConvertPixelsToDIPs(X_coord,             hWnd);
	int32_t dipYCoord         = ConvertPixelsToDIPs(Y_coord,             hWnd);
	int32_t dipControlSep     = ConvertPixelsToDIPs(CONTROL_SEPARATOR,   hWnd);
	int32_t dipWindowWidth    = ConvertPixelsToDIPs(MAIN_WINDOW_WIDTH,   hWnd);
	int32_t dipWindowHeight   = ConvertPixelsToDIPs(MAIN_WINDOW_HEIGHT,  hWnd);
	int32_t dipLabelWidth     = ConvertPixelsToDIPs(LABEL_WIDTH,         hWnd);
	int32_t dipLabelHeight    = ConvertPixelsToDIPs(LABEL_HEIGHT,        hWnd);
	int32_t dipTextboxWidth   = ConvertPixelsToDIPs(TEXTBOX_WIDTH,       hWnd);
	int32_t dipTextboxHeight  = ConvertPixelsToDIPs(TEXTBOX_HEIGHT,      hWnd);
	int32_t dipComboBoxHeight = ConvertPixelsToDIPs(DROPDOWN_HEIGHT,     hWnd);
	int32_t dipComboBoxWidth  = ConvertPixelsToDIPs(DROPDOWN_WIDTH2,     hWnd);
	int32_t dipButtonWidthN   = ConvertPixelsToDIPs(BUTTON_WIDTH_NARROW, hWnd);
	int32_t dipButtonWidth    = ConvertPixelsToDIPs(BUTTON_WIDTH,        hWnd);
	int32_t dipButtonWidthW   = ConvertPixelsToDIPs(BUTTON_WIDTH_WIDE,   hWnd);
	int32_t dipButtonHeight   = ConvertPixelsToDIPs(BUTTON_HEIGHT,       hWnd);
	int32_t dipImageWidth     = ConvertPixelsToDIPs(IMAGE_WIDTH,         hWnd);
	int32_t dipImageHeight    = ConvertPixelsToDIPs(IMAGE_HEIGHT,        hWnd);
	
	// Define a lambda that will create a label ('STATIC'), one that will create
	// a textbox ('EDIT'), and one that will create a 'ComboBox' window control:
	auto lDrawButton = [&](LPSTR lpWindowName, INT X_, INT Y_, INT nWidth, 
						   INT   nHeight,      INT hID)->HWND {
		HWND hWndButton = CreateWindowA("BUTTON", 
										lpWindowName, 
										WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_TEXT|BS_FLAT,
										X_, 
										Y_, 
										nWidth, 
										nHeight, 
										hWnd, 
										RC_MENU(hID), 
										hInst, 
										nullptr);
		return hWndButton;
	};
	
	auto lDrawLabel = [&](LPSTR lpWindowName, INT X_, INT Y_, INT nWidth, 
						  INT   nHeight,      INT hID)->HWND {
		HWND hWndLabel = CreateWindowA("STATIC", 
									   nullptr, 
									   WS_EX_TRANSPARENT|WS_VISIBLE|WS_CHILD, 
									   X_, 
									   Y_, 
									   nWidth, 
									   nHeight, 
									   hWnd, 
									   RC_MENU(hID), 
									   hInst, 
									   nullptr);
		return hWndLabel;
	};
	
	auto lDrawTextbox = [&](LPSTR lpWindowName, INT X_, INT Y_, INT nWidth, 
							INT   nHeight,      INT hID)->HWND {
		HWND hWndTxtbx = CreateWindowA("EDIT", 
									   nullptr, 
									   WS_TABSTOP|WS_BORDER|WS_VISIBLE|WS_CHILD 
										|WS_VSCROLL|ES_LEFT|ES_MULTILINE
										|ES_AUTOVSCROLL|ES_READONLY, 
									   X_, 
									   Y_, 
									   nWidth, 
									   nHeight, 
									   hWnd, 
									   RC_MENU(hID), 
									   hInst, 
									   nullptr);
		return hWndTxtbx;
	};
	
	auto lDrawComboBox = [&](LPSTR lpWindowName, INT X_, INT Y_, INT nWidth, 
							 INT   nHeight,      INT hID)->HWND {
		HWND hWndCombo = CreateWindowA("ComboBox", 
									   lpWindowName, 
									   WS_CHILD|WS_TABSTOP|WS_VISIBLE|CBS_DROPDOWN, 
									   X_, 
									   Y_, 
									   nWidth, 
									   nHeight, 
									   hWnd, 
									   RC_MENU(hID), 
									   hInst, 
									   nullptr);
		return hWndCombo;
	};
	
	// Declare and initialise 7 'INT' variables that will hold the height (the 
	// 'Y' coordinate) of the labels and textboxes:
	constexpr static const size_t I32_ARRAY_SIZE = 11ui64;
	std::array<size_t, I32_ARRAY_SIZE> arrYCoords;
	arrYCoords.at(0)  = (dipYCoord);
	arrYCoords.at(1)  = (arrYCoords.at(0) + (dipLabelHeight));
	size_t t_ = 2ui64;
#pragma loop(hint_parallel(8))
	for (size_t i = 2ui64; i < I32_ARRAY_SIZE; ++i) {
		t_ = (i - 1ui64);
		arrYCoords.at(i)  = (arrYCoords.at(t_) + (dipTextboxHeight));
	}
	
	/*  ----------------    START OF DRAWING OF CONTROLS    ----------------  */
	// [1] Labels (STATIC):
	size_t LblInstructionsWidth    = (MAIN_WINDOW_WIDTH - (CONTROL_SEPARATOR * 2));
	size_t dipLblInstructionsWidth = ConvertPixelsToDIPs(LblInstructionsWidth, hWnd);
	hLblInstructions = lDrawLabel(lblInstructions, 
								  dipXCoord, 
								  arrYCoords.at(0), 
								  dipLblInstructionsWidth, 
								  dipLabelHeight, 
								  ID_LBL_INSTRUCTIONS);
	hLblTitle = lDrawLabel(lblTitle, 
								  dipXCoord, 
								  arrYCoords.at(1), 
								  dipLabelWidth, 
								  dipLabelHeight, 
								  ID_LBL_TITLE);
	hLblArtist = lDrawLabel(lblArtist, 
								  dipXCoord, 
								  arrYCoords.at(2), 
								  dipLabelWidth, 
								  dipLabelHeight, 
								  ID_LBL_ARTIST);
	hLblAlbum = lDrawLabel(lblAlbum, 
								  dipXCoord, 
								  arrYCoords.at(3), 
								  dipLabelWidth, 
								  dipLabelHeight, 
								  ID_LBL_ALBUM);
	hLblYear = lDrawLabel(lblYear, 
								  dipXCoord, 
								  arrYCoords.at(4), 
								  dipLabelWidth, 
								  dipLabelHeight, 
								  ID_LBL_YEAR);
	hLblTrack = lDrawLabel(lblTrack, 
								  dipXCoord, 
								  arrYCoords.at(5), 
								  dipLabelWidth, 
								  dipLabelHeight, 
								  ID_LBL_TRACK);
	hLblComment = lDrawLabel(lblComment, 
								  dipXCoord, 
								  arrYCoords.at(6), 
								  dipLabelWidth, 
								  dipLabelHeight, 
								  ID_LBL_COMMENT);
	hLblAlbumArtist = lDrawLabel(lblAlbumArtist, 
								  dipXCoord, 
								  arrYCoords.at(7), 
								  dipLabelWidth, 
								  dipLabelHeight, 
								  ID_LBL_ALBUMARTIST);
	hLblGenre = lDrawLabel(lblGenre, 
								  dipXCoord, 
								  arrYCoords.at(8), 
								  dipLabelWidth, 
								  dipLabelHeight, 
								  ID_LBL_GENRE);
	hLblComposer = lDrawLabel(lblComposer, 
								  dipXCoord, 
								  arrYCoords.at(9), 
								  dipLabelWidth, 
								  dipLabelHeight, 
								  ID_LBL_COMPOSER);
	hLblDiscNumber = lDrawLabel(lblDiscNumber, 
								  dipXCoord, 
								  arrYCoords.at(10), 
								  dipLabelWidth, 
								  dipLabelHeight, 
								  ID_LBL_DISCNUMBER);
	
	
	// [2] Textboxes (EDIT):
	/* hTxtSupported = lDrawTextbox(txtSupported,
								 dipXCoord, 
								 arrYCoords.at(4), 
								 dipTextboxWidth, 
								 dipTextboxHeight, 
								 ID_TXT_SUPPORTED);
	hTxtUnsupported = lDrawTextbox(txtUnsupported, 
								   dipXCoord, 
								   arrYCoords.at(6), 
								   dipTextboxWidth, 
								   dipTextboxHeight, 
								   ID_TXT_UNSUPPORTED); */
	
	// [3] Buttons (BUTTON):
	
	/*   ----------------    END OF DRAWING OF CONTROLS    ----------------   */
	/*  ----------------    START OF LOADING ICONS    ----------------  */
	/* HBITMAP iconAudiobooks{
		static_cast<HBITMAP>(::LoadImageA(::GetModuleHandleA(nullptr), 
										  MAKEINTRESOURCEA(IDB_BMP_AUDIOBOOK_32PX), 
										  IMAGE_BITMAP, 
										  32i32, 
										  32i32, 
										  0x0ui32))
	}; */
	/*  ----------------    END OF LOADING ICONS    ----------------  */
	
	// Set the text of the labels, textboxes, ComboBoxes, and buttons:
	/* Labels: */
	SetWindowTextA(hLblInstructions, lblInstructions);
	
	/* Textboxes: */
	/* SetWindowTextA(hTxtSupported,   txtSupported);
	SetWindowTextA(hTxtUnsupported, txtUnsupported); */
	
	/* Buttons: */
	
	// Make sure the controls are using the correct font:
	/* Labels: */
	SendMessageA(hLblInstructions, 
				 WM_SETFONT, 
				 reinterpret_cast<WPARAM>(hfSegoeUI), 
				 TRUE);
	
	/* Textboxes: */
	
	/* ComboBoxes: */
	
	/* Buttons: */
	
	// Set the icon on each button:
	/* ::SendMessageA(btnAudiobooks,  BM_SETIMAGE, IMAGE_ICON, (LPARAM)iconAudiobooks);
	::SendMessageA(btnMovies,      BM_SETIMAGE, IMAGE_ICON, (LPARAM)iconMovies);
	::SendMessageA(hBtnAudiobooks,  
				   BM_SETIMAGE, 
				   IMAGE_BITMAP, 
				   reinterpret_cast<LPARAM>(iconAudiobooks)); */
	
	// Based off of the following StackOverflow answer, attempt to enable the 
	// dark Windows 10 theme for the window:
	// https://stackoverflow.com/a/53545935
	/*   ----------------   START OF ENABLING DARK MODE    ----------------   */
	// Attempt to enable dark mode for the textboxes, ComboBoxes, and buttons:
	SetWindowTheme(hWnd,            L"DarkMode_Explorer", nullptr);
	
	/* Textboxes: */
	
	/* ComboBoxes: */
	/* Buttons: */
	
	/* Textboxes: */
	SendMessageA(hWnd,            WM_THEMECHANGED, 0, 0);
	
	/* ComboBoxes: */
	/* Buttons: */
	/*    ----------------    END OF ENABLING DARK MODE   ----------------    */
	
	// Return 0 to the calling function:
	return 0i32;
}


/* -------------------------------------------------------------------------- */


//
//    FUNCTION: AboutDialogProc(HWND, UINT, WPARAM, LPARAM)
//    
//    RETURNS:  INT_PTR
//    
//    PURPOSE:  Message handler for the "About" dialog box. Shown when the user 
//              clicks the "Help" menu, then "About CPUInfo" menu item.
//
INT_PTR CALLBACK AboutDialogProc(HWND   hDlg,   UINT   message, 
								 WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
		case WM_INITDIALOG:
			return static_cast<INT_PTR>(TRUE);
		case WM_COMMAND:
			if ((LOWORD(wParam) == IDOK) || (LOWORD(wParam) == IDCANCEL)) {
				EndDialog(hDlg, LOWORD(wParam));
				return static_cast<INT_PTR>(TRUE);
			}
			break;
	}
	return static_cast<INT_PTR>(FALSE);
}


/* -------------------------------------------------------------------------- */


//
//    FUNCTION: ShowMsgBox(std::string&, std::string&)
//    
//    RETURNS:  VOID
//    
//    PURPOSE:  Displays a 'MessageBox' with the specified title and message; 
//              the MessageBox has the 'Information' icon.
//
VOID APIENTRY ShowMsgBox(std::string& Title, std::string& Message) {
	LPCSTR szTitle = Title.c_str();
	LPCSTR szBody  = Message.c_str();
	MessageBoxA(0, szBody, szTitle, MB_OK|MB_ICONINFORMATION);
}


/* -------------------------------------------------------------------------- */


//
//    FUNCTION: ShowErrorMessage(std::string&)
//    
//    RETURNS:  VOID
//    
//    PURPOSE:  Displays a MessageBox with the 'exclamation mark' icon to 
//              provide information about an error.
//
VOID APIENTRY ShowErrorMessage(std::string& ErrorDetails) {
	MessageBoxA(0, ErrorDetails.c_str(), "Error", MB_OK|MB_ICONEXCLAMATION);
}


/* -------------------------------------------------------------------------- */


//
//    FUNCTION: ConfigWindowFont()
//    
//    RETURNS:  HFONT
//    
//    PURPOSE:  Configures the font for the window and its controls.
//    
//    COMMENTS: [To be added]
//
HFONT APIENTRY ConfigWindowFont() {
	INT    cHeight         =              -13i32;
	INT    cWidth          =                0i32;
	INT    cEscapement     =                0i32;
	INT    cOrientation    =                0i32;
	INT    cWeight         =           FW_NORMAL;
	DWORD  bItalic         =               FALSE;
	DWORD  bUnderline      =               FALSE;
	DWORD  bStrikeOut      =               FALSE;
	DWORD  iCharSet        =        ANSI_CHARSET;
	DWORD  iOutPrecision   =       OUT_TT_PRECIS;
	DWORD  iClipPrecision  = CLIP_DEFAULT_PRECIS;
	DWORD  iQuality        =   CLEARTYPE_QUALITY;
	DWORD  iPitchAndFamily =       TMPF_TRUETYPE;
	LPCSTR pszFaceName     =          "Segoe UI";
	HFONT  hfWindowFont    = CreateFontA(cHeight, 
										 cWidth, 
										 cEscapement, 
										 cOrientation, 
										 cWeight, 
										 bItalic, 
										 bUnderline, 
										 bStrikeOut, 
										 iCharSet, 
										 iOutPrecision, 
										 iClipPrecision, 
										 iQuality, 
										 iPitchAndFamily, 
										 pszFaceName);
	return hfWindowFont;
}


/* -------------------------------------------------------------------------- */


//
//    FUNCTION: EnableDialogTheme()
//    
//    RETURNS:  BOOL
//    
//    PURPOSE:  Attempts to enable to UI themes; requires 'Uxtheme.dll' to be 
//              available on the system. This function was adapted from:
//              [...]\Downloads\Programming\Wintellect\EnableDialogTheme.c
//    
//    COMMENTS: [To be added]
//
BOOL APIENTRY EnableDialogTheme(HWND hWnd) {
	HRESULT res1 = EnableThemeDialogTexture(hWnd, ETDT_ENABLEAEROWIZARDTAB);
	if (res1 == S_OK) {
		return TRUE;
	} else {
		return FALSE;
	}
}


/* -------------------------------------------------------------------------- */


//
//    FUNCTION: GetTextFromTextboxes()
//    
//    RETURNS:  VOID
//    
//    PURPOSE:  Retrieves the text from each textbox ('EDIT') and stores the 
//              text in the textbox's global 'std::string' variable.
//    
//    COMMENTS: [To be added]
//
VOID APIENTRY GetTextFromTextboxes() {
	// TODO: Implement this function.
}


/* -------------------------------------------------------------------------- */


//
//    FUNCTION: GetWindowTitle()
//    
//    RETURNS:  string (std::string)
//    
//    PURPOSE:  Generates the title of the window. Called by the window's 
//              'WndProc_*()' function.
//    
//    COMMENTS: [To be added]
//
string APIENTRY GetWindowTitle() noexcept {
	std::string strProgramTitle(str::PROGRAM_NAME);
	std::string strProgramVersion(str::PROGRAM_VERSION);
	const char* bn1 = reinterpret_cast<const char*>(VAL_VER_BUILDNUM_S);
	std::string strProgramBuildNum(bn1);
	std::string strWindowTitle{
		fmt::format("{0} - Version {1} (build {2})", 
					strProgramTitle, 
					strProgramVersion, 
					strProgramBuildNum)
	};
	//LPCSTR szWindowTitle = reinterpret_cast<LPCSTR>(strWindowTitle.c_str());
	return strWindowTitle;
}


/* -------------------------------------------------------------------------- */


//
//    FUNCTION: ()
//    
//    RETURNS:  
//    
//    PURPOSE:  [To be added]
//    
//    COMMENTS: [To be added]
//
VOID APIENTRY DisplayWin32ApiError(WORD wLine, LPSTR lpszFile, const char* routineName) {
	DWORD errorCode  = GetLastError();
	char* lpvMessage = nullptr;
	DWORD dwError;
	TCHAR szBuffer[256];
	dwError = FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM
								|FORMAT_MESSAGE_ALLOCATE_BUFFER
								|FORMAT_MESSAGE_IGNORE_INSERTS, 
							 nullptr, 
							 errorCode, 
							 MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_CAN), 
							 reinterpret_cast<LPTSTR>(&lpvMessage), 
							 0, 
							 nullptr);
	
	// Check to see if an error occurred calling FormatMessage()
	if (dwError == 0) {
		_sntprintf_s(szBuffer, 
					 _countof(szBuffer), 
					 _TRUNCATE, 
					 TEXT("An error occurred calling 'FormatMessageA()'; ")
						TEXT("Error Code %d"), 
					 GetLastError());
		MessageBoxA(nullptr, 
					szBuffer, 
					TEXT("Generic"), 
					MB_ICONSTOP|MB_ICONEXCLAMATION);
		return;
	}
	//fwprintf(stderr, L"Error code %i returned from %S.\n%s\n", errorCode, routineName, lpvMessage);
	
	// Display the error information along with where the error happened:
	_sntprintf_s(szBuffer, 
				 _countof(szBuffer), 
				 _TRUNCATE, 
				 TEXT("Generic, Line=%d, File=%s"), 
				 wLine, 
				 lpszFile);
	MessageBox(nullptr, lpvMessage, szBuffer, MB_ICONEXCLAMATION|MB_OK);
	LocalFree(lpvMessage);
}


/* -------------------------------------------------------------------------- */


//
//    FUNCTION: AddString(const HWND, const string&)
//    
//    RETURNS:  UINT
//    
//    PURPOSE:  [To be added]
//    
//    COMMENTS: [To be added]
//
UINT APIENTRY AddString(const HWND hCombo, const string& s) {
	return static_cast<UINT>(SendMessage(hCombo, 
										 CB_ADDSTRING, 
										 0, 
										 reinterpret_cast<LPARAM>(s.c_str())));
}


/* -------------------------------------------------------------------------- */


//
//    FUNCTION: GetFilenameFromDlg(HWND&)
//    
//    RETURNS:  VOID
//    
//    PURPOSE:  [To be added]
//    
//    COMMENTS: [To be added]
//
// Displays a common dialog to get a filename:
// SOURCE: https://msdn.microsoft.com/en-us/library/windows/desktop/ms646829(v=vs.85).aspx#open_file
VOID APIENTRY GetFilenameFromDlg(HWND& hWnd) {
	try {
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = hWnd;
		ofn.lpstrFile = szFilePath;
		
		// Set lpstrFile[0] to '\0' so that GetOpenFileName does not
		// use the contents of szFile to initialize itself:
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof(szFilePath);
		ofn.lpstrFilter = "All\0*.*\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		
		// Display the Open dialog box:
		if (GetOpenFileNameA(&ofn) == TRUE) {
			hfOpenFileDlg = CreateFileA(ofn.lpstrFilter,
										GENERIC_READ,
										0,
										(LPSECURITY_ATTRIBUTES) NULL,
										OPEN_EXISTING,
										FILE_ATTRIBUTE_NORMAL,
										(HANDLE) NULL);
			
			// Save the selected filename in the global variable 'fname':
			fname = ofn.lpstrFile;
		}
	} catch (const std::system_error &sys_err1) {
		const std::string part_1 = "Caught system_error with code: ";
		const std::string part_2 = "Meaning: ";
		const std::string part_3 = "The program will now exit.";
		const std::string err_num = std::to_string(sys_err1.code().value());
		const std::string err_msg = sys_err1.what();
		std::string prompt = part_1 + err_num + "\n\n" + part_2 + err_msg + "\n\n" + part_3;
		MessageBoxA(hWnd, prompt.c_str(), "Exception Encountered", MB_OK | MB_ICONERROR);
	} catch (const std::exception &excpnt1) {
		const std::string part_1 = "Caught exception: ";
		const std::string part_2 = "The program will now exit.";
		const std::string err_msg = excpnt1.what();
		const std::string prompt = part_1 + err_msg + "\n\n" + part_2;
		MessageBoxA(hWnd, prompt.c_str(), "Exception Encountered", MB_OK | MB_ICONERROR);
	}
}


/* -------------------------------------------------------------------------- */


//
//    FUNCTION: DeduceFilename(std::string&)
//    
//    RETURNS:  string (std::string)
//    
//    PURPOSE:  Isolates the filename from the full path.
//    
//    COMMENTS: [To be added]
//
string APIENTRY DeduceFilename(std::string& str) {
	fs::path _path(str);
	return _path.filename().string();
}


/* -------------------------------------------------------------------------- */


//
//    FUNCTION: DoesFileExist(std::string&)
//    
//    RETURNS:  BOOL
//    
//    PURPOSE:  Checks to see if the specified filename exists.
//    
//    COMMENTS: [To be added]
//
BOOL APIENTRY DoesFileExist(std::string& target) {
	fs::path _path(target);
	if (fs::exists(_path) && fs::is_regular_file(_path)) {
		return true;
	} else {
		return false;
	}
}
