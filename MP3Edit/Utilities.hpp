// SPDX-License-Identifier: GPL-2.0-only
// PROJECT NAME:  MP3Edit
// COPYRIGHT:     Copyright © 2022 Sean Cassell <sean.cassell@outlook.com>
// FILENAME:      Utilities.hpp
// FILE PURPOSE:  Defines prototypes for the utilities functions.


/* ****************************** HEADER GUARD ****************************** */
#pragma once


/* **************************** INCLUDED HEADERS **************************** */
#include "StdAfx.hpp"


/* ************************** FUNCTION PROTOTYPES *************************** */
/* --------    File IO functions    -------- */
auto  IsValidFile(std::string& Filename)->bool;
auto  GetFileSizeInBytes(std::string& Filename)->size_t;
auto  ReadTextFile(std::string& Filename)->std::string;
auto  ReadBinaryFile(std::string& Filename)->std::byte*;
auto  WriteStringToFile(std::string& Filename, std::string& Text)->void;
extern "C" {
	void  CWriteTextFile(const char* Filename, const char* Text);
	char* CReadTextFile(const char* Filename);
}
auto  AppendTextToTextFile(std::string& Filename, std::string& NewText)->bool;
auto  DuplicateFile(std::string& OldFilename, std::string& NewFilename)->void;
auto  DuplicateFileV2(std::string& OldFilename, std::string& NewFilename)->void;
auto  ReadTextFileV2(std::string& Filename)->std::string;
auto  DeleteFileFromPath(std::string& Filename)->bool;
auto  CreateFolder(std::string& FolderName)->bool;
auto  GetListOfFilesInFolder(std::string& Directory)->std::vector<std::string>;
auto  RenameFileOrDir(std::string& OldName, std::string& NewName)->void;


/* --------    String/Text Parsing Functions (narrow)    -------- */
auto GenerateHorizontalRuler(size_t Length, char c_)->std::string;
auto WStringToString(std::wstring& _WideString)->std::string;
auto StringToWString(std::string&  _NarrowString)->std::wstring;
auto CslToVector(std::string& _InputList)->std::vector<std::string>;
auto CalcDJB2(const char* InputString, const size_t Length)->uint64_t;
auto ConvertTextToUpperCase(std::string& str)->std::string;
auto ConvertTextToLowerCase(std::string& str)->std::string;
auto ConvertTextToUpperCaseV2(std::string& InputString)->std::string;
auto ConvertTextToLowerCaseV2(std::string& InputString)->std::string;
auto UpdatePlaceholder(std::string& InputString, 
					   std::string& Placeholder, 
					   std::string& NewValue)->std::string;
auto CompareStrings(std::string& Str1, std::string& Str2)->bool;


/* --------    Other Utilitiy Functions    -------- */
auto PauseExecution(size_t Duration)->void;
auto GetRandomUInt64()->uint64_t;
auto GetDayOfYear()->uint32_t;
template <typename T> std::vector<unsigned char> VariableToBytes(T value);
auto GetSysEnvironmentVariable(std::string& EnvVar)->std::string;
auto getTimestamp() noexcept->std::string;


/* --------    String/Text Parsing Functions (wide)    -------- */
std::wstring ReadTextFileV2(std::wstring& Filename);
void         WriteStringToFile(std::wstring& Filename, std::wstring& Text);
bool         CompareStrings(std::wstring& Str1, std::wstring& Str2);
std::wstring UpdatePlaceholder(std::wstring& InputString, 
							   std::wstring& Placeholder, 
							   std::wstring& NewValue);
bool         IsValidFileW(std::wstring& Filename);

int UcToAnsi(wchar_t* pszUc, char* pszAnsi, int cch);
