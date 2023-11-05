#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
	char *str = "          string to be trimmed";
	printf("%s\n", str);
	/*
	 * Don't miss the cast here, which ensures the character is in the range
	 * of [0, 255] (e.g., ASCII encoded)
	 */
	while (isspace( (unsigned char) *str)) {
		str++;
	}
	printf("%s\n", str);

	return 0;
}

