#include "png.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "buffer.h"

#define SWAP_32(n) \
	(((n) >> 24) & 0xff) | \
	(((n) << 8) & 0xff0000) | \
	(((n) >> 8) & 0xff00) | \
	(((n) << 24) & 0xff000000)

static error_t read_and_verify_header(Buffer* buf)
{
	// Read the 8-byte header:
	unsigned char header[8];
	int header_res = buffer_readchunk(buf, sizeof(unsigned char), 8, header);
	if (header_res != OK)
	{
		switch (header_res) {
			case ERR_EOF:
				return ERR_EOF;
			case ERR_READ:
				return ERR_READ;
			default:
				break;
		}
	}

	// Verify the header: 89 50 4E 47 0D 0A 1A 0A
	unsigned char expected_header[8] = { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a };
	for (int i = 0; i < 8; i++)
	{
		if (header[i] != expected_header[i])
		{
			return ERR_PNG_INVALID;
		}
	}

	return OK;
}

static error_t get_chunk_length_and_type(Buffer* buf, uint32_t* length, unsigned char chunk_type[4])
{
	// Chunk length
	uint32_t len;
	if (buffer_readu32(buf, &len) != OK)
	{
		return buffer_status();
	}

	// PNG encodes this in big-endian; swap to little-endian
	*length = SWAP_32(len);

	// Chunk type
	if (buffer_readchunk(buf, sizeof(unsigned char), 4, chunk_type) != OK)
	{
		return buffer_status();
	}

	return OK;
}

/*
static error_t get_next_chunk(Buffer* buf)
{
	// Chunk length and type
	uint32_t length;
	unsigned char chunk_type[4];
	if (get_chunk_length_and_type(buf, &length, chunk_type) != OK)
	{
		return buffer_status();
	}

	// Chunk data
	unsigned char* chunk_data = NULL;
	if (length > 0)
	{
		chunk_data = malloc(sizeof(unsigned char) * length);
		if (chunk_data == NULL)
		{
			return PNG_ERR_ALLOC;
		}
	}

	// CRC
	uint32_t crc;
	if (buffer_readu32(buf, &crc) != OK)
	{
		return buffer_status();
	}

	return PNG_OK;
}
*/

static error_t get_ihdr(Buffer* buf, PngIHDR* ihdr)
{
	// Chunk length and type
	uint32_t length = 0;
	unsigned char chunk_type[4] = { 'A', 'B', 'C', 'D' };
	if (get_chunk_length_and_type(buf, &length, chunk_type) != OK)
	{
		return buffer_status();
	}

	// Verify chunk type
	unsigned char chunk_type_expected[4] = { 'I', 'H', 'D', 'R' };
	if (memcmp(chunk_type, chunk_type_expected, sizeof(chunk_type)) != 0) {
		return ERR_PNG_INVALID;
	}

	// Verify chunk length
	if (length != 13) {
		return ERR_PNG_INVALID;
	}

	// Read IHDR data
	if (buffer_readu32(buf, &ihdr->width) != OK) return buffer_status();
	if (buffer_readu32(buf, &ihdr->height) != OK) return buffer_status();
	if (buffer_readu8(buf, &ihdr->bit_depth) != OK) return buffer_status();
	if (buffer_readu8(buf, &ihdr->color_type) != OK) return buffer_status();
	if (buffer_readu8(buf, &ihdr->compression_method) != OK) return buffer_status();
	if (buffer_readu8(buf, &ihdr->filter_method) != OK) return buffer_status();
	if (buffer_readu8(buf, &ihdr->interlace_method) != OK) return buffer_status();

	// Convert width/height from big-endian to little-endian
	ihdr->width = SWAP_32(ihdr->width);
	ihdr->height = SWAP_32(ihdr->height);

	return OK;
}

error_t png_get_info(const char* filepath, PngInfo* info)
{
	if (info == NULL)
	{
		return ERR_NULL;
	}

	Buffer buf;
	if (buffer_open(filepath, &buf, BUFFER_MODE_READ) != OK)
	{
		buffer_close(&buf);
		return ERR_OPEN_FILE;
	}

	int verify_header = read_and_verify_header(&buf);
	if (verify_header != OK)
	{
		buffer_close(&buf);
		return verify_header;
	}

	int ihdr_status = get_ihdr(&buf, &info->ihdr);
	if (ihdr_status != OK)
	{
		buffer_close(&buf);
		return ERR_PNG_INVALID;
	}

	// Stop here. Nothing more than IHDR chunk is needed.

	// Read in the full file
	rewind(buf.f);
	struct stat f_stat;
	stat(filepath, &f_stat);
	void* data = malloc(sizeof(char) * f_stat.st_size);
	if (data == NULL)
	{
		buffer_close(&buf);
		return ERR_ALLOC;
	}
	size_t r = fread(data, f_stat.st_size, 1, buf.f);
	if (r < f_stat.st_size)
	{
		free(data);
		buffer_close(&buf);
		return ERR_READ;
	}
	info->data = data;
	info->data_size = f_stat.st_size;

	buffer_close(&buf);
	return OK;
}

error_t png_get_width_height(const char* filepath, int* width, int* height)
{
	PngInfo info;
	int err = png_get_info(filepath, &info);
	if (err != OK)
	{
		return err;
	}

	*width = info.ihdr.width;
	*height = info.ihdr.height;

	png_free_info(&info);

	return OK;
}

void png_free_info(PngInfo* info)
{
	free(info->data);
}
