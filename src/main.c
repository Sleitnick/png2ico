#include <stdio.h>
#include <string.h>
#include "png.h"
#include "ico.h"
#include "err.h"

#ifndef PNG2ICO_VERSION
#define PNG2ICO_VERSION ""
#endif

static void print_help(void)
{
	printf("PNG to ICO\n\nUsage: png2ico output.ico input1.png [input2.png]...\n\n");
}

static void print_version(void)
{
	printf("png2ico %s\n", PNG2ICO_VERSION);
}

static int ends_with(const char* str, const char* ending)
{
	size_t str_len = strlen(str);
	size_t ending_len = strlen(ending);
	if (str_len < ending_len)
		return 0;
	
	return memcmp(str + (str_len - ending_len), ending, ending_len) == 0;
}

int main(int argc, char** argv)
{
	if (argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0))
	{
		print_help();
		return 0;
	}

	if (argc == 2 && (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-V") == 0))
	{
		print_version();
		return 0;
	}

	// Verify output exists
	if (argc <= 1)
	{
		printf("no output file argument found\n\n");
		print_help();
		return 1;
	}

	// Verify output ends with .ico:
	if (!ends_with(argv[1], ".ico"))
	{
		printf("output file extension must be \".ico\"\n\n");
		print_help();
		return 1;
	}

	// Verify there are any input files:
	if (argc <= 2)
	{
		printf("no input file arguments found\n\n");
		print_help();
		return 1;
	}

	// Verify input files end with .png:
	for (int i = 2; i < argc; i++)
	{
		const char* input = argv[i];
		if (!ends_with(input, ".png"))
		{
			printf("input file must end with \".png\": %s\n\n", input);
			print_help();
			return 1;
		}
	}

	int ico_res = ico_build(argv[1], argv + 2, argc - 2);

	if (ico_res == OK)
	{
		printf("Generated %s\n", argv[1]);
		return 0;
	}

	printf("Error: %s\n", err_to_string(ico_res));
	return ico_res;
}
