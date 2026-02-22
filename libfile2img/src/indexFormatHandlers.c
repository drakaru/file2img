#include "file2img/indexFormatHandlers.h"

void f2i_indexFormatHandlerI4BE(int* dst, uint8_t const* src, int numBytes) {
	for (int i = numBytes; i-- != 0;) {
		uint8_t const value = *src++;
		uint8_t const hi = (value >> 4);
		uint8_t const lo = (value & 0xf);
		*dst++ = (int)hi;
		*dst++ = (int)lo;
	}
}

void f2i_indexFormatHandlerI4LE(int* dst, uint8_t const* src, int numBytes) {
	for (int i = numBytes; i-- != 0;) {
		uint8_t const value = *src++;
		uint8_t const hi = (value >> 4);
		uint8_t const lo = (value & 0xf);
		*dst++ = (int)lo;
		*dst++ = (int)hi;
	}
}

void f2i_indexFormatHandlerI8(int* dst, uint8_t const* src, int numBytes) {
	for (int i = numBytes; i-- != 0; ++dst, ++src) {
		*dst = (int)*src;
	}
}
