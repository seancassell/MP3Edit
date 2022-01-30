/*
 * This file is part of the id3v2lib library
 *
 * Copyright (c) 2013, Lorenzo Ruiz
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <id3v2lib/utils.h>


uint32_t bytes_to_int(char* bytes, int32_t size, int32_t offset) {
	uint32_t result = 0x00;
	int32_t  i      =    0;
	for (i = 0; i < size; ++i) {
		result = result << 8;
		result = result | (unsigned char) bytes[offset + i];
	}
	
	return result;
}


char* int_to_bytes(int32_t integer) {
	int32_t i;
	int32_t size   = 4;
	char*   result = (char*) malloc(sizeof(char) * size);
	
	// We need to reverse the bytes because Intel uses little endian:
	char* aux = (char*) &integer;
	for (i = size - 1; i >= 0; --i) {
		result[size - 1 - i] = aux[i];
	}
	
	return result;
}


int32_t syncint_encode(int32_t value) {
	int32_t out;
	int32_t mask = 0x7F;
	
	while (mask ^ 0x7FFFFFFF) {
		out   = value & ~mask;
		out   <<= 1;
		out   |= value & mask;
		mask  = ((mask + 1) << 8) - 1;
		value = out;
	}
	
	return out;
}


int32_t syncint_decode(int32_t value) {
	uint32_t a      = 0;
	uint32_t b      = 0;
	uint32_t c      = 0;
	uint32_t d      = 0;
	uint32_t result = 0x0;
	a = (value & 0xFF);
	b = ((value >>  8) & 0xFF);
	c = ((value >> 16) & 0xFF);
	d = ((value >> 24) & 0xFF);
	
	result = (result | a);
	result = (result | (b << 7));
	result = (result | (c << 14));
	result = (result | (d << 21));
	
	return result;
}


void add_to_list(ID3v2_frame_list* main, ID3v2_frame* frame) {
	ID3v2_frame_list* current;
	
	// Check if the list is empty:
	if (main->start == NULL) {
		main->start = main;
		main->last  = main;
		main->frame = frame;
	} else {
		current          = new_frame_list();
		current->frame   = frame;
		current->start   = main->start;
		main->last->next = current;
		main->last       = current;
	}
}


ID3v2_frame* get_from_list(ID3v2_frame_list* list, char* frame_id) {
	while ((list != NULL) && (list->frame != NULL)) {
		if (strncmp(list->frame->frame_id, frame_id, 4) == 0) {
			return list->frame;
		}
		list = list->next;
	}
	return NULL;
}


void free_tag(ID3v2_tag* tag) {
	ID3v2_frame_list* list;
	
	free(tag->raw);
	free(tag->tag_header);
	list = tag->frames;
	while (list != NULL) {
		if (list->frame) {
			free(list->frame->data);
		}
		free(list->frame);
		list = list->next;
	}
	free(list);
	free(tag);
}


char* get_mime_type_from_filename(const char* filename) {
	if (strcmp(strrchr(filename, '.') + 1, "png") == 0) {
		return PNG_MIME_TYPE;
	} else {
		return JPG_MIME_TYPE;
	}
}


// String functions:
int32_t has_bom(uint16_t* string) {
	if (memcmp("\xFF\xFE", string, 2) == 0 
		|| memcmp("\xFE\xFF", string, 2) == 0) {
		return 1;
	}
	return 0;
}


uint16_t* char_to_utf16(char* string, int32_t size) {
	uint16_t* result = (uint16_t*) malloc(size * sizeof(uint16_t));
	memcpy(result, string, size);
	return result;
}


void println_utf16(uint16_t* string, int32_t size) {
	// Start at 1 to skip the byte order marker (BOM):
	int32_t i = 1;
	while (1) {
		if ((size > 0) && (i > size)) {
			break;
		}
		
		if (string[i] == 0x0000) {
			break;
		}
		
		printf("%lc", string[i]);
		++i;
	}
	printf("\n");
}


char* get_path_to_file(const char* file) {
	char*    file_name = strrchr(file, '/');
	
	// Add 1 to account for the trailing '/':
	uint32_t size      = strlen(file) - strlen(file_name) + 1; 
	char*    file_path = (char*) malloc(size * sizeof(char));
	strncpy(file_path, file, size);
	
	return file_path;
}
