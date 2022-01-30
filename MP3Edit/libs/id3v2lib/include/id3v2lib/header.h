/*
 * This file is part of the id3v2lib library
 *
 * Copyright (c) 2013, Lorenzo Ruiz
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#pragma once
#ifndef ID3V2LIB_HEADER_H
#define ID3V2LIB_HEADER_H

#ifdef __cplusplus
extern "C" {
#endif


#include <inttypes.h>
#include <id3v2lib/constants.h>
#include <id3v2lib/types.h>
#include <id3v2lib/utils.h>


int32_t       has_id3v2tag(ID3v2_header* tag_header);
int32_t       _has_id3v2tag(char* raw_header);
ID3v2_header* get_tag_header(const char* file_name);
ID3v2_header* get_tag_header_with_buffer(char* buffer, int32_t length);
int32_t       get_tag_version(ID3v2_header* tag_header);
void          edit_tag_size(ID3v2_tag* tag);


#ifdef __cplusplus
}
#endif

#endif  // ID3V2LIB_HEADER_H
