// SPDX-License-Identifier: GPL-2.0-only
// PROJECT NAME:  MP3Edit
// COPYRIGHT:     Copyright © 2022 Sean Cassell <sean.cassell@outlook.com>
// FILENAME:      TagsIO.cpp
// FILE PURPOSE:  Defines the class 'TagsIO', which interfaces with the 
//                <id3v2lib> library.


/* **************************** INCLUDED HEADERS **************************** */
// PROJECT-SPECIFIC HEADERS:
#include "TagsIO.hpp"


/* **************************** CLASS DEFINITION **************************** */
TagsIO::TagsIO(string& MP3Filename) noexcept : MP3Filename_(MP3Filename) {
	// Verify that the file specified by 'MP3Filename' exists and is an MP3:
	bool bIsMP3 = isValidMP3();
	if (!bIsMP3) {
		static string mb_title_ = "Error Encountered";
		static string mb_body_{
			fmt::format("The file \"{0}\" does not exist, or does does not "
						"appear to be a valid MP3.", 
						MP3Filename)
		};
		MessageBoxA(0, 
					mb_body_.c_str(), 
					mb_title_.c_str(), 
					MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	
	// Load the full set of tags from the file:
	Tag_ = load_tag(MP3Filename_.c_str());
	if (Tag_ == nullptr) {
		Tag_ = new_tag();
	}
	Frame temp;
	/* Field: Title */
	temp._frame         = tag_get_title(Tag_);
	temp._text_content  = parse_text_frame_content(temp._frame);
	temp._value         = temp._text_content->data;
	Title_              = temp._value;
	mapFrames_["Title"] = temp;
	
	/* Field: Artist */
	temp._frame         = tag_get_artist(Tag_);
	temp._text_content  = parse_text_frame_content(temp._frame);
	temp._value         = temp._text_content->data;
	Artist_             = temp._value;
	mapFrames_["Artist"] = temp;
	
	/* Field: Album */
	temp._frame         = tag_get_album(Tag_);
	temp._text_content  = parse_text_frame_content(temp._frame);
	temp._value         = temp._text_content->data;
	Album_              = temp._value;
	mapFrames_["Album"] = temp;
	
	/* Field: Year */
	temp._frame         = tag_get_year(Tag_);
	temp._text_content  = parse_text_frame_content(temp._frame);
	temp._value         = temp._text_content->data;
	Year_               = temp._value;
	mapFrames_["Year"]  = temp;
	
	/* Field: Track */
	temp._frame         = tag_get_track(Tag_);
	temp._text_content  = parse_text_frame_content(temp._frame);
	temp._value         = temp._text_content->data;
	Track_              = temp._value;
	mapFrames_["Track"] = temp;
	
	/* Field: Comment */
	temp._frame           = tag_get_comment(Tag_);
	auto* comment__       = parse_comment_frame_content(temp._frame);
	auto* comment__text_  = comment__->text;
	temp._value           = comment__text_->data;
	Comment_              = temp._value;
	mapFrames_["Comment"] = temp;
	
	/* Field: AlbumArtist */
	temp._frame         = tag_get_album_artist(Tag_);
	temp._text_content  = parse_text_frame_content(temp._frame);
	temp._value         = temp._text_content->data;
	AlbumArtist_        = temp._value;
	mapFrames_["AlbumArtist"] = temp;
	
	/* Field: Genre */
	temp._frame         = tag_get_genre(Tag_);
	temp._text_content  = parse_text_frame_content(temp._frame);
	temp._value         = temp._text_content->data;
	Genre_              = temp._value;
	mapFrames_["Genre"] = temp;
	
	/* Field: Composer */
	temp._frame         = tag_get_composer(Tag_);
	temp._text_content  = parse_text_frame_content(temp._frame);
	temp._value         = temp._text_content->data;
	Composer_           = temp._value;
	mapFrames_["Composer"] = temp;
	
	/* Field: DiscNumber */
	temp._frame         = tag_get_disc_number(Tag_);
	temp._text_content  = parse_text_frame_content(temp._frame);
	temp._value         = temp._text_content->data;
	DiscNumber_         = temp._value;
	mapFrames_["DiscNumber"] = temp;
}


TagsIO::~TagsIO() noexcept {
	// Write the new tag values to the file:
	tag_set_title(Title_.data(),              0, Tag_);
	tag_set_artist(Artist_.data(),            0, Tag_);
	tag_set_album(Album_.data(),              0, Tag_);
	tag_set_album_artist(AlbumArtist_.data(), 0, Tag_);
	tag_set_genre(Genre_.data(),              0, Tag_);
	tag_set_track(Track_.data(),              0, Tag_);
	tag_set_year(Year_.data(),                0, Tag_);
	tag_set_comment(Comment_.data(),          0, Tag_);
	tag_set_disc_number(DiscNumber_.data(),   0, Tag_);
	tag_set_composer(Composer_.data(),        0, Tag_);
	set_tag(MP3Filename_.data(), Tag_);
}


bool TagsIO::isValidMP3() {
	// Check if the file/path exists:
	fs::path _path(MP3Filename_);
	if (fs::exists(_path) == false) {
		return false;
	}
	
	// Check if the file extension is ".mp3"/".MP3":
	string expected_ = ".mp3"s;
	string actual_   = _path.extension().string();
	actual_ = ConvertTextToLowerCase(std::ref(actual_));
	bool bIsMatch = CompareStrings(std::ref(expected_), std::ref(actual_));
	if (!bIsMatch) {
		return false;
	}
	return true;
}
