#include "err.h"

const char* err_to_string(error_t error)
{
	switch (error) {
		case OK:
			return "OK";
		case ERR_ALLOC:
			return "Failed to allocate memory";
		case ERR_OPEN_FILE:
			return "Failed to open file";
		case ERR_EOF:
			return "End of file";
		case ERR_READ:
			return "Failed to read";
		case ERR_WRITE:
			return "Failed to write";
		case ERR_PNG_TOO_BIG:
			return "PNG file exceeds maximum size for ICO (256x256 pixels)";
		case ERR_PNG_INVALID:
			return "Invalid PNG file";
		case ERR_NULL:
			return "Unexpected null pointer";
		default:
			return "Unknown error";
	}
}
