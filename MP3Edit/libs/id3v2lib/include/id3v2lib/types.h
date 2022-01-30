/*
 * This file is part of the id3v2lib library
 *
 * Copyright (c) 2013, Lorenzo Ruiz
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#pragma once
#ifndef ID3V2LIB_TYPES_H
#define ID3V2LIB_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif


#include <inttypes.h>
#include <id3v2lib/constants.h>


// Data types:
typedef struct {
	char    tag[ID3_HEADER_TAG];
	char    major_version;
	char    minor_version;
	char    flags;
	int32_t tag_size;
	int32_t extended_header_size;
} ID3v2_header;

typedef struct {
	int32_t size;
	char    encoding;
	char*   data;
} ID3v2_frame_text_content;

typedef struct {
	char* language;
	char* short_description;
	ID3v2_frame_text_content* text;
} ID3v2_frame_comment_content;

typedef struct {
	char    encoding;
	char*   mime_type;
	char    picture_type;
	char*   description;
	int32_t picture_size;
	char*   data;
} ID3v2_frame_apic_content;

typedef struct {
	char    frame_id[ID3_FRAME_ID];
	int32_t size;
	char    flags[ID3_FRAME_FLAGS];
	char*   data;
} ID3v2_frame;

typedef struct _ID3v2_frame_list {
	ID3v2_frame*              frame;
	struct _ID3v2_frame_list* start;
	struct _ID3v2_frame_list* last;
	struct _ID3v2_frame_list* next;
} ID3v2_frame_list;

typedef struct {
	char*             raw;
	ID3v2_header*     tag_header;
	ID3v2_frame_list* frames;
} ID3v2_tag;


// Constructor functions:
ID3v2_header*                new_header();
ID3v2_tag*                   new_tag();
ID3v2_frame*                 new_frame();
ID3v2_frame_list*            new_frame_list();
ID3v2_frame_text_content*    new_text_content(int32_t size);
ID3v2_frame_comment_content* new_comment_content(int32_t size);
ID3v2_frame_apic_content*    new_apic_content();


#ifdef __cplusplus
}
#endif

#endif  // ID3V2LIB_TYPES_H
