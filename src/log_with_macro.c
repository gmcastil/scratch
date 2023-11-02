#include <stdio.h>

#define LOG(filename, ...) do { \
	FILE *log_file = fopen(filename, "a+"); \
	if (log_file) { \
		fprintf(log_file, "File: %s, Line: %d, Msg: ", __FILE__, __LINE__); \
		fprintf(log_file, __VA_ARGS__); \
		fprintf(log_file, "\n"); \
		fclose(log_file); \
	} else { \
		fprintf(stderr, "Could not open or create log file\n"); \
	} \
} while (0)

int main(int args, char *argv[])
{
	LOG("example.log", "string to log");
	return 0;
}

