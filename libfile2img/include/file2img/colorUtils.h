#pragma once

#include "types.h"

inline uint8_t f2i_expand6(uint8_t a) { return (a << 2) | (a >> 4); }
inline uint8_t f2i_expand5(uint8_t a) { return (a << 3) | (a >> 2); }
inline uint8_t f2i_expand4(uint8_t a) { return (a << 4) | a; }
inline uint8_t f2i_expand2(uint8_t a) { return f2i_expand4((a << 2) | a); }

inline uint16_t f2i_readU16BE(uint8_t const** src) {
	uint16_t const hi = (*src)[0];
	uint16_t const lo = (*src)[1];
	*src += 2;
	return (hi<<8) | lo;
}

inline uint16_t f2i_readU16LE(uint8_t const** src) {
	uint16_t const lo = (*src)[0];
	uint16_t const hi = (*src)[1];
	*src += 2;
	return (hi<<8) | lo;
}

inline uint32_t f2i_readU32LE(uint8_t const** src) {
	uint32_t const a = (*src)[0];
	uint32_t const b = (*src)[1];
	uint32_t const c = (*src)[2];
	uint32_t const d = (*src)[3];
	*src += 4;
	return (d<<24) | (c<<16) | (b<<8) | a;
}

inline uint64_t f2i_readU48LE(uint8_t const** src) {
	uint64_t const a = (*src)[0];
	uint64_t const b = (*src)[1];
	uint64_t const c = (*src)[2];
	uint64_t const d = (*src)[3];
	uint64_t const e = (*src)[4];
	uint64_t const f = (*src)[5];
	*src += 6;
	return (f<<40) | (e<<32) | (d<<24) | (c<<16) | (b<<8) | a;
}

inline f2i_rgba8888_t f2i_convertRGB565(uint16_t value) {
	uint8_t const r = f2i_expand5(value >> 11);
	uint8_t const g = f2i_expand6((value >> 5) & 0x3f);
	uint8_t const b = f2i_expand5(value & 0x1f);
	return (f2i_rgba8888_t){r,g,b,0xff};
}

inline f2i_rgba8888_t f2i_convertBGR565(uint16_t value) {
	uint8_t const r = f2i_expand5(value & 0x1f);
	uint8_t const g = f2i_expand6((value >> 5) & 0x3f);
	uint8_t const b = f2i_expand5(value >> 11);
	return (f2i_rgba8888_t){r,g,b,0xff};
}

inline f2i_rgba8888_t f2i_convertARGB1555(uint16_t value) {
	uint8_t const a = (value & 0x8000) != 0 ? 0xff : 0x00;
	uint8_t const r = f2i_expand5((value >> 10) & 0x1f);
	uint8_t const g = f2i_expand5((value >> 5) & 0x1f);
	uint8_t const b = f2i_expand5(value & 0x1f);
	return (f2i_rgba8888_t){r,g,b,a};
}

inline f2i_rgba8888_t f2i_convertABGR1555(uint16_t value) {
	uint8_t const a = (value & 0x8000) != 0 ? 0xff : 0x00;
	uint8_t const r = f2i_expand5(value & 0x1f);
	uint8_t const g = f2i_expand5((value >> 5) & 0x1f);
	uint8_t const b = f2i_expand5((value >> 10) & 0x1f);
	return (f2i_rgba8888_t){r,g,b,a};
}

inline f2i_rgba8888_t f2i_convertXRGB1555(uint16_t value) {
	uint8_t const r = f2i_expand5((value >> 10) & 0x1f);
	uint8_t const g = f2i_expand5((value >> 5) & 0x1f);
	uint8_t const b = f2i_expand5(value & 0x1f);
	return (f2i_rgba8888_t){r,g,b,0xff};
}

inline f2i_rgba8888_t f2i_convertXBGR1555(uint16_t value) {
	uint8_t const r = f2i_expand5(value & 0x1f);
	uint8_t const g = f2i_expand5((value >> 5) & 0x1f);
	uint8_t const b = f2i_expand5((value >> 10) & 0x1f);
	return (f2i_rgba8888_t){r,g,b,0xff};
}

inline f2i_rgba8888_t f2i_convertARGB4444(uint16_t value) {
	uint8_t const a = f2i_expand4(value >> 12);
	uint8_t const r = f2i_expand4((value >> 8) & 0xf);
	uint8_t const g = f2i_expand4((value >> 4) & 0xf);
	uint8_t const b = f2i_expand4(value & 0xf);
	return (f2i_rgba8888_t){r,g,b,a};
}
