// SPDX-License-Identifier: GPL-2.0-only
// PROJECT NAME:  MP3Edit
// COPYRIGHT:     Copyright © 2022 Sean Cassell <sean.cassell@outlook.com>
// FILENAME:      ControlVars.h
// FILE PURPOSE:  Defines the unique control ID numbers, the class names, and 
//                the handles for each control. Detailed information and practi-
//                cal usage examples can be found at:
//                https://zetcode.com/gui/winapi/controls/


/* ****************************** HEADER GUARD ****************************** */
#pragma once


/* **************************** INCLUDED HEADERS **************************** */
#include <windef.h>   // Basic Windows Type Definitions


/* ************************ PREPROCESSOR DEFINITIONS ************************ */
#define TEXTBOX_CLASS_SIZE 255


/* **************************** GLOBAL VARIABLES **************************** */
/*   ------------------------   CONTROL HANDLES    ------------------------   */
// Labels (STATIC):
HWND hLblInstructions;                   // HWND for lblInstructions
HWND hLblTitle;                          // HWND for lblTitle
HWND hLblArtist;                         // HWND for lblArtist
HWND hLblAlbum;                          // HWND for lblAlbum
HWND hLblYear;                           // HWND for lblYear
HWND hLblTrack;                          // HWND for lblTrack
HWND hLblComment;                        // HWND for lblComment
HWND hLblAlbumArtist;                    // HWND for lblAlbumArtist
HWND hLblGenre;                          // HWND for lblGenre
HWND hLblComposer;                       // HWND for lblComposer
HWND hLblDiscNumber;                     // HWND for lblDiscNumber

// Textboxes (EDIT):
HWND hTxtTitle;                          // HWND for txtTitle
HWND hTxtArtist;                         // HWND for txtArtist
HWND hTxtAlbum;                          // HWND for txtAlbum
HWND hTxtYear;                           // HWND for txtYear
HWND hTxtTrack;                          // HWND for txtTrack
HWND hTxtComment;                        // HWND for txtComment
HWND hTxtAlbumArtist;                    // HWND for txtAlbumArtist
HWND hTxtComposer;                       // HWND for txtComposer
HWND hTxtDiscNumber;                     // HWND for txtDiscNumber

// Checkboxes (BUTTON):

// Group Boxes (BUTTON):

// ComboBoxes (COMBOBOX):
HWND hDdlGenre;                          // HWND for ddlGenre

// Buttons (BUTTON):
HWND hBtnSave;                           // HWND for btnSave
HWND hBtnCancel;                         // HWND for btnCancel

// Static Images (STATIC):


/* ------------------------   CONTROL CLASS NAMES    ------------------------ */
// Labels (STATIC):
CHAR lblInstructions[42]        = "Select the media type you wish to manage:";
CHAR lblTitle[7]                = "Title:";
CHAR lblArtist[8]               = "Artist:";
CHAR lblAlbum[7]                = "Album:";
CHAR lblYear[6]                 = "Year:";
CHAR lblTrack[7]                = "Track:";
CHAR lblComment[9]              = "Comment:";
CHAR lblAlbumArtist[14]         = "Album Artist:";
CHAR lblGenre[7]                = "Genre:";
CHAR lblComposer[10]            = "Composer:";
CHAR lblDiscNumber[13]          = "Disc Number:";

// Textboxes (EDIT):
CHAR txtTitle[TEXTBOX_CLASS_SIZE];
CHAR txtArtist[TEXTBOX_CLASS_SIZE];
CHAR txtAlbum[TEXTBOX_CLASS_SIZE];
CHAR txtYear[TEXTBOX_CLASS_SIZE];
CHAR txtTrack[TEXTBOX_CLASS_SIZE];
CHAR txtComment[TEXTBOX_CLASS_SIZE];
CHAR txtAlbumArtist[TEXTBOX_CLASS_SIZE];
CHAR txtGenre[TEXTBOX_CLASS_SIZE];
CHAR txtComposer[TEXTBOX_CLASS_SIZE];
CHAR txtDiscNumber[TEXTBOX_CLASS_SIZE];

// Checkboxes (BUTTON):

// Group Boxes (BUTTON):

// Combobox (COMBOBOX):
CHAR ddlGenre[TEXTBOX_CLASS_SIZE];

// Buttons (BUTTON):
CHAR btnSave[5]                 = "Save";
CHAR btnCancel[7]               = "Cancel";

// Static Images (STATIC):


/* ************************** CONSTEXPR CONSTANTS *************************** */
// Labels (STATIC):
constexpr INT ID_LBL_INSTRUCTIONS       = 1010i32;
constexpr INT ID_LBL_TITLE              = 1011i32;
constexpr INT ID_LBL_ARTIST             = 1012i32;
constexpr INT ID_LBL_ALBUM              = 1013i32;
constexpr INT ID_LBL_YEAR               = 1014i32;
constexpr INT ID_LBL_TRACK              = 1015i32;
constexpr INT ID_LBL_COMMENT            = 1016i32;
constexpr INT ID_LBL_ALBUMARTIST        = 1017i32;
constexpr INT ID_LBL_GENRE              = 1018i32;
constexpr INT ID_LBL_COMPOSER           = 1019i32;
constexpr INT ID_LBL_DISCNUMBER         = 1020i32;

// Textboxes (EDIT):
constexpr INT ID_TXT_TITLE              = 1210i32;
constexpr INT ID_TXT_ARTIST             = 1211i32;
constexpr INT ID_TXT_ALBUM              = 1212i32;
constexpr INT ID_TXT_YEAR               = 1213i32;
constexpr INT ID_TXT_TRACK              = 1214i32;
constexpr INT ID_TXT_COMMENT            = 1215i32;
constexpr INT ID_TXT_ALBUMARTIST        = 1216i32;
constexpr INT ID_TXT_GENRE              = 1217i32;
constexpr INT ID_TXT_COMPOSER           = 1218i32;
constexpr INT ID_TXT_DISCNUMBER         = 1219i32;

// Checkboxes (BUTTON):

// Group Boxes (BUTTON):

// Combobox (COMBOBOX):
constexpr INT ID_DDL_GENRE              = 1410i32;

// Buttons (BUTTON):
constexpr INT ID_BTN_SAVE               = 1610i32;
constexpr INT ID_BTN_CANCEL             = 1611i32;

// Static Images (STATIC):
