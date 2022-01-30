/*
 * This file is part of the id3v2lib library
 *
 * Copyright (c) 2013, Lorenzo Ruiz
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#pragma once
#ifndef ID3V2LIB_FRAME_H
#define ID3V2LIB_FRAME_H

#ifdef __cplusplus
extern "C" {
#endif


#include <inttypes.h>
#include <id3v2lib/constants.h>
#include <id3v2lib/types.h>


ID3v2_frame*                 parse_frame(char* bytes, 
                                         int32_t offset, 
                                         int32_t version);
int32_t                      get_frame_type(char* frame_id);
ID3v2_frame_text_content*    parse_text_frame_content(ID3v2_frame* frame);
ID3v2_frame_comment_content* parse_comment_frame_content(ID3v2_frame* frame);
ID3v2_frame_apic_content*    parse_apic_frame_content(ID3v2_frame* frame);


#ifdef __cplusplus
}
#endif

#endif  // ID3V2LIB_FRAME_H
