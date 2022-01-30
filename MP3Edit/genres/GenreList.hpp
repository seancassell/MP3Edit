/* ****************************** HEADER GUARD ****************************** */
#pragma once


/* **************************** INCLUDED HEADERS **************************** */
#include <new>
#include <vector>
//#include "../header.hpp"


/* ******************************* DATA TYPES ******************************* */
// Define a Unicode string type alias:
//typedef std::basic_string<TCHAR> ustring;


/* ******************************* STRUCTURES ******************************* */
typedef struct __genre {
	uint32_t    _id;
	std::string _value;
} _Genre;


/* ************************** FUNCTION PROTOTYPES *************************** */
auto getGenreList()->std::vector<_Genre>;
