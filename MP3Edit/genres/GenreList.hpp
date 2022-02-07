/* ****************************** HEADER GUARD ****************************** */
#pragma once


/* **************************** INCLUDED HEADERS **************************** */
// C++ STANDARD LIBRARY/STL HEADERS:
#include <new>
#include <string>
#include <vector>


/* ******************************* STRUCTURES ******************************* */
typedef struct __genre {
	uint32_t    _id;
	std::string _value;
} _Genre;


/* ************************** FUNCTION PROTOTYPES *************************** */
auto getGenreList()->std::vector<_Genre>;
