#pragma once

#include "types.h"

void f2i_blockFormatHandlerDXT1    (f2i_rgba8888_t* dst, uint8_t const* src, int dstWidth, int numBytes);
void f2i_blockFormatHandlerDXT5    (f2i_rgba8888_t* dst, uint8_t const* src, int dstWidth, int numBytes);

void f2i_blockFormatHandlerGameboy (f2i_rgba8888_t* dst, uint8_t const* src, int dstWidth, int numBytes);
void f2i_blockFormatHandlerNES     (f2i_rgba8888_t* dst, uint8_t const* src, int dstWidth, int numBytes);
