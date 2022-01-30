// SPDX-License-Identifier: GPL-2.0-only
// PROJECT NAME:  MP3Edit
// COPYRIGHT:     Copyright © 2021 Sean Cassell <sean.cassell@outlook.com>
// FILENAME:      GenreList.cpp
// FILE PURPOSE:  Defines a function that provides a vector of genres.


/* **************************** INCLUDED HEADERS **************************** */
#include "GenreList.hpp"


/* ************************** FUNCTION DEFINITIONS ************************** */
//
//    FUNCTION: getGenreList()
//    
//    RETURNS:  std::vector<_Genre>
//    
//    PURPOSE:  
//
auto getGenreList()->std::vector<_Genre> {
	std::vector<_Genre> list;
	list.reserve(82);
	
	_Genre _temp;
	
	_temp._id = 0;
	_temp._value = _T("Blues");
	list.emplace_back(_temp);
	
	_temp._id = 1;
	_temp._value = _T("Classic Rock");
	list.emplace_back(_temp);
	
	_temp._id = 2;
	_temp._value = _T("Country");
	list.emplace_back(_temp);
	
	_temp._id = 3;
	_temp._value = _T("Dance");
	list.emplace_back(_temp);
	
	_temp._id = 4;
	_temp._value = _T("Disco");
	list.emplace_back(_temp);
	
	_temp._id = 5;
	_temp._value = _T("Funk");
	list.emplace_back(_temp);
	
	_temp._id = 6;
	_temp._value = _T("Grunge");
	list.emplace_back(_temp);
	
	_temp._id = 7;
	_temp._value = _T("Hip-Hop");
	list.emplace_back(_temp);
	
	_temp._id = 8;
	_temp._value = _T("Jazz");
	list.emplace_back(_temp);
	
	_temp._id = 9;
	_temp._value = _T("Metal");
	list.emplace_back(_temp);
	
	_temp._id = 10;
	_temp._value = _T("New Age");
	list.emplace_back(_temp);
	
	_temp._id = 11;
	_temp._value = _T("Oldies");
	list.emplace_back(_temp);
	
	_temp._id = 12;
	_temp._value = _T("Other");
	list.emplace_back(_temp);
	
	_temp._id = 13;
	_temp._value = _T("Pop");
	list.emplace_back(_temp);
	
	_temp._id = 14;
	_temp._value = _T("R&B");
	list.emplace_back(_temp);
	
	_temp._id = 15;
	_temp._value = _T("Rap");
	list.emplace_back(_temp);
	
	_temp._id = 16;
	_temp._value = _T("Reggae");
	list.emplace_back(_temp);
	
	_temp._id = 17;
	_temp._value = _T("Rock");
	list.emplace_back(_temp);
	
	_temp._id = 18;
	_temp._value = _T("Techno");
	list.emplace_back(_temp);
	
	_temp._id = 19;
	_temp._value = _T("Industrial");
	list.emplace_back(_temp);
	
	_temp._id = 20;
	_temp._value = _T("Alternative");
	list.emplace_back(_temp);
	
	_temp._id = 21;
	_temp._value = _T("Ska");
	list.emplace_back(_temp);
	
	_temp._id = 22;
	_temp._value = _T("Death Metal");
	list.emplace_back(_temp);
	
	_temp._id = 23;
	_temp._value = _T("Pranks");
	list.emplace_back(_temp);
	
	_temp._id = 24;
	_temp._value = _T("Soundtrack");
	list.emplace_back(_temp);
	
	_temp._id = 25;
	_temp._value = _T("Euro-Techno");
	list.emplace_back(_temp);
	
	_temp._id = 26;
	_temp._value = _T("Ambient");
	list.emplace_back(_temp);
	
	_temp._id = 27;
	_temp._value = _T("Trip-Hop");
	list.emplace_back(_temp);
	
	_temp._id = 28;
	_temp._value = _T("Vocal");
	list.emplace_back(_temp);
	
	_temp._id = 29;
	_temp._value = _T("Jazz+Funk");
	list.emplace_back(_temp);
	
	_temp._id = 30;
	_temp._value = _T("Fusion");
	list.emplace_back(_temp);
	
	_temp._id = 31;
	_temp._value = _T("Trance");
	list.emplace_back(_temp);
	
	_temp._id = 32;
	_temp._value = _T("Classical");
	list.emplace_back(_temp);
	
	_temp._id = 33;
	_temp._value = _T("Instrumental");
	list.emplace_back(_temp);
	
	_temp._id = 34;
	_temp._value = _T("Acid");
	list.emplace_back(_temp);
	
	_temp._id = 35;
	_temp._value = _T("House");
	list.emplace_back(_temp);
	
	_temp._id = 36;
	_temp._value = _T("Game");
	list.emplace_back(_temp);
	
	_temp._id = 37;
	_temp._value = _T("Sound Clip");
	list.emplace_back(_temp);
	
	_temp._id = 38;
	_temp._value = _T("Gospel");
	list.emplace_back(_temp);
	
	_temp._id = 39;
	_temp._value = _T("Noise");
	list.emplace_back(_temp);
	
	_temp._id = 40;
	_temp._value = _T("AlternRock");
	list.emplace_back(_temp);
	
	_temp._id = 41;
	_temp._value = _T("Bass");
	list.emplace_back(_temp);
	
	_temp._id = 42;
	_temp._value = _T("Soul");
	list.emplace_back(_temp);
	
	_temp._id = 43;
	_temp._value = _T("Punk");
	list.emplace_back(_temp);
	
	_temp._id = 44;
	_temp._value = _T("Space");
	list.emplace_back(_temp);
	
	_temp._id = 45;
	_temp._value = _T("Meditative");
	list.emplace_back(_temp);
	
	_temp._id = 46;
	_temp._value = _T("Instrumental Pop");
	list.emplace_back(_temp);
	
	_temp._id = 47;
	_temp._value = _T("Instrumental Rock");
	list.emplace_back(_temp);
	
	_temp._id = 48;
	_temp._value = _T("Ethnic");
	list.emplace_back(_temp);
	
	_temp._id = 49;
	_temp._value = _T("Gothic");
	list.emplace_back(_temp);
	
	_temp._id = 50;
	_temp._value = _T("Darkwave");
	list.emplace_back(_temp);
	
	_temp._id = 51;
	_temp._value = _T("Techno-Industrial");
	list.emplace_back(_temp);
	
	_temp._id = 52;
	_temp._value = _T("Electronic");
	list.emplace_back(_temp);
	
	_temp._id = 53;
	_temp._value = _T("Pop-Folk");
	list.emplace_back(_temp);
	
	_temp._id = 54;
	_temp._value = _T("Eurodance");
	list.emplace_back(_temp);
	
	_temp._id = 55;
	_temp._value = _T("Dream");
	list.emplace_back(_temp);
	
	_temp._id = 56;
	_temp._value = _T("Southern Rock");
	list.emplace_back(_temp);
	
	_temp._id = 57;
	_temp._value = _T("Comedy");
	list.emplace_back(_temp);
	
	_temp._id = 58;
	_temp._value = _T("Cult");
	list.emplace_back(_temp);
	
	_temp._id = 59;
	_temp._value = _T("Gangsta");
	list.emplace_back(_temp);
	
	_temp._id = 60;
	_temp._value = _T("Top 40");
	list.emplace_back(_temp);
	
	_temp._id = 61;
	_temp._value = _T("Christian Rap");
	list.emplace_back(_temp);
	
	_temp._id = 62;
	_temp._value = _T("Pop/Funk");
	list.emplace_back(_temp);
	
	_temp._id = 63;
	_temp._value = _T("Jungle");
	list.emplace_back(_temp);
	
	_temp._id = 64;
	_temp._value = _T("Native American");
	list.emplace_back(_temp);
	
	_temp._id = 65;
	_temp._value = _T("Cabaret");
	list.emplace_back(_temp);
	
	_temp._id = 66;
	_temp._value = _T("New Wave");
	list.emplace_back(_temp);
	
	_temp._id = 67;
	_temp._value = _T("Psychadelic");
	list.emplace_back(_temp);
	
	_temp._id = 68;
	_temp._value = _T("Rave");
	list.emplace_back(_temp);
	
	_temp._id = 69;
	_temp._value = _T("Showtunes");
	list.emplace_back(_temp);
	
	_temp._id = 70;
	_temp._value = _T("Trailer");
	list.emplace_back(_temp);
	
	_temp._id = 71;
	_temp._value = _T("Lo-Fi");
	list.emplace_back(_temp);
	
	_temp._id = 72;
	_temp._value = _T("Tribal");
	list.emplace_back(_temp);
	
	_temp._id = 73;
	_temp._value = _T("Acid Punk");
	list.emplace_back(_temp);
	
	_temp._id = 74;
	_temp._value = _T("Acid Jazz");
	list.emplace_back(_temp);
	
	_temp._id = 75;
	_temp._value = _T("Polka");
	list.emplace_back(_temp);
	
	_temp._id = 76;
	_temp._value = _T("Retro");
	list.emplace_back(_temp);
	
	_temp._id = 77;
	_temp._value = _T("Musical");
	list.emplace_back(_temp);
	
	_temp._id = 78;
	_temp._value = _T("Rock & Roll");
	list.emplace_back(_temp);
	
	_temp._id = 79;
	_temp._value = _T("Hard Rock");
	list.emplace_back(_temp);
	
	_temp._id = 80;
	_temp._value = _T("Podcast");
	list.emplace_back(_temp);
	
	_temp._id = 81;
	_temp._value = _T("Audiobook");
	list.emplace_back(_temp);
	
	return list;
}
