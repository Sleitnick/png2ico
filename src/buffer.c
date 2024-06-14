#include "buffer.h"

#include <stdlib.h>
#include <string.h>

#define ASSERT_READ(f, bytes_read, expected_size) (bytes_read < expected_size ? (feof(f) ? ERR_EOF : ferror(f) ? ERR_READ : OK) : OK)
#define ASSERT_WRITE(f, bytes_written, expected_size) (bytes_written < expected_size ? (feof(f) ? ERR_EOF : ferror(f) ? ERR_WRITE : OK) : OK)

static error_t last_status = OK;

static error_t status(int s)
{
	last_status = s;
	return s;
}

error_t buffer_open(const char* filepath, Buffer* buf, int mode)
{
	FILE* f = NULL;
	switch (mode) {
		case BUFFER_MODE_READ:
			f = fopen(filepath, "rb");
			break;
		case BUFFER_MODE_WRITE:
			f = fopen(filepath, "wb");
			break;
		default:
			return status(ERR_OPEN_FILE);
	}
	if (f == NULL)
	{
		return status(ERR_OPEN_FILE);
	}

	buf->f = f;

	return status(OK);
}

void buffer_close(Buffer* buf)
{
	if (buf->f != NULL)
	{
		fclose(buf->f);
	}
}

error_t buffer_readi8(Buffer* buf, int8_t* n)
{
	size_t r = fread(n, sizeof(unsigned char), 1, buf->f);
	return status(r < 1 ? ERR_READ : OK);
}

error_t buffer_readu8(Buffer* buf, uint8_t* n)
{
	size_t r = fread(n, sizeof(unsigned char), 1, buf->f);
	return status(r < 1 ? ERR_READ : OK);
}

error_t buffer_readi16(Buffer* buf, int16_t* n)
{
	size_t r = fread(n, sizeof(unsigned char), 2, buf->f);
	return status(r < 2 ? ERR_READ : OK);
}

error_t buffer_readu16(Buffer* buf, uint16_t* n)
{
	size_t r = fread(n, sizeof(unsigned char), 2, buf->f);
	return status(r < 2 ? ERR_READ : OK);
}

error_t buffer_readi32(Buffer* buf, int32_t* n)
{
	size_t r = fread(n, sizeof(unsigned char), 4, buf->f);
	return status(r < 4 ? ERR_READ : OK);
}

error_t buffer_readu32(Buffer* buf, uint32_t* n)
{
	size_t r = fread(n, sizeof(unsigned char), 4, buf->f);
	return status(r < 4 ? ERR_READ : OK);
}

error_t buffer_readchunk(Buffer* buf, size_t size, size_t len, void* dst)
{
	size_t r = fread(dst, size, len, buf->f);
	return status(ASSERT_READ(buf->f, r, size));
}

error_t buffer_writei8(Buffer* buf, int8_t n)
{
	size_t w = fwrite(&n, sizeof(unsigned char), 1, buf->f);
	return status(w < 1 ? ERR_WRITE : OK);
}

error_t buffer_writeu8(Buffer* buf, uint8_t n)
{
	size_t w = fwrite(&n, sizeof(unsigned char), 1, buf->f);
	return status(w < 1 ? ERR_WRITE : OK);
}

error_t buffer_writei16(Buffer* buf, int16_t n)
{
	size_t w = fwrite(&n, sizeof(unsigned char), 2, buf->f);
	return status(w < 2 ? ERR_WRITE : OK);
}

error_t buffer_writeu16(Buffer* buf, uint16_t n)
{
	size_t w = fwrite(&n, sizeof(unsigned char), 2, buf->f);
	return status(w < 2 ? ERR_WRITE : OK);
}

error_t buffer_writei32(Buffer* buf, int32_t n)
{
	size_t w = fwrite(&n, sizeof(unsigned char), 4, buf->f);
	return status(w < 4 ? ERR_WRITE : OK);
}

error_t buffer_writeu32(Buffer* buf, uint32_t n)
{
	size_t w = fwrite(&n, sizeof(unsigned char), 4, buf->f);
	return status(w < 4 ? ERR_WRITE : OK);
}

error_t buffer_writechunk(Buffer* buf, size_t size, size_t len, void* src)
{
	size_t w = fwrite(src, size, len, buf->f);
	return status(ASSERT_WRITE(buf->f, w, size));
}

int buffer_eof(Buffer* buf)
{
	return feof(buf->f);
}

error_t buffer_status(void)
{
	return last_status;
}
