#ifndef _ERR_H_
#define _ERR_H_

#define OK 0
#define ERR_ALLOC 1
#define ERR_OPEN_FILE 2
#define ERR_EOF 3
#define ERR_READ 4
#define ERR_WRITE 5
#define ERR_PNG_TOO_BIG 6
#define ERR_PNG_INVALID 7
#define ERR_NULL 8

typedef int error_t;

const char* err_to_string(int error);

#endif
