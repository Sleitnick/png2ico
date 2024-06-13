#ifndef _ICO_H_
#define _ICO_H_

#include <stdlib.h>
#include "err.h"

error_t ico_build(const char* output_filepath, char** input_filepaths, size_t num_inputs);

#endif
