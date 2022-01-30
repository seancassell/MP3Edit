// SPDX-License-Identifier: GPL-2.0-only
// PROJECT NAME:  MP3Edit
// COPYRIGHT:     Copyright © 2022 Sean Cassell <sean.cassell@outlook.com>
// FILENAME:      Utilities.cpp
// FILE PURPOSE:  Implements the definitions of the utilities functions.


/* **************************** INCLUDED HEADERS **************************** */
#include "Utilities.hpp"
#include <iostream>

// THIRD-PARTY LIBRARY HEADERS:
// Boost.Algorithm:
#include <boost/algorithm/string.hpp>


/* **************************** STATIC FUNCTIONS **************************** */
// NAME:    PrintError
// PURPOSE: Prints information about an error to the console in red text. This 
//          function is intended for user-facing error information, not for 
//          developmer-facing error information (for that purpose, use 
//          'PrintDebugError()').
auto static inline PrintErrorMsg(std::string& msg_)->void {
	// Print the error message in bold red text:
	//fmt::print(fmt::emphasis::bold | fg(fmt::color::red), 
	//		   "Error: {0}\n", 
	//		   msg_);
}


/* ************************** FUNCTION DEFINITIONS ************************** */
/* --------    File IO functions     -------- */
// FUNCTION:    IsValidFile
// DESCRIPTION: Verifies that the file named 'Filename' exists and is a regular 
//              file. Returns 'false' if either test fails, and 'true' if both 
//              pass.
auto IsValidFile(std::string& Filename)->bool {
	// Check if the file/path exists:
	fs::path _path(Filename);
	if (fs::exists(_path) == false) {
		// Error - The specified file does not exist:
		std::string msg_ = fmt::format("The specified file (\"{0}\") "
									   " does not exist.", 
									   Filename);
		// std::cerr << "Error: " << msg_ << std::endl;
		PrintErrorMsg(msg_);
		return false;
	}
	
	// Verify that the path points to a regular file and not a directory or 
	// something else:
	if (fs::is_regular_file(_path) == false) {
		// Error - The path exists, but it does not point to a regular file:
		std::string msg_ = fmt::format("The specified path to \"{0}\" "
									   "exists, but it does not point "
									   "to a regular file.", 
									   Filename);
		// std::cerr << "Error: " << msg_ << std::endl;
		PrintErrorMsg(msg_);
		return false;
	}
	
	// If we have gotten to this point without an error or anything else, we can
	// assume the file is valid (i.e. the path exists and it points to a regular
	// file). Therefore, we return 'true' to the calling function:
	return true;
}


// FUNCTION:    GetFileSizeInBytes
// DESCRIPTION: Uses the 'std::filesystem::file_size' function to get the size 
//              of a file in bytes. Returns the value as a 'size_t'.
auto GetFileSizeInBytes(std::string& Filename)->size_t {
	size_t fileSizeInBytes = fs::file_size(Filename);
	return fileSizeInBytes;
}


// FUNCTION:    ReadTextFile
// DESCRIPTION: Reads a text file into an 'std::string' variable. This method 
//              was adapted from "method C++" from the following URL:
//        http://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html
auto ReadTextFile(std::string& Filename)->std::string {
	std::ifstream in(Filename, std::ios::in);
	if (in) {
		std::size_t fileSizeInBytes = GetFileSizeInBytes(Filename);
		std::string contents;
		contents.resize(fileSizeInBytes);
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	} else {
		std::string msg_ = fmt::format("Could not open \"{0}\".\n", Filename);
		// std::cerr << "Error: " << msg_ << std::endl;
		PrintErrorMsg(msg_);
		return msg_;
	}
	throw(errno);
}


// FUNCTION:    ReadBinaryFile
// DESCRIPTION: Reads a binary file into an array of type 'std::byte'. This 
//              method was adapted from "method C++" from the following URL:
//        http://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html
auto ReadBinaryFile(std::string& Filename)->std::byte* {
	std::ifstream in(Filename, std::ios::in | std::ios::binary);
	if (in) {
		size_t FileSize = GetFileSizeInBytes(Filename);
		char*  contents = new char[FileSize]();
		if (contents == nullptr) {
			throw std::exception("Heap allocation returned nullptr");
		}
		in.seekg(0, std::ios::beg);
		in.read(contents, FileSize);
		in.close();
		return reinterpret_cast<std::byte*>(contents);
	}
	throw(errno);
}


// FUNCTION:    WriteStringToFile
// DESCRIPTION: Writes the value of 'Text' to a text file named 'Filename'.
auto WriteStringToFile(std::string& Filename, std::string& Text)->void {
	std::ofstream ofsOutput;
	ofsOutput.open(Filename, std::ios::out);
	if (!ofsOutput.is_open()) {
		std::string msg_ = fmt::format("Could not open \"{0}\".\n", Filename);
		// std::cerr << "Error: " << msg_ << std::endl;
		PrintErrorMsg(msg_);
		return;
	}
	ofsOutput.write(Text.c_str(), Text.length());
	ofsOutput.flush();
	ofsOutput.close();
}


// FUNCTION:    CWriteTextFile
// DESCRIPTION: Write a text file using the C API. This function was adapted 
//              from: https://stackoverflow.com/a/14002993
void CWriteTextFile(const char* Filename, const char* Text) {
	// Open the file for writing:
	FILE* fOut = fopen(Filename, "w");
	
	// Calculate the number of bytes that are expected to be written:
	const size_t expected_ = (sizeof(Text) / sizeof(Text[0]));
	
	// Write to the file, and get the actual number of bytes that were written:
	const size_t actual_   = fwrite(Text, sizeof Text[0], expected_, fOut);
	
	// Check to see if the expected number of bytes to be written matches the 
	// number of bytes that were actually written:
	if (expected_ != actual_) {
		printf("Expected to write %llu bytes, but %llu bytes were written.\n", 
			   expected_, 
			   actual_);
	}
	
	// Close the file:
	fclose(fOut);
}


// FUNCTION:    CReadTextFile
// DESCRIPTION: Read from a text file using the C API. This function was adapted 
//              from: https://stackoverflow.com/a/14002993
char* CReadTextFile(const char* Filename) {
	// Open the file for reading:
	FILE* fIn   = fopen(Filename, "r");
	
	// Determine the file's size so that we know how much memory to allocate:
	fseek(fIn, 0, SEEK_END);
	size_t fSize = ftell(fIn);
	fseek(fIn, 0, SEEK_SET);  /* same as "rewind(fIn);" */
	
	// Allocate memory for the buffer and verify the allocation succeeded:
	char* fBuffer = (char*) malloc(fSize + 1ui64);
	if (fBuffer == NULL) {
		// Error: The attempt to allocate memory failed.
		printf("Attempt to allocate %llu bytes for a buffer failed.\n", 
			   (fSize + 1ui64));
		return NULL;
	}
	
	// Read the file into the buffer:
	fread(fBuffer, fSize, 1ui64, fIn);
	
	// Close the file:
	fclose(fIn);
	
	// Ensure that the buffer is NULL-terminated:
	fBuffer[fSize] = '\0';
	
	// Return the file contents ('fBuffer') to the calling function:
	return fBuffer;
}


// FUNCTION:    AppendTextToTextFile
// DESCRIPTION: Appends 'NewText' to the end of an existing text file 
//              ('Filename').
auto AppendTextToTextFile(std::string& Filename, std::string& NewText)->bool {
	std::ofstream ofsOutput;
	ofsOutput.open(Filename, std::ios::out | std::ios::app);
	if (!ofsOutput.is_open()) {
		std::string msg_ = fmt::format("Could not open '{0}' for writing.", 
									   Filename);
		PrintErrorMsg(msg_);
		throw new std::runtime_error(msg_);
		return false;
	}
	ofsOutput.write(NewText.c_str(), NewText.length());
	ofsOutput << NewText;
	ofsOutput.flush();
	ofsOutput.close();
	return true;
}


// FUNCTION:    DuplicateFile
// DESCRIPTION: Make an identical copy of 'OldFilename' named 'NewFilename'.
void DuplicateFile(std::string& OldFilename, std::string& NewFilename) {
	// Duplicate a file:
	/*
	ifstream in(inputFile, ios::binary);
	ofstream out(outputFile, ios::binary);
	if(in.is_open() && out.is_open()) {
		while(!in.eof()) {
			out.put(in.get());
		}
	}
	in.close();
	out.close();
	*/
	
	// Same thing in one line:
	std::ofstream(NewFilename) << std::ifstream(OldFilename).rdbuf();
}


// FUNCTION:    DuplicateFileV2
// DESCRIPTION: Make an identical copy of 'OldFilename' named 'NewFilename'.
auto DuplicateFileV2(std::string& OldFilename, std::string& NewFilename)->void {
	fs::path InputFilePath(OldFilename);
	fs::path OutputFilePath(NewFilename);
	fs::copy(InputFilePath, OutputFilePath);
}


// FUNCTION:    ReadTextFileV2
// DESCRIPTION: Using the C++ API, reads a text file into an 'std::string'. 
//              Based off of: https://stackoverflow.com/a/2602060/8075527
auto ReadTextFileV2(std::string& Filename)->std::string {
	// Declare and initialise the variables we will need:
	std::ifstream ifStrm(Filename);
	std::string   str_ = "";
	
	// Get the size of 'Filename':
	ifStrm.seekg(0, std::ios::end);
	str_.reserve(ifStrm.tellg());
	ifStrm.seekg(0, std::ios::beg);
	
	// Read the file into 'str_':
	str_.assign((std::istreambuf_iterator<char>(ifStrm)), 
				 std::istreambuf_iterator<char>());
				 
	// Return the file contents ('str_') to the calling function:
	return str_;
}


// FUNCTION:    DeleteFileFromPath
// DESCRIPTION: Deletes the file named 'Filename'.
auto DeleteFileFromPath(std::string& Filename)->bool {
	fs::path pth(Filename);
	bool status = false;
	status = fs::remove(pth);
	return status;
}


// FUNCTION:    CreateFolder
// DESCRIPTION: Creates a folder/directory named "FolderName" in the current 
//              working directory.
auto CreateFolder(std::string& FolderName)->bool {
	// Check to see if a folder named 'FolderName' already exists. If one does, 
	// immediately return 'true' to the calling function; otherwise, attempt to
	// create a folder with that name:
	bool status = false;
	
	if (fs::exists(FolderName) && fs::is_directory(FolderName)) {
		fmt::print("A folder named '{0}' already exists.\n", FolderName);
		return true;
	} else {
		// Attempt to create the directory:
		status = fs::create_directory(FolderName);
		
		// Inform the user as to whether the directory was created or not:
		if (status) {
			fmt::print("The folder \"{0}\" was successfully created.\n", 
					   FolderName);
		} else {
			std::string msg_ = 
				fmt::format("The folder \"{0}\" could not be created.\n", 
							FolderName);
			PrintErrorMsg(msg_);
		};
		
		// Return the directory creation status to the calling function:
		return status;
	}
	
	// We should not get to this point, so assume there is an error:
	std::string msg_ = "Unreachable code was reached; uh oh!"s;
	throw new std::runtime_error(msg_);
	return false;
}


// FUNCTION:    GetListOfFilesInFolder
// DESCRIPTION: Iterates through the folder specified by 'path', and creates an 
//              'std::vector' of the filenames of each directory entry.
auto GetListOfFilesInFolder(std::string& Directory)->std::vector<std::string> {
	std::vector<std::string> FileList;
	if (!Directory.empty()) {
		fs::path dir_(Directory);
		for (auto& p : fs::recursive_directory_iterator(dir_)) {
			FileList.push_back(p.path().string());
		}
	}
	return FileList;
}


// FUNCTION:    RenameFileOrDir
// DESCRIPTION: Renames the file or directory 'OldName' to 'NewName'.
auto RenameFileOrDir(std::string& OldName, std::string& NewName)->void {
	// https://en.cppreference.com/w/cpp/filesystem/rename
	// fs::path old_p = fs::current_path() / OldName;
	fs::path old_p(OldName);
	fs::rename(old_p, fs::current_path() / NewName); // OK
}


/* -------------------------------------------------------------------------- */


/* --------    String/Text Parsing Functions (narrow)    -------- */
// FUNCTION:    GenerateHorizontalRuler(size_t, char)
// DESCRIPTION: Generates an 'std::string' containing 'Length' characters. The 
//              characters are all the same (currently '-').
auto GenerateHorizontalRuler(size_t Length, char c_)->std::string {
	std::string Ruler_(Length, c_);
	return Ruler_;
}


// FUNCTION:    WStringToString(std::wstring&)
// DESCRIPTION: Accepts a wide string ('std::wstring'), converts it to a narrow 
//              string ('std::string'), and returns the narrowed-string.
auto WStringToString(std::wstring& _WideString)->std::string {
	std::string _NarrowString = "";
	utf8::utf16to8(_WideString.begin(), 
				   _WideString.end(), 
				   back_inserter(_NarrowString)
	);
	return _NarrowString;
}


// FUNCTION:    StringToWString(std::string&)
// DESCRIPTION: Accepts a narrow string ('std::string'), converts it to a wide 
//              string ('std::wstring'), and returns the widened-string.
auto StringToWString(std::string& _NarrowString)->std::wstring {
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(_NarrowString);
}


// FUNCTION:    CslToVector
// DESCRIPTION: Converts a comma-separated list ('_InputList') to an 
//              'std::vector'. Each element of the vector corresponds to the 
//              value between each comma.
auto CslToVector(std::string& _InputList)->std::vector<std::string> {
	// For some reason, the last word in '_InputList' is not added to '_Results'
	// if there is no comma at the very end of '_InputList'. So, check to see if
	// the last character '_InputList' is a comma; if it isn't, add one:
	const size_t LastCharPosition = _InputList.length() - 1ui64; // 0-based idx
	if (_InputList.at(LastCharPosition) != ',') {
		_InputList.append(",");
	}
	
	// Declare and initialise the variables we will use:
	const size_t _InputLen = _InputList.length();
	std::vector<std::string> _Results;
	std::string temp_Str   =    "";
	char        temp_Chr   =   'a';
	size_t      _FirstChar = 0ui64;
	size_t      _LastChar  = 2ui64;
	size_t      _WordLen   = 1ui64;
	
	// Loop through '_InputList' one character at a time. If the character is 
	// not a comma or '\0', then append it to 'temp_Str'. If it is a comma, then
	// add the current value of 'temp_Str' to '_Results':
#pragma loop(hint_parallel(8))
	for (size_t i = 0ui64; i < _InputLen; ++i) {
		// Get the current character from '_InputList':
		temp_Chr = _InputList[i];
		
		// Check if 'temp_Chr' is a comma or a '\0':
		if ((temp_Chr == ',') || (temp_Chr == '\0')) {
			// If this is the first character (i == 0), ignore it:
			if (i == 0ui64) {
				continue;
			} else {
				// Ensure that the length of the string is not 0; this can 
				// occur if the input string contains 2 or more commas in a row:
				if (temp_Str.length() == 0ui64) {
					continue;
				} else {
					// Add the value of 'temp_Str' to '_Results':
					_Results.push_back(temp_Str);
					
					// Clear the contents of 'temp_Str':
					temp_Str.clear();
					
					// Continue to the next word:
					continue;
				}
			}
		} else {
			// Append 'temp_Chr' to the end of 'temp_Str':
			temp_Str += temp_Chr;
		}
	}
	
	// Return '_Results' to the calling function:
	return _Results;
}


// FUNCTION:    CalcDJB2
// DESCRIPTION: Calculates the DJB2 hash of the input string.
auto CalcDJB2(const char* InputString, const size_t Length)->uint64_t {
	uint64_t Hash_ = 5381ui64;
	int32_t  chr_  =     0i32;
	
#pragma loop(hint_parallel(8))
	for (size_t i = 0ui64; i < Length; ++i) {
		chr_ = InputString[i];
		Hash_ = ((Hash_ << 5ui64) + Hash_) + chr_; /* (Hash_ * 33) + chr_ */
	}
	
	return Hash_;
}


// FUNCTION:    ConvertTextToUpperCase(std::string&)
// DESCRIPTION: Converts 'str' from its current case (possibly mixed) to all 
//              upper-case text.
auto ConvertTextToUpperCase(std::string& str)->std::string {
	std::string Upper_ = boost::to_upper_copy<std::string>(str);
	return Upper_;
}


// FUNCTION:    ConvertTextToLowerCase(std::string&)
// DESCRIPTION: Converts 'str' from its current case (possibly mixed) to all 
//              lower-case text.
auto ConvertTextToLowerCase(std::string& str)->std::string {
	std::string Lower_ = boost::to_lower_copy<std::string>(str);
	return Lower_;
}


// FUNCTION:    ConvertTextToUpperCaseV2(std::string&)
// DESCRIPTION: Converts any lowercase letters in 'InputString' to uppercase.
auto ConvertTextToUpperCaseV2(std::string& InputString)->std::string {
	std::locale loc;
	std::string OutputString(InputString);
#pragma loop(hint_parallel(8))
	for (std::string::size_type i = 0; i < OutputString.length(); ++i) {
		OutputString.at(i) = std::toupper(OutputString.at(i), loc);
	}
	return OutputString;
}


// FUNCTION:    ConvertTextToLowerCaseV2(std::string&)
// DESCRIPTION: Converts any uppercase letters in 'InputString' to lowercase.
auto ConvertTextToLowerCaseV2(std::string& InputString)->std::string {
	std::locale loc;
	std::string OutputString(InputString);
	
#pragma loop(hint_parallel(8))
	for (std::string::size_type i = 0; i < OutputString.length(); ++i) {
		OutputString.at(i) = std::tolower(OutputString.at(i), loc);
	}
	return OutputString;
}


// FUNCTION:    UpdatePlaceholder(std::string&, std::string&, std::string&)
// DESCRIPTION: Search 'InputString' for the value 'Placeholder' and replace it 
//              with the value of 'NewValue'. Once all instances of 
//             'Placeholder' have been replaced, return the modified 
//             'std::string' to the calling function.
auto UpdatePlaceholder(std::string& InputString, 
					   std::string& Placeholder, 
					   std::string& NewValue)->std::string {
	// Create an 'std::string' to hold the output:
	std::string OutputString(InputString);
	
	// Search 'InputString' for the value of 'Placeholder':
	size_t index = 0ui64;
	index        = OutputString.find(Placeholder, index);
	if (index == std::string::npos) {
		std::string msg_ = "Could not find placeholder"s;
		return msg_;
	}
	
	// Make the replacement:
	OutputString.replace(index, Placeholder.length(), NewValue);
	
	// Return 'OutputString' to the calling function:
	return OutputString;
}


// FUNCTION:    CompareStrings(std::string&, std::string&)
// DESCRIPTION: Compares 'Str1' with 'Str2'. If they are identical, the function
//              returns TRUE. Otherwise, it returns FALSE.
auto CompareStrings(std::string& Str1, std::string& Str2)->bool {
	int32_t compare_value{
		Str1.compare(Str2)
	};
	if (compare_value != 0i32) {
		return false;
	} else {
		return true;
	}
}


/* -------------------------------------------------------------------------- */


/* --------    Other Utilitiy Functions    -------- */
// FUNCTION:    PauseExecution
// DESCRIPTION: Pauses the thread (and therefore program execution) for 
//              'Duration' milliseconds.
auto PauseExecution(size_t Duration)->void {
	using namespace std::literals::chrono_literals;
	std::chrono::milliseconds sleepDuration(Duration);
	std::this_thread::sleep_for(sleepDuration);
}


// FUNCTION:    GetRandomUInt64
// DESCRIPTION: Uses the C++ standard library to generate a pseudorandom number 
//              between 0 and UINT64_MAX. Note that this function *IS NOT* safe 
//              to use for cryptographic functions; it is intended only for use 
//              where insecure PRNG usage is acceptable (e.g. games).
auto GetRandomUInt64()->uint64_t {
	// Generate a random number:
	std::random_device random_device;
	std::mt19937   random_engine{random_device()};
	const uint64_t MIN_VAL = 0ui64;
	const uint64_t MAX_VAL = UINT64_MAX;
	std::uniform_int_distribution<uint64_t> die_distribution {
		MIN_VAL, MAX_VAL
	};
	uint64_t random_ = die_distribution(random_engine);
	return random_;
}


// FUNCTION:    GetDayOfYear
// DESCRIPTION: Returns the day of the year (a 'uint32_t' between 1 and 365, 
//              inclusive).
auto GetDayOfYear()->uint32_t {
	// Determine the number of days since January 1st:
	std::time_t t            = std::time(nullptr);
	std::tm*    currentMonth = std::localtime(&t);
	uint32_t    DayOfYear    = currentMonth->tm_yday;
	DayOfYear                = (DayOfYear < 365ui32) 
								? (++DayOfYear) 
								: (365ui32);
	return DayOfYear;
}


// FUNCTION:    UInt32ToBytes
// DESCRIPTION: Converts a 'uint32_t' to a vector of 'unsigned char'. This was 
//              adapted from: https://stackoverflow.com/a/5585683
template <typename T>
std::vector<unsigned char> VariableToBytes(T value) {
	constexpr const size_t SizeInBytes = sizeof(T);
	std::vector<unsigned char> arrayOfBytes(SizeInBytes);
#pragma loop(hint_parallel(8))
	for (size_t i = 0; i < SizeInBytes; ++i) {
		//arrayOfBytes[SizeInBytes - i] = (value >> (i * 8));
		arrayOfBytes.push_back((value >> (i * 8))); // FIXME: Is this correct???
	}
	return arrayOfBytes;
}


// NAME:    GetSysEnvironmentVariable(std::string&)
// PURPOSE: Returns the value of an environment variable.
auto GetSysEnvironmentVariable(std::string& EnvVar)->std::string {
	const char* VarName = EnvVar.c_str();
	char*       str     = std::getenv(VarName);
	if (str != nullptr) {
		return std::string(str);
	}
	return std::string("N/A");
}


// NAME:    getTimestamp(std::string&)
// PURPOSE: Returns an 'std::string' with the current timestamp in the 
//          prescribed format (YYYYMMDD-HHMMSS).
auto getTimestamp() noexcept->std::string {
	// Get the current time:
	std::time_t result = std::time(nullptr);
	
	// Allocate a 'char*' buffer to hold the output timestamp string:
	constexpr size_t const BuffSize = 100ui64;
	char* buffer = new (std::nothrow) char[BuffSize]();
	if (buffer == nullptr) {
		std::string msg_ = fmt::format("Could not allocate {0} bytes for the "
									   "buffer", 
									   BuffSize);
		PrintErrorMsg(std::ref(msg_));
	}
	
	// NOTE: For the 'std::strftime()' parameters, refer to:
	//       https://en.cppreference.com/w/cpp/chrono/c/strftime
	if (std::strftime(buffer, 
					  BuffSize, 
					  "%Y%M%d-%H%M%S", 
					  std::localtime(&result))) {
		// Construct an 'std::string' from 'buffer':
		std::string str_(buffer);
		
		// Return 'str_' to the calling function:
		return str_;
	} else {
		std::string str_ = "19700101-000000";
		return str_;
	}
	
	// NOTE: We should NEVER get here, but to ensure that ALL code paths return 
	//       a value, we will put it (just in case...). 
	std::string str_ = "19700101-000000";
	return str_;
}


/* -------------------------------------------------------------------------- */


/* --------    String/Text Parsing Functions (wide)    -------- */
// FUNCTION:    ReadTextFileV2W(std::wstring&)
// DESCRIPTION: Using the C++ API, reads a text file into an 'std::wstring'. 
//              Based off of: https://stackoverflow.com/a/2602060/8075527
std::wstring ReadTextFileV2W(std::wstring& Filename) {
	// Declare and initialise the variables we will need:
	std::wifstream ifStrm(Filename);
	std::wstring   str_ = L"";
	
	// Get the size of 'Filename':
	ifStrm.seekg(0, std::ios::end);   
	str_.reserve(ifStrm.tellg());
	ifStrm.seekg(0, std::ios::beg);
	
	// Read the file into 'str_':
	str_.assign((std::istreambuf_iterator<wchar_t>(ifStrm)), 
				 std::istreambuf_iterator<wchar_t>());
				 
	// Return the file contents ('str_') to the calling function:
	return str_;
}


// FUNCTION:    WriteStringToFileW(std::wstring&, std::wstring&)
// DESCRIPTION: Writes the value of 'Text' to a text file named 'Filename'.
void WriteStringToFileW(std::wstring& Filename, std::wstring& Text) {
	std::wofstream ofsOutput;
	ofsOutput.open(Filename, std::ios::out);
	if (!ofsOutput.is_open()) {
		std::wstring msg_ = fmt::format(L"Could not open \"{0}\".\n", Filename);
		std::wcerr << L"Error: " << msg_ << std::endl;
		return;
	}
	ofsOutput.write(Text.c_str(), Text.length());
	ofsOutput.flush();
	ofsOutput.close();
}


// FUNCTION:    CompareStringsW(std::wstring&, std::wstring&)
// DESCRIPTION: Compares 'Str1' with 'Str2'. If they are identical, the function
//              returns TRUE. Otherwise, it returns FALSE.
bool CompareStringsW(std::wstring& Str1, std::wstring& Str2) {
	int32_t compare_value{
		Str1.compare(Str2)
	};
	if (compare_value != 0i32) {
		return false;
	} else {
		return true;
	}
}


// FUNCTION:    UpdatePlaceholderW(std::wstring&, std::wstring&, std::wstring&)
// DESCRIPTION: Search 'InputString' for the value 'Placeholder' and replace it 
//              with the value of 'NewValue'. Once all instances of 
//             'Placeholder' have been replaced, return the modified 
//             'std::string' to the calling function.
std::wstring UpdatePlaceholderW(std::wstring& InputString, 
								std::wstring& Placeholder, 
								std::wstring& NewValue) {
	// Create an 'std::string' to hold the output:
	std::wstring OutputString(InputString);
	
	// Search 'InputString' for the value of 'Placeholder':
	size_t index = 0ui64;
	index        = OutputString.find(Placeholder, index);
	if (index == std::string::npos) {
		std::wstring msg_ = L"Could not find placeholder";
		std::wcerr << L"Error: " << msg_ << std::endl;
		return msg_;
	}
	
	// Make the replacement:
	OutputString.replace(index, Placeholder.length(), NewValue);
	
	// Return 'OutputString' to the calling function:
	return OutputString;
}


// FUNCTION:    IsValidFileW(std::wstring&)
// DESCRIPTION: Verifies that the file named 'Filename' exists and is a regular 
//              file. Returns 'false' if either test fails, and 'true' if both 
//              pass.
bool IsValidFileW(std::wstring& Filename) {
	std::string FilenameN = WStringToString(Filename);
	bool        result    = IsValidFile(FilenameN);
	return result;
}


// From:
// "C:\Users\seanc\source\repos\_3rdParty\_Microsoft\_CPP\VCSamples\VC2010Samples\ComTypeLibfor7\freethrd\server\apputil.cpp"

/* -----------------------------------------------------------------------------
  Function: UcToAnsi

  Summary:  Convert a UNICODE input string to an output ANSI string.

  Args:     LPWSTR pszUc
              Pointer to a caller's input UNICODE wide string.
            LPSTR pszAnsi
              Pointer to a caller's output ANSI string.
            int cch
              Character count. If 0 then use length of pszUc.

  Returns:  HRESULT
              Standard OLE result code. NOERROR for success.
----------------------------------------------------------------------------- */
#include <Stringapiset.h>
//HRESULT UcToAnsi(LPWSTR pszUc, LPSTR pszAnsi, int cch) {
int UcToAnsi(wchar_t* pszUc, char* pszAnsi, int cch) {
	HRESULT hr = E_FAIL;
	int     cSize;
	int     cOut;
	
	if (0 == cch) {
		cSize = WideCharToMultiByte(CP_ACP, 0, pszUc, -1, nullptr, 0, nullptr, nullptr);
	} else {
		cSize = cch;
	}
	
	if (0 != cSize) {
		cOut = WideCharToMultiByte(CP_ACP, 0, pszUc, -1, pszAnsi, cSize, nullptr, nullptr);
		if (0 != cOut) {
			//hr = NOERROR;
			hr = 0;
		}
	}
	
	return hr;
}
