CLI_SOURCES = \
	main.c

INTERACTIVE_SOURCES = \
	interactive/main.c

HEADERS = \
	include/stb_image_write.h

LIB_SOURCES = \
	libfile2img/src/file2img.c \
	libfile2img/src/blockFormatHandlers.c \
	libfile2img/src/colorFormatHandlers.c \
	libfile2img/src/indexFormatHandlers.c

LIB_OBJECTS := $(LIB_SOURCES:libfile2img/src/%.c=libfile2img/out/%.o)

LIB_HEADERS = \
	libfile2img/include/file2img/boilerplate.h \
	libfile2img/include/file2img/colorUtils.h \
	libfile2img/include/file2img/types.h \
	libfile2img/include/file2img/file2img.h \
	libfile2img/include/file2img/blockFormatHandlers.h \
	libfile2img/include/file2img/colorFormatHandlers.h \
	libfile2img/include/file2img/indexFormatHandlers.h

CFLAGS = \
	-std=c99 \
	-O3 \
	-Wall -Wextra -Wpedantic \
	-Ilibfile2img/include \
	-Iinclude

CC ?= clang

all: file2img ifile2img libfile2img.a

file2img: $(CLI_SOURCES) $(HEADERS) libfile2img.a
	$(CC) $(CLI_SOURCES) $(CFLAGS) libfile2img.a -o file2img

ifile2img: $(INTERACTIVE_SOURCES) $(HEADERS) libfile2img.a
	$(CC) $(INTERACTIVE_SOURCES) $(CFLAGS) libfile2img.a -o ifile2img

libfile2img.a: $(LIB_OBJECTS) $(LIB_HEADERS)
	ar rcs libfile2img.a $(LIB_OBJECTS)

$(LIB_OBJECTS): libfile2img/out/%.o: libfile2img/src/%.c
	$(CC) -c $^ -o $@ $(CFLAGS)

install: file2img
	cp file2img /usr/local/bin/file2img

uninstall:
	rm -f /usr/local/bin/file2img

clean:
	rm -f file2img ifile2img $(LIB_OBJECTS) libfile2img.a

.PHONY: all install uninstall clean
