/*
 * This file is part of the id3v2lib library
 *
 * Copyright (c) 2013, Lorenzo Ruiz
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */


#pragma once
#ifndef ID3V2LIB_ID3V2LIB_H
#define ID3V2LIB_ID3V2LIB_H

#ifdef __cplusplus
extern "C" {
#endif


#include <inttypes.h>
#include <id3v2lib/constants.h>
#include <id3v2lib/frame.h>
#include <id3v2lib/header.h>
#include <id3v2lib/types.h>
#include <id3v2lib/utils.h>


ID3v2_tag* load_tag(const char* file_name);
ID3v2_tag* load_tag_with_buffer(char* buffer, int32_t length);
void       remove_tag(const char* file_name);
void       set_tag(const char* file_name, ID3v2_tag* tag);


// Getter functions:
ID3v2_frame* tag_get_title(ID3v2_tag* tag);
ID3v2_frame* tag_get_artist(ID3v2_tag* tag);
ID3v2_frame* tag_get_album(ID3v2_tag* tag);
ID3v2_frame* tag_get_album_artist(ID3v2_tag* tag);
ID3v2_frame* tag_get_genre(ID3v2_tag* tag);
ID3v2_frame* tag_get_track(ID3v2_tag* tag);
ID3v2_frame* tag_get_year(ID3v2_tag* tag);
ID3v2_frame* tag_get_comment(ID3v2_tag* tag);
ID3v2_frame* tag_get_disc_number(ID3v2_tag* tag);
ID3v2_frame* tag_get_composer(ID3v2_tag* tag);
ID3v2_frame* tag_get_album_cover(ID3v2_tag* tag);


// Setter functions:
void tag_set_title(char* title, char encoding, ID3v2_tag* tag);
void tag_set_artist(char* artist, char encoding, ID3v2_tag* tag);
void tag_set_album(char* album, char encoding, ID3v2_tag* tag);
void tag_set_album_artist(char* album_artist, char encoding, ID3v2_tag* tag);
void tag_set_genre(char* genre, char encoding, ID3v2_tag* tag);
void tag_set_track(char* track, char encoding, ID3v2_tag* tag);
void tag_set_year(char* year, char encoding, ID3v2_tag* tag);
void tag_set_comment(char* comment, char encoding, ID3v2_tag* tag);
void tag_set_disc_number(char* disc_number, char encoding, ID3v2_tag* tag);
void tag_set_composer(char* composer, char encoding, ID3v2_tag* tag);
void tag_set_album_cover(const char* filename, ID3v2_tag* tag);
void tag_set_album_cover_from_bytes(char*      album_cover_bytes, 
                                    char*      mimetype, 
                                    int32_t    picture_size,
                                    ID3v2_tag* tag);


#ifdef __cplusplus
}
#endif

#endif  // ID3V2LIB_ID3V2LIB_H
