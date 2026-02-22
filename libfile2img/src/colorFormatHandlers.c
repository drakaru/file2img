#include <string.h>
#include "file2img/colorFormatHandlers.h"
#include "file2img/colorUtils.h"

void f2i_colorFormatHandlerL1BE(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	for (int i = numBytes; i-- != 0;) {
		uint8_t const value = *src++;
		for (int j = 0; j != 8; ++j) {
			uint8_t const a = ((value<<j)&0x80) ? 0xff : 0x00;
			*dst++ = (f2i_rgba8888_t){a,a,a,0xff};
		}
	}
}

void f2i_colorFormatHandlerL1LE(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	for (int i = numBytes; i-- != 0;) {
		uint8_t const value = *src++;
		for (int j = 0; j != 8; ++j) {
			uint8_t const a = ((value>>j)&0x01) ? 0xff : 0x00;
			*dst++ = (f2i_rgba8888_t){a,a,a,0xff};
		}
	}
}

void f2i_colorFormatHandlerL2BE(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	for (int i = numBytes; i-- != 0;) {
		uint8_t const value = *src++;
		uint8_t const a = f2i_expand2((value >> 6) & 0x3);
		uint8_t const b = f2i_expand2((value >> 4) & 0x3);
		uint8_t const c = f2i_expand2((value >> 2) & 0x3);
		uint8_t const d = f2i_expand2(value & 0x3);
		*dst++ = (f2i_rgba8888_t){a,a,a,0xff};
		*dst++ = (f2i_rgba8888_t){b,b,b,0xff};
		*dst++ = (f2i_rgba8888_t){c,c,c,0xff};
		*dst++ = (f2i_rgba8888_t){d,d,d,0xff};
	}
}

void f2i_colorFormatHandlerL2LE(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	for (int i = numBytes; i-- != 0;) {
		uint8_t const value = *src++;
		uint8_t const a = f2i_expand2((value >> 6) & 0x3);
		uint8_t const b = f2i_expand2((value >> 4) & 0x3);
		uint8_t const c = f2i_expand2((value >> 2) & 0x3);
		uint8_t const d = f2i_expand2(value & 0x3);
		*dst++ = (f2i_rgba8888_t){d,d,d,0xff};
		*dst++ = (f2i_rgba8888_t){c,c,c,0xff};
		*dst++ = (f2i_rgba8888_t){b,b,b,0xff};
		*dst++ = (f2i_rgba8888_t){a,a,a,0xff};
	}
}

void f2i_colorFormatHandlerL4BE(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	for (int i = numBytes; i-- != 0;) {
		uint8_t const value = *src++;
		uint8_t const hi = f2i_expand4(value >> 4);
		uint8_t const lo = f2i_expand4(value & 0xf);
		*dst++ = (f2i_rgba8888_t){hi,hi,hi,0xff};
		*dst++ = (f2i_rgba8888_t){lo,lo,lo,0xff};
	}
}

void f2i_colorFormatHandlerL4LE(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	for (int i = numBytes; i-- != 0;) {
		uint8_t const value = *src++;
		uint8_t const hi = f2i_expand4(value >> 4);
		uint8_t const lo = f2i_expand4(value & 0xf);
		*dst++ = (f2i_rgba8888_t){lo,lo,lo,0xff};
		*dst++ = (f2i_rgba8888_t){hi,hi,hi,0xff};
	}
}

void f2i_colorFormatHandlerL8(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	for (int i = numBytes; i-- != 0; ++dst, ++src) {
		*dst = (f2i_rgba8888_t){*src,*src,*src,0xff};
	}
}

void f2i_colorFormatHandlerRGB565BE(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = f2i_convertRGB565(f2i_readU16BE(&src));
		numBytes -= 2;
	}
}

void f2i_colorFormatHandlerRGB565LE(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = f2i_convertRGB565(f2i_readU16LE(&src));
		numBytes -= 2;
	}
}

void f2i_colorFormatHandlerBGR565BE(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = f2i_convertBGR565(f2i_readU16BE(&src));
		numBytes -= 2;
	}
}

void f2i_colorFormatHandlerBGR565LE(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = f2i_convertBGR565(f2i_readU16LE(&src));
		numBytes -= 2;
	}
}

void f2i_colorFormatHandlerARGB1555BE(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = f2i_convertARGB1555(f2i_readU16BE(&src));
		numBytes -= 2;
	}
}

void f2i_colorFormatHandlerARGB1555LE(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = f2i_convertARGB1555(f2i_readU16LE(&src));
		numBytes -= 2;
	}
}

void f2i_colorFormatHandlerABGR1555BE(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = f2i_convertABGR1555(f2i_readU16BE(&src));
		numBytes -= 2;
	}
}

void f2i_colorFormatHandlerABGR1555LE(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = f2i_convertABGR1555(f2i_readU16LE(&src));
		numBytes -= 2;
	}
}

void f2i_colorFormatHandlerXRGB1555BE(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = f2i_convertXRGB1555(f2i_readU16BE(&src));
		numBytes -= 2;
	}
}

void f2i_colorFormatHandlerXRGB1555LE(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = f2i_convertXRGB1555(f2i_readU16LE(&src));
		numBytes -= 2;
	}
}

void f2i_colorFormatHandlerXBGR1555BE(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = f2i_convertXBGR1555(f2i_readU16BE(&src));
		numBytes -= 2;
	}
}

void f2i_colorFormatHandlerXBGR1555LE(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = f2i_convertXBGR1555(f2i_readU16LE(&src));
		numBytes -= 2;
	}
}

void f2i_colorFormatHandlerARGB4444BE(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = f2i_convertARGB4444(f2i_readU16BE(&src));
		numBytes -= 2;
	}
}

void f2i_colorFormatHandlerARGB4444LE(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = f2i_convertARGB4444(f2i_readU16LE(&src));
		numBytes -= 2;
	}
}

void f2i_colorFormatHandlerRGB888(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 3) {
		uint8_t const r = *src++;
		uint8_t const g = *src++;
		uint8_t const b = *src++;
		*dst++ = (f2i_rgba8888_t){r,g,b,0xff};
		numBytes -= 3;
	}
}

void f2i_colorFormatHandlerBGR888(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 3) {
		uint8_t const b = *src++;
		uint8_t const g = *src++;
		uint8_t const r = *src++;
		*dst++ = (f2i_rgba8888_t){r,g,b,0xff};
		numBytes -= 3;
	}
}

void f2i_colorFormatHandlerARGB8888(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 4) {
		uint8_t const a = *src++;
		uint8_t const r = *src++;
		uint8_t const g = *src++;
		uint8_t const b = *src++;
		*dst++ = (f2i_rgba8888_t){r,g,b,a};
		numBytes -= 4;
	}
}

void f2i_colorFormatHandlerABGR8888(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 4) {
		uint8_t const a = *src++;
		uint8_t const b = *src++;
		uint8_t const g = *src++;
		uint8_t const r = *src++;
		*dst++ = (f2i_rgba8888_t){r,g,b,a};
		numBytes -= 4;
	}
}

void f2i_colorFormatHandlerRGBA8888(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	// special case for this layout
	numBytes -= (numBytes % 4);
	memcpy(dst, src, numBytes);
}

void f2i_colorFormatHandlerBGRA8888(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 4) {
		uint8_t const b = *src++;
		uint8_t const g = *src++;
		uint8_t const r = *src++;
		uint8_t const a = *src++;
		*dst++ = (f2i_rgba8888_t){r,g,b,a};
		numBytes -= 4;
	}
}

void f2i_colorFormatHandlerXRGB8888(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 4) {
		++src; //uint8_t const x = *src++;
		uint8_t const r = *src++;
		uint8_t const g = *src++;
		uint8_t const b = *src++;
		*dst++ = (f2i_rgba8888_t){r,g,b,0xff};
		numBytes -= 4;
	}
}

void f2i_colorFormatHandlerXBGR8888(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 4) {
		++src; //uint8_t const x = *src++;
		uint8_t const b = *src++;
		uint8_t const g = *src++;
		uint8_t const r = *src++;
		*dst++ = (f2i_rgba8888_t){r,g,b,0xff};
		numBytes -= 4;
	}
}

void f2i_colorFormatHandlerRGBX8888(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 4) {
		uint8_t const r = *src++;
		uint8_t const g = *src++;
		uint8_t const b = *src++;
		++src; //uint8_t const x = *src++;
		*dst++ = (f2i_rgba8888_t){r,g,b,0xff};
		numBytes -= 4;
	}
}

void f2i_colorFormatHandlerBGRX8888(f2i_rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 4) {
		uint8_t const b = *src++;
		uint8_t const g = *src++;
		uint8_t const r = *src++;
		++src; //uint8_t const x = *src++;
		*dst++ = (f2i_rgba8888_t){r,g,b,0xff};
		numBytes -= 4;
	}
}
