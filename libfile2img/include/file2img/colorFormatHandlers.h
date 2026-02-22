#pragma once

#include "types.h"

void f2i_colorFormatHandlerL1BE       (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);
void f2i_colorFormatHandlerL1LE       (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);
void f2i_colorFormatHandlerL2BE       (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);
void f2i_colorFormatHandlerL2LE       (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);
void f2i_colorFormatHandlerL4BE       (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);
void f2i_colorFormatHandlerL4LE       (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);
void f2i_colorFormatHandlerL8         (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);

void f2i_colorFormatHandlerRGB565BE   (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);
void f2i_colorFormatHandlerRGB565LE   (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);
void f2i_colorFormatHandlerBGR565BE   (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);
void f2i_colorFormatHandlerBGR565LE   (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);

void f2i_colorFormatHandlerARGB4444BE (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);
void f2i_colorFormatHandlerARGB4444LE (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);

void f2i_colorFormatHandlerARGB1555BE (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);
void f2i_colorFormatHandlerARGB1555LE (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);
void f2i_colorFormatHandlerABGR1555BE (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);
void f2i_colorFormatHandlerABGR1555LE (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);

void f2i_colorFormatHandlerXRGB1555BE (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);
void f2i_colorFormatHandlerXRGB1555LE (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);
void f2i_colorFormatHandlerXBGR1555BE (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);
void f2i_colorFormatHandlerXBGR1555LE (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);

void f2i_colorFormatHandlerRGB888     (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);
void f2i_colorFormatHandlerBGR888     (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);

void f2i_colorFormatHandlerARGB8888   (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);
void f2i_colorFormatHandlerABGR8888   (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);
void f2i_colorFormatHandlerRGBA8888   (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);
void f2i_colorFormatHandlerBGRA8888   (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);

void f2i_colorFormatHandlerXRGB8888   (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);
void f2i_colorFormatHandlerXBGR8888   (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);
void f2i_colorFormatHandlerRGBX8888   (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);
void f2i_colorFormatHandlerBGRX8888   (f2i_rgba8888_t* dst, uint8_t const* src, int numBytes);
