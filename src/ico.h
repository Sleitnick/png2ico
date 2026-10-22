#ifndef _ICO_H_
#define _ICO_H_

#include "err.h"

#include <stdlib.h>

error_t ico_build(const char* output_filepath, char** input_filepaths, size_t num_inputs);

#endif
