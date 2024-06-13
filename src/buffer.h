#ifndef _BUFFER_H_
#define _BUFFER_H_

#define BUFFER_MODE_READ 0
#define BUFFER_MODE_WRITE 1

#include <stdio.h>
#include <stdint.h>
#include "err.h"

typedef struct Buffer
{
	FILE* f;

} Buffer;

error_t buffer_open(const char* filepath, Buffer* buf, int mode);
void buffer_close(Buffer* buf);

error_t buffer_readi8(Buffer* buf, int8_t* n);
error_t buffer_readu8(Buffer* buf, u_int8_t* n);

error_t buffer_readi16(Buffer* buf, int16_t* n);
error_t buffer_readu16(Buffer* buf, u_int16_t* n);

error_t buffer_readi32(Buffer* buf, int32_t* n);
error_t buffer_readu32(Buffer* buf, u_int32_t* n);

error_t buffer_readchunk(Buffer* buf, size_t size, size_t len, void* dst);

error_t buffer_writei8(Buffer* buf, int8_t n);
error_t buffer_writeu8(Buffer* buf, u_int8_t n);

error_t buffer_writei16(Buffer* buf, int16_t n);
error_t buffer_writeu16(Buffer* buf, u_int16_t n);

error_t buffer_writei32(Buffer* buf, int32_t n);
error_t buffer_writeu32(Buffer* buf, u_int32_t n);

error_t buffer_writechunk(Buffer* buf, size_t size, size_t len, void* src);

int buffer_eof(Buffer* buf);

error_t buffer_status(void);

#endif
