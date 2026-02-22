#pragma once

#include <stdbool.h>
#include <string.h>

#define array_size(x) (sizeof(x)/sizeof(x[0]))

#define eprintf(...) fprintf(stderr, __VA_ARGS__)

#define NEW(type, count) (type*)malloc(sizeof(type)*(count))
#define DELETE(ptr) free(ptr)

inline bool f2i_strEqual(char const* a, char const* b) {
	return strcmp(a,b)==0;
}

inline bool f2i_charEqualIgnoreCaseAssumeAscii(char a, char b) {
	char const mask = (char)0xdf;
	char const aa = (char)(a & mask);
	char const bb = (char)(b & mask);
	return (a==b) || ((aa == bb) && (aa >= 'A') && (aa <= 'Z'));
}

inline bool f2i_strEqualIgnoreCaseAssumeAscii(char const* a, char const* b) {
	while (*a && *b) {
		if (!f2i_charEqualIgnoreCaseAssumeAscii(*a, *b)) {
			return false;
		}
		++a;
		++b;
	}
	return *a == *b;
}

inline int f2i_alignToMultiple(int a, int divisor)
{
	if (divisor <= 1)
		return a;

	if ((a % divisor) == 0)
		return a;

	return a + divisor - (a % divisor);
}
