#include "file2img/file2img.h"

f2i_color_format_t f2i_all_color_formats[] = {
	{ .id="l1be",       .bit_depth= 1, .function=f2i_colorFormatHandlerL1BE,       .description="1-bit luminance format, big-endian (MSB first)", },
	{ .id="l1le",       .bit_depth= 1, .function=f2i_colorFormatHandlerL1LE,       .description="1-bit luminance format, little-endian (LSB first)", },
	{ .id="l2be",       .bit_depth= 2, .function=f2i_colorFormatHandlerL2BE,       .description="2-bit luminance format, big-endian (MSB first)", },
	{ .id="l2le",       .bit_depth= 2, .function=f2i_colorFormatHandlerL2LE,       .description="2-bit luminance format, little-endian (LSB first)", },
	{ .id="l4be",       .bit_depth= 4, .function=f2i_colorFormatHandlerL4BE,       .description="4-bit luminance format, big-endian (MSB first)", },
	{ .id="l4le",       .bit_depth= 4, .function=f2i_colorFormatHandlerL4LE,       .description="4-bit luminance format, little-endian (LSB first)", },
	{ .id="l8",         .bit_depth= 8, .function=f2i_colorFormatHandlerL8,         .description="8-bit luminance format", },

	{ .id="rgb565be",   .bit_depth=16, .function=f2i_colorFormatHandlerRGB565BE,   .description="RGB565 format, big-endian    (RRRRRGGG GGGBBBBB)", },
	{ .id="rgb565le",   .bit_depth=16, .function=f2i_colorFormatHandlerRGB565LE,   .description="RGB565 format, little-endian (GGGBBBBB RRRRRGGG)", },
	{ .id="bgr565be",   .bit_depth=16, .function=f2i_colorFormatHandlerBGR565BE,   .description="BGR565 format, big-endian    (BBBBBGGG GGGRRRRR)", },
	{ .id="bgr565le",   .bit_depth=16, .function=f2i_colorFormatHandlerBGR565LE,   .description="BGR565 format, little-endian (GGGRRRRR BBBBBGGG)", },

	{ .id="argb4444be", .bit_depth=16, .function=f2i_colorFormatHandlerARGB4444BE, .description="ARGB4444 format, big-endian    (AAAARRRR GGGGBBBB)", },
	{ .id="argb4444le", .bit_depth=16, .function=f2i_colorFormatHandlerARGB4444LE, .description="ARGB4444 format, little-endian (GGGGBBBB AAAARRRR)", },

	{ .id="argb1555be", .bit_depth=16, .function=f2i_colorFormatHandlerARGB1555BE, .description="ARGB1555 format, big-endian    (ARRRRRGG GGGBBBBB)", },
	{ .id="argb1555le", .bit_depth=16, .function=f2i_colorFormatHandlerARGB1555LE, .description="ARGB1555 format, little-endian (GGGBBBBB ARRRRRGG)", },
	{ .id="abgr1555be", .bit_depth=16, .function=f2i_colorFormatHandlerABGR1555BE, .description="ABGR1555 format, big-endian    (ABBBBBGG GGGRRRRR)", },
	{ .id="abgr1555le", .bit_depth=16, .function=f2i_colorFormatHandlerABGR1555LE, .description="ABGR1555 format, little-endian (GGGRRRRR ABBBBBGG)", },

	{ .id="xrgb1555be", .bit_depth=16, .function=f2i_colorFormatHandlerXRGB1555BE, .description="XRGB1555 format, big-endian    (no alpha) (XRRRRRGG GGGBBBBB)", },
	{ .id="xrgb1555le", .bit_depth=16, .function=f2i_colorFormatHandlerXRGB1555LE, .description="XRGB1555 format, little-endian (no alpha) (GGGBBBBB XRRRRRGG)", },
	{ .id="xbgr1555be", .bit_depth=16, .function=f2i_colorFormatHandlerXBGR1555BE, .description="XBGR1555 format, big-endian    (no alpha) (XBBBBBGG GGGRRRRR)", },
	{ .id="xbgr1555le", .bit_depth=16, .function=f2i_colorFormatHandlerXBGR1555LE, .description="XBGR1555 format, little-endian (no alpha) (GGGRRRRR XBBBBBGG)", },

	{ .id="rgb888",     .bit_depth=24, .function=f2i_colorFormatHandlerRGB888,     .description="RGB888 format (RRRRRRRR GGGGGGGG BBBBBBBB)" },
	{ .id="bgr888",     .bit_depth=24, .function=f2i_colorFormatHandlerBGR888,     .description="BGR888 format (BBBBBBBB GGGGGGGG RRRRRRRR)" },

	{ .id="argb8888",   .bit_depth=32, .function=f2i_colorFormatHandlerARGB8888,   .description="ARGB8888 format (AAAAAAAA RRRRRRRR GGGGGGGG BBBBBBBB)" },
	{ .id="abgr8888",   .bit_depth=32, .function=f2i_colorFormatHandlerABGR8888,   .description="ABGR8888 format (AAAAAAAA BBBBBBBB GGGGGGGG RRRRRRRR)" },
	{ .id="rgba8888",   .bit_depth=32, .function=f2i_colorFormatHandlerRGBA8888,   .description="RGBA8888 format (RRRRRRRR GGGGGGGG BBBBBBBB AAAAAAAA)" },
	{ .id="bgra8888",   .bit_depth=32, .function=f2i_colorFormatHandlerBGRA8888,   .description="BGRA8888 format (BBBBBBBB GGGGGGGG RRRRRRRR AAAAAAAA)" },
	{ .id="xrgb8888",   .bit_depth=32, .function=f2i_colorFormatHandlerXRGB8888,   .description="XRGB8888 format (XXXXXXXX RRRRRRRR GGGGGGGG BBBBBBBB)" },
	{ .id="xbgr8888",   .bit_depth=32, .function=f2i_colorFormatHandlerXBGR8888,   .description="XBGR8888 format (XXXXXXXX BBBBBBBB GGGGGGGG RRRRRRRR)" },
	{ .id="rgbx8888",   .bit_depth=32, .function=f2i_colorFormatHandlerRGBX8888,   .description="RGBX8888 format (RRRRRRRR GGGGGGGG BBBBBBBB XXXXXXXX)" },
	{ .id="bgrx8888",   .bit_depth=32, .function=f2i_colorFormatHandlerBGRX8888,   .description="BGRX8888 format (BBBBBBBB GGGGGGGG RRRRRRRR XXXXXXXX)" },
};

f2i_index_format_t f2i_all_index_formats[] = {
	{ .id="i4be",       .bit_depth= 4, .function=f2i_indexFormatHandlerI4BE,       .description="4-bit index format, big-endian", },
	{ .id="i4le",       .bit_depth= 4, .function=f2i_indexFormatHandlerI4LE,       .description="4-bit index format, little-endian", },
	{ .id="i8",         .bit_depth= 8, .function=f2i_indexFormatHandlerI8,         .description="8-bit index format", },
};

f2i_block_format_t f2i_all_block_formats[] = {
	{ .id="dxt1",       .bit_depth= 64, .width=4, .height=4, .function=f2i_blockFormatHandlerDXT1,    .description="DXT1 block format", },
	{ .id="dxt5",       .bit_depth=128, .width=4, .height=4, .function=f2i_blockFormatHandlerDXT5,    .description="DXT5 block format", },

	{ .id="gameboy",    .bit_depth=128, .width=8, .height=8, .function=f2i_blockFormatHandlerGameboy, .description="Game Boy 2-bit tile format" },
	{ .id="nes",        .bit_depth=128, .width=8, .height=8, .function=f2i_blockFormatHandlerNES,     .description="NES 2-bit tile format" },
};

int const f2i_num_color_formats = array_size(f2i_all_color_formats);
int const f2i_num_index_formats = array_size(f2i_all_index_formats);
int const f2i_num_block_formats = array_size(f2i_all_block_formats);
