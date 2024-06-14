#include "ico.h"

#include "png.h"
#include "buffer.h"

static void free_png_infos(PngInfo** infos, size_t num)
{
	for (size_t i = 0; i < num; i++)
	{
		if (infos[i] != NULL)
		{
			if (infos[i]->data != NULL)
				png_free_info(infos[i]);
			free(infos[i]);
		}
	}
}

error_t ico_build(const char* output_filepath, char** input_filepaths, size_t num_inputs)
{
	PngInfo** infos = (PngInfo**)calloc(num_inputs, sizeof(PngInfo*));
	if (infos == NULL)
	{
		return ERR_ALLOC;
	}

	int alloc_succeed = 1;
	for (size_t i = 0; i < num_inputs; i++)
	{
		infos[i] = (PngInfo*)malloc(sizeof(PngInfo));
		if (infos[i] == NULL)
		{
			alloc_succeed = 0;
			break;
		}
		infos[i]->data = NULL;
	}
	if (!alloc_succeed)
	{
		free_png_infos(infos, num_inputs);
		return ERR_ALLOC;
	}

	// Read PNG info:
	for (size_t i = 0; i < num_inputs; i++)
	{
		const char* input = input_filepaths[i];
		PngInfo* info = infos[i];
		int png_err = png_get_info(input, info);
		if (png_err != OK)
		{
			free_png_infos(infos, num_inputs);
			return png_err;
		}

		// Ensure PNG size is within limits:
		if (info->ihdr.width > 256 || info->ihdr.height > 256)
		{
			free_png_infos(infos, num_inputs);
			return ERR_PNG_TOO_BIG;
		}

		// Max width/height is represented by 0
		if (info->ihdr.width == 256) info->ihdr.width = 0;
		if (info->ihdr.height == 256) info->ihdr.height = 0;
	}

	Buffer buf;
	if (buffer_open(output_filepath, &buf, BUFFER_MODE_WRITE) != OK)
	{
		buffer_close(&buf);
		return ERR_OPEN_FILE;
	}

	// Header
	buffer_writeu16(&buf, 0); // Reserved; always 0
	buffer_writeu16(&buf, 1); // ICO type (1 = ICO, 2 = CUR)
	buffer_writeu16(&buf, (uint16_t)num_inputs); // Number of files

	// Write icon entries:
	size_t offset = 6 + 16 * num_inputs;
	for (size_t i = 0; i < num_inputs; i++)
	{
		PngInfo* info = infos[i];
		buffer_writeu8(&buf, (uint8_t)info->ihdr.width);
		buffer_writeu8(&buf, (uint8_t)info->ihdr.height);
		buffer_writeu8(&buf, 0); // Colors in color palette (TODO)
		buffer_writeu8(&buf, 0); // Reserved; always 0
		buffer_writeu16(&buf, 0); // Color plane
		buffer_writeu16(&buf, info->ihdr.bit_depth); // Bits per pixel
		buffer_writeu32(&buf, (uint32_t)info->data_size); // Image data size
		buffer_writeu32(&buf, (uint32_t)offset); // Image data size
		offset += info->data_size;
	}

	// Write image data
	for (size_t i = 0; i < num_inputs; i++)
	{
		PngInfo* info = infos[i];
		buffer_writechunk(&buf, sizeof(unsigned char), info->data_size, info->data);
	}

	free_png_infos(infos, num_inputs);

	return OK;
}
