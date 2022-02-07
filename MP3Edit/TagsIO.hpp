// SPDX-License-Identifier: GPL-2.0-only
// PROJECT NAME:  MP3Edit
// COPYRIGHT:     Copyright © 2022 Sean Cassell <sean.cassell@outlook.com>
// FILENAME:      TagsIO.hpp
// FILE PURPOSE:  Declares the class 'TagsIO', which interfaces with the 
//                <id3v2lib> library.


/* ****************************** HEADER GUARD ****************************** */
#pragma once


/* **************************** INCLUDED HEADERS **************************** */
// PROJECT-SPECIFIC HEADERS:
#include "StdAfx.hpp"


/* *************************** CUSTOM DATA TYPES **************************** */
using Frame = struct _Frame {
	_Frame() {}
	~_Frame() {}
	ID3v2_frame*              _frame        = nullptr;
	ID3v2_frame_text_content* _text_content = nullptr;
	string                    _value        = "";
};


/* *************************** CLASS DECLARATION **************************** */
class TagsIO {
	
	private:
		ID3v2_tag*              Tag_;
		std::map<string, Frame> mapFrames_;
	
	public:
		string MP3Filename_ = "placeholder.mp3"s;
		string Title_       = "Title"s;
		string Artist_      = "Artist"s;
		string Album_       = "Album"s;
		string Year_        = "Year"s;
		string Track_       = "Track"s;
		string Comment_     = "Comment"s;
		string AlbumArtist_ = "AlbumArtist"s;
		string Genre_       = "Genre"s;
		string Composer_    = "Composer"s;
		string DiscNumber_  = "DiscNumber"s;
	
	public:
		TagsIO() = delete;
		TagsIO(string& MP3Filename) noexcept;
		~TagsIO() noexcept;
	
	private:
		bool isValidMP3();
	
};
