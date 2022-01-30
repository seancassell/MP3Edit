/*
 * This file is part of the id3v2lib library
 *
 * Copyright (c) 2013, Lorenzo Ruiz
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#pragma once
#ifndef ID3V2LIB_UTILS_H
#define ID3V2LIB_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif


#include <inttypes.h>
#include <id3v2lib/types.h>


// Conversion functions:
uint32_t     bytes_to_int(char* bytes, int32_t size, int32_t offset);
char*        int_to_bytes(int32_t integer);
int32_t      syncint_encode(int32_t value);
int32_t      syncint_decode(int32_t value);
void         add_to_list(ID3v2_frame_list* list, ID3v2_frame* frame);
ID3v2_frame* get_from_list(ID3v2_frame_list* list, char* frame_id);
void         free_tag(ID3v2_tag* tag);
char*        get_mime_type_from_filename(const char* filename);

// String functions:
int32_t   has_bom(uint16_t* string);
uint16_t* char_to_utf16(char* string, int32_t size);
void      println_utf16(uint16_t* string, int32_t size);
char*     get_path_to_file(const char* file);


#ifdef __cplusplus
}
#endif

#endif  // ID3V2LIB_UTILS_H
