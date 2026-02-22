#pragma once

#include "types.h"
#include "boilerplate.h"
#include "colorFormatHandlers.h"
#include "indexFormatHandlers.h"
#include "blockFormatHandlers.h"

extern f2i_color_format_t f2i_all_color_formats[];
extern f2i_index_format_t f2i_all_index_formats[];
extern f2i_block_format_t f2i_all_block_formats[];

extern int const f2i_num_color_formats;
extern int const f2i_num_index_formats;
extern int const f2i_num_block_formats;

inline f2i_index_format_t const* findIndexFormat(char const* id) {
	for (int i = 0; i < f2i_num_index_formats; ++i) {
		if (f2i_strEqualIgnoreCaseAssumeAscii(f2i_all_index_formats[i].id, id)) {
			return &f2i_all_index_formats[i];
		}
	}
	return NULL;
}

inline f2i_color_format_t const* findColorFormat(char const* id) {
	for (int i = 0; i < f2i_num_color_formats; ++i) {
		if (f2i_strEqualIgnoreCaseAssumeAscii(f2i_all_color_formats[i].id, id)) {
			return &f2i_all_color_formats[i];
		}
	}
	return NULL;
}

inline f2i_block_format_t const* findBlockFormat(char const* id) {
	for (int i = 0; i < f2i_num_block_formats; ++i) {
		if (f2i_strEqualIgnoreCaseAssumeAscii(f2i_all_block_formats[i].id, id)) {
			return &f2i_all_block_formats[i];
		}
	}
	return NULL;
}
