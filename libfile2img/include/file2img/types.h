#pragma once

#include <stdint.h>

typedef struct {
	uint8_t r, g, b, a;
} f2i_rgba8888_t;

typedef struct {
	char const* id;
	int bit_depth;
	void (*function)(int* dst, uint8_t const* src, int numBytes);
	char const* description;
} f2i_index_format_t;

typedef struct {
	char const* id;
	int bit_depth;
	void (*function)(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);
	char const* description;
} f2i_color_format_t;

typedef struct {
	char const* id;
	int bit_depth;
	int width;
	int height;
	void (*function)(f2i_rgba8888_t* dst, uint8_t const* src, int dstWidth, int numBytes);
	char const* description;
} f2i_block_format_t;
