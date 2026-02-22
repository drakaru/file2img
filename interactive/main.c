#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>


/**
 * for now just a copy of main.c but will become a gui version, probably raylib+imgui
 */



#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "file2img/file2img.h"

f2i_color_format_t const* g_colorFormat = NULL;
f2i_block_format_t const* g_blockFormat = NULL;
f2i_index_format_t const* g_indexFormat = NULL;
int g_width = 256;
int g_tileWidth = 1;
int g_tileHeight = 1;
char const * g_outputPath = NULL;
int g_start = 0;
int g_paletteStart = 0;
int g_length = -1;

int g_argc;
char** g_argv;

bool flip_vertical;

void parseCommandLine(void) {
	while (1) {
		static struct option long_options[] = {
			{ "format",        required_argument, 0, 'f' },
			{ "list-formats",        no_argument, 0, 'F' },
			{ "tile",          required_argument, 0, 't' },
			{ "width",         required_argument, 0, 'w' },
			{ "output",        required_argument, 0, 'o' },
			{ "start",         required_argument, 0, 's' },
			{ "length",        required_argument, 0, 'n' },
			{ "index-format",  required_argument, 0, 'i' },
			{ "palette-start", required_argument, 0, 'p' },
			{ "flip-vertical",       no_argument, 0, 'v' },
			{ 0, 0, 0, 0 }
		};

		int option_index = 0;
		int const c = getopt_long(g_argc, g_argv, "f:Ft:w:o:s:n:i:p:vt:", long_options, &option_index);

		if (c == -1) {
			break;
		}

		switch (c) {
			case 'f': {
				char const* formatName = optarg;
				g_blockFormat = NULL;
				g_colorFormat = f2i_findColorFormat(formatName);
				if (!g_colorFormat) {
					g_blockFormat = f2i_findBlockFormat(formatName);
					if (!g_blockFormat) {
						eprintf("Unknown format specified: %s\n", formatName);
						exit(1);
					}
				}
				break;
			}
			case 'i': {
				char const* formatName = optarg;
				g_indexFormat = f2i_findIndexFormat(formatName);
				if (!g_indexFormat) {
					eprintf("Unknown index format specified: %s\n", formatName);
					exit(1);
				}
				break;
			}
			case 't': {
				// TODO: find an elegant way to get separate width/height
				g_tileHeight = g_tileWidth = strtol(optarg, NULL, 10);
				if (g_tileWidth <= 0) {
					eprintf("Tile size must be greater than zero.\n");
					exit(1);
				}
				break;
			}
			case 'w': {
				g_width = strtol(optarg, NULL, 10);
				if (g_width <= 0) {
					eprintf("Width must be greater than zero.\n");
					exit(1);
				}
				break;
			}
			case 'o': {
				g_outputPath = optarg;
				break;
			}
			case 's': {
				g_start = strtol(optarg, NULL, 10);
				if (g_start < 0) {
					eprintf("Start offset must be greater than or equal to zero.\n");
					exit(1);
				}
				break;
			}
			case 'p': {
				g_paletteStart = strtol(optarg, NULL, 10);
				if (g_start < 0) {
					eprintf("Palette start offset must be greater than or equal to zero.\n");
					exit(1);
				}
				break;
			}
			case 'n': {
				g_length = strtol(optarg, NULL, 10);
				if (g_length <= 0) {
					eprintf("Length must be greater than zero.\n");
					exit(1);
				}
				break;
			}
			case 'v': {
				flip_vertical = true;
				break;
			}
			case 'F': {
				printf("Available formats:\n");
				printf("- Color formats:\n");
				for (int i=0;i<f2i_num_color_formats;++i) {
					printf("  - %s\t\t(%s)\n", f2i_all_color_formats[i].id, f2i_all_color_formats[i].description);
				}
				printf("- Block formats:\n");
				for (int i=0;i<f2i_num_block_formats;++i) {
					printf("  - %s\t\t(%s)\n", f2i_all_block_formats[i].id, f2i_all_block_formats[i].description);
				}
				printf("- Index formats:\n");
				for (int i=0;i<f2i_num_index_formats;++i) {
					printf("  - %s\t\t(%s)\n", f2i_all_index_formats[i].id, f2i_all_index_formats[i].description);
				}
				exit(0);
			}
			default: {
				// silences missing default branch
				// do nothing as getopt already reports invalid options
				break;
			}
		}
	}
}

void earlySanityCheck(void) {
	if (optind >= g_argc) {
		puts("Usage:");
		puts("   file2img [options] <input file>");
		puts("");
		puts("Options:");
		puts("   -F,--list-formats    Print a list of available formats");
		puts("   -f,--format          Specify the color format (default: L8)");
		puts("   -t,--tile            Specify the tile size (default: 1/disabled)");
		puts("   -w,--width           Specify the target width (default: 256)");
		puts("   -o,--output          Specify the output path (default: out.png)");
		puts("   -s,--start           Specify the start offset (default: 0)");
		puts("   -n,--length          Specify the input byte count (default: all of them)");
		puts("   -i,--index-format    Specify the index map format (default: none)");
		puts("   -p,--palette-start   Specify the palette start offset (default: 0)");
		puts("   -v,--flip-vertically Specify the the output is flipped vertically");
		exit(0);
	}
	if (g_outputPath != NULL && optind + 1 < g_argc) {
		eprintf("Output path was specified along with multiple input files!\n");
		exit(1);
	}
	if (g_blockFormat && g_indexFormat) {
		eprintf("Cannot use block format %s as a palette source.\n", g_blockFormat->id);
		exit(1);
	}
	if (!g_colorFormat && !g_blockFormat && !g_indexFormat) {
		g_colorFormat = f2i_findColorFormat("l8");
	}
}

int calculatePixelCount(int numSrcBytes, f2i_color_format_t const* colorFormat, f2i_index_format_t const* indexFormat, f2i_block_format_t const* blockFormat)
{
	if (indexFormat) {
		return (numSrcBytes * 8) / indexFormat->bit_depth;
	} else if (blockFormat) {
		return (numSrcBytes * 8 * blockFormat->width * blockFormat->height) / blockFormat->bit_depth;
	} else {
		return (numSrcBytes * 8) / colorFormat->bit_depth;
	}
}

void applyTileLayout(f2i_rgba8888_t* buffer, int width, int height, int tileWidth, int tileHeight) {
	if ((width % tileWidth) != 0) {
		eprintf("Chosen layout must have a width divisible by %d.\n", tileWidth);
		exit(1);
	}
	if ((height % tileHeight) != 0) {
		eprintf("Chosen layout must have a height divisible by %d.\n", tileHeight);
		exit(1);
	}

	int const scratchPixelCount = width * tileHeight;
	int const numTileRows = height / tileHeight;
	f2i_rgba8888_t* scratch = NEW(f2i_rgba8888_t, scratchPixelCount);
	{
		for (int tileRow = 0; tileRow < numTileRows; ++tileRow) {
			for (int i = 0; i < scratchPixelCount; ++i) {
				int const xInBlock = i % tileWidth;
				int const yInBlock = (i / tileWidth) % tileHeight;
				int const blockIndex = i / (tileWidth * tileHeight);
				int const blockX = (blockIndex % (width /tileWidth)) * tileWidth;
				int const blockY = (blockIndex / (width /tileWidth)) * tileHeight;
				int const x = blockX + xInBlock;
				int const y = blockY + yInBlock;
				int const offset = y*width+x;
				scratch[offset] = buffer[i+tileRow*scratchPixelCount];
			}

			memcpy(buffer+tileRow*scratchPixelCount, scratch, (size_t)scratchPixelCount * sizeof(f2i_rgba8888_t));
		}
	}
	DELETE(scratch);
}

void processInputFile(char const* inputFilePath)
{
	FILE* fh = fopen(inputFilePath, "rb");
	{
		if (!fh) {
			eprintf("Failed to open %s\n", inputFilePath);
			return;
		}

		int srcLength = g_length;

		if (srcLength < 0) {
			// attempt to determine file length.
			// this will fail for things like /dev/random.
			fseek(fh, 0, SEEK_END);
			size_t const fileLength = ftell(fh);
			fseek(fh, 0, SEEK_SET);

			if (fileLength == 0) {
				eprintf("Failed to automatically determine length of '%s', or it's an empty file.\n", inputFilePath);
				eprintf("If this is some unbounded device like /dev/random, please specify an explicit length with -n\n");
				exit(1);
			}

			if (fileLength <= (size_t)g_start) {
				eprintf("Requested start position %d is beyond the end of the available data (%lu bytes).\n", g_start, fileLength);
				exit(1);
			}
			srcLength = (fileLength - g_start);
		}

		if (g_start != 0) {
			fseek(fh, g_start, SEEK_SET);
		}

		uint8_t* srcBuffer = NEW(uint8_t, srcLength);

		size_t const totalBytesRead = fread(srcBuffer, 1, srcLength, fh);
		if (totalBytesRead < (size_t)srcLength) {
			eprintf("Failed to read requested %d bytes, only %lu bytes were available.\n", srcLength, totalBytesRead);
			exit(1);
		}

		int const pixelCount = calculatePixelCount(srcLength, g_colorFormat, g_indexFormat, g_blockFormat);

		int width = g_width;
		int height = (pixelCount + width - 1) / width;

		if (g_blockFormat) {
			// ensure this width is valid
			if ((width % g_blockFormat->width) != 0) {
				eprintf("Requested block format %s requires a width divisible by %d.\n", g_blockFormat->id, g_blockFormat->width);
				exit(1);
			}

			// pad the height if necessary
			height = f2i_alignToMultiple(height, g_blockFormat->height);
		}

		// handle tile size
		if (g_tileWidth != 1 || g_tileHeight != 1) {
			if ((width % g_tileWidth) != 0) {
				eprintf("Width %d is not divisible by tile size %d.\n", width, g_tileWidth);
				exit(1);
			}
			if ((height % g_tileHeight) != 0) {
				if (g_blockFormat) {
					eprintf("Format %s is not trivially compatible with tile height %d.\n", g_blockFormat->id, g_tileHeight);
					exit(1);
				} else {
					height = f2i_alignToMultiple(height, g_tileHeight);
				}
			}
		}

		f2i_rgba8888_t* dstBuffer = NEW(f2i_rgba8888_t, width * height);
		if (!dstBuffer) {
			eprintf("Failed to allocate dstBuffer\n");
			exit(1);
		}
		memset(dstBuffer, 0, width * height * sizeof(f2i_rgba8888_t));
		int const dstComp = 4;

		if (g_indexFormat) {
			int const numPaletteEntries = (1 << g_indexFormat->bit_depth);
			int const paletteSizeBytes = (g_colorFormat->bit_depth * numPaletteEntries + 7) / 8;
			uint8_t* paletteSrcBuffer = NEW(uint8_t, paletteSizeBytes);

			fseek(fh, g_paletteStart, SEEK_SET);
			size_t const paletteBytesRead = fread(paletteSrcBuffer, 1, paletteSizeBytes, fh);
			if (paletteBytesRead < (size_t)paletteSizeBytes) {
				eprintf("Failed to read requested %d bytes for palette, only %lu bytes were available.\n", paletteSizeBytes, paletteBytesRead);
				exit(1);
			}

			f2i_rgba8888_t palette[numPaletteEntries];
			g_colorFormat->function(palette, paletteSrcBuffer, paletteSizeBytes);

			int indexBuffer[width * height];
			g_indexFormat->function(indexBuffer, srcBuffer, srcLength);

			for (int i = 0; i != pixelCount; ++i) {
				dstBuffer[i] = palette[indexBuffer[i]];
			}
		} else if (g_blockFormat) {
			g_blockFormat->function(dstBuffer, srcBuffer, width, srcLength);
		} else {
			g_colorFormat->function(dstBuffer, srcBuffer, srcLength);
		}

		DELETE(srcBuffer);

		if (g_tileWidth != 1 || g_tileHeight != 1) {
			applyTileLayout(dstBuffer, width, height, g_tileWidth, g_tileHeight);
		}

		const char* filename = g_outputPath;
		if (filename == NULL) {
			filename = "out.png";
		}

		if (flip_vertical) {
			stbi_flip_vertically_on_write(1);
		}
		stbi_write_png(filename, width, height, dstComp, dstBuffer, width * dstComp);

		DELETE(dstBuffer);
	}
	fclose(fh);
}

int main(int argc, char** argv) {
	g_argc = argc;
	g_argv = argv;
	
	parseCommandLine();
	earlySanityCheck();

	for (int i = optind; i < g_argc; ++i) {
		eprintf("Processing file %s\n", g_argv[i]);
		processInputFile(g_argv[i]);
	}

	return 0;
}
