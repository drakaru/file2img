#pragma once

#include "types.h"

void f2i_indexFormatHandlerI4BE (int* dst, uint8_t const* src, int numBytes);
void f2i_indexFormatHandlerI4LE (int* dst, uint8_t const* src, int numBytes);
void f2i_indexFormatHandlerI8   (int* dst, uint8_t const* src, int numBytes);
