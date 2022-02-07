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
static HWND hLblInstructions;                   // HWND for lblInstructions
static HWND hLblTitle;                          // HWND for lblTitle
static HWND hLblArtist;                         // HWND for lblArtist
static HWND hLblAlbum;                          // HWND for lblAlbum
static HWND hLblYear;                           // HWND for lblYear
static HWND hLblTrack;                          // HWND for lblTrack
static HWND hLblComment;                        // HWND for lblComment
static HWND hLblAlbumArtist;                    // HWND for lblAlbumArtist
static HWND hLblGenre;                          // HWND for lblGenre
static HWND hLblComposer;                       // HWND for lblComposer
static HWND hLblDiscNumber;                     // HWND for lblDiscNumber

// Textboxes (EDIT):
static HWND hTxtTitle;                          // HWND for txtTitle
static HWND hTxtArtist;                         // HWND for txtArtist
static HWND hTxtAlbum;                          // HWND for txtAlbum
static HWND hTxtYear;                           // HWND for txtYear
static HWND hTxtTrack;                          // HWND for txtTrack
static HWND hTxtComment;                        // HWND for txtComment
static HWND hTxtAlbumArtist;                    // HWND for txtAlbumArtist
static HWND hTxtComposer;                       // HWND for txtComposer
static HWND hTxtDiscNumber;                     // HWND for txtDiscNumber

// Checkboxes (BUTTON):

// Group Boxes (BUTTON):

// ComboBoxes (COMBOBOX):
static HWND hDdlGenre;                          // HWND for ddlGenre

// Buttons (BUTTON):
static HWND hBtnSave;                           // HWND for btnSave
static HWND hBtnCancel;                         // HWND for btnCancel

// Static Images (STATIC):


/* ------------------------   CONTROL CLASS NAMES    ------------------------ */
// Labels (STATIC):
static CHAR lblInstructions[42]        = "Select the media type you wish to manage:";
static CHAR lblTitle[7]                = "Title:";
static CHAR lblArtist[8]               = "Artist:";
static CHAR lblAlbum[7]                = "Album:";
static CHAR lblYear[6]                 = "Year:";
static CHAR lblTrack[7]                = "Track:";
static CHAR lblComment[9]              = "Comment:";
static CHAR lblAlbumArtist[14]         = "Album Artist:";
static CHAR lblGenre[7]                = "Genre:";
static CHAR lblComposer[10]            = "Composer:";
static CHAR lblDiscNumber[13]          = "Disc Number:";

// Textboxes (EDIT):
static CHAR txtTitle[TEXTBOX_CLASS_SIZE];
static CHAR txtArtist[TEXTBOX_CLASS_SIZE];
static CHAR txtAlbum[TEXTBOX_CLASS_SIZE];
static CHAR txtYear[TEXTBOX_CLASS_SIZE];
static CHAR txtTrack[TEXTBOX_CLASS_SIZE];
static CHAR txtComment[TEXTBOX_CLASS_SIZE];
static CHAR txtAlbumArtist[TEXTBOX_CLASS_SIZE];
static CHAR txtGenre[TEXTBOX_CLASS_SIZE];
static CHAR txtComposer[TEXTBOX_CLASS_SIZE];
static CHAR txtDiscNumber[TEXTBOX_CLASS_SIZE];

// Checkboxes (BUTTON):

// Group Boxes (BUTTON):

// Combobox (COMBOBOX):
static CHAR ddlGenre[TEXTBOX_CLASS_SIZE];

// Buttons (BUTTON):
static CHAR btnSave[5]                 = "Save";
static CHAR btnCancel[7]               = "Cancel";

// Static Images (STATIC):


/* ************************** CONSTEXPR CONSTANTS *************************** */
// Labels (STATIC):
constexpr static INT ID_LBL_INSTRUCTIONS       = 1010i32;
constexpr static INT ID_LBL_TITLE              = 1011i32;
constexpr static INT ID_LBL_ARTIST             = 1012i32;
constexpr static INT ID_LBL_ALBUM              = 1013i32;
constexpr static INT ID_LBL_YEAR               = 1014i32;
constexpr static INT ID_LBL_TRACK              = 1015i32;
constexpr static INT ID_LBL_COMMENT            = 1016i32;
constexpr static INT ID_LBL_ALBUMARTIST        = 1017i32;
constexpr static INT ID_LBL_GENRE              = 1018i32;
constexpr static INT ID_LBL_COMPOSER           = 1019i32;
constexpr static INT ID_LBL_DISCNUMBER         = 1020i32;

// Textboxes (EDIT):
constexpr static INT ID_TXT_TITLE              = 1210i32;
constexpr static INT ID_TXT_ARTIST             = 1211i32;
constexpr static INT ID_TXT_ALBUM              = 1212i32;
constexpr static INT ID_TXT_YEAR               = 1213i32;
constexpr static INT ID_TXT_TRACK              = 1214i32;
constexpr static INT ID_TXT_COMMENT            = 1215i32;
constexpr static INT ID_TXT_ALBUMARTIST        = 1216i32;
constexpr static INT ID_TXT_GENRE              = 1217i32;
constexpr static INT ID_TXT_COMPOSER           = 1218i32;
constexpr static INT ID_TXT_DISCNUMBER         = 1219i32;

// Checkboxes (BUTTON):

// Group Boxes (BUTTON):

// Combobox (COMBOBOX):
constexpr static INT ID_DDL_GENRE              = 1410i32;

// Buttons (BUTTON):
constexpr static INT ID_BTN_SAVE               = 1610i32;
constexpr static INT ID_BTN_CANCEL             = 1611i32;

// Static Images (STATIC):
