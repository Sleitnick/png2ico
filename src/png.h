#ifndef _PNG_H_
#define _PNG_H_

#include <stdint.h>
#include <stdlib.h>
#include "err.h"

#define PNG_OK 0
#define PNG_ERR_PNG_INFO_NULL 1
#define PNG_ERR_FAILED_TO_OPEN 2
#define PNG_ERR_READ_EOF 3
#define PNG_ERR_READ_ERR 4
#define PNG_ERR_INVALID_PNG 5
#define PNG_ERR_ALLOC 6

typedef struct PngIHDR
{
	uint32_t width;
	uint32_t height;
	uint8_t bit_depth;
	uint8_t color_type;
	uint8_t compression_method;
	uint8_t filter_method;
	uint8_t interlace_method;
} PngIHDR;

typedef struct PngInfo
{
	PngIHDR ihdr;
	size_t data_size;
	void* data;
} PngInfo;

typedef struct PngChunk
{
	size_t length;
	unsigned char chunk_type[4];
	unsigned char* chunk_data;
	uint32_t crc;
} PngChunk;

error_t png_get_info(const char* filepath, PngInfo* info);
error_t png_get_width_height(const char* filename, int* width, int* height);
void png_free_info(PngInfo* info);

#endif
