#include "UTF8.h"

#include <stdio.h>

int main() {

	char Character[16];

	const char* String = "Hello World, こんにちは世界, привет мир.";

	UTF8_Iterator ITER;

	UTF8_Init(&ITER, String);

	printf("\nString = %s\n", String);

	#if __WIN32
	printf("Length = %u\n\n", ITER.length);
	#else
	printf("Length = %lu\n\n", ITER.length);
	#endif

	while (UTF8_Next(&ITER)) {

		strcpy(Character, Unicode_to_UTF8(ITER.codepoint));

		printf("Character =  %s\t Codepoint =  %u\t\t BYTES:  ", Character, ITER.codepoint);

		for (int i = 0; i < 8; i++) {
			if (Character[i] == 0) break;
			printf("%u  ", (unsigned char)Character[i]);
		}

		printf("\n");

	}
	
	#if __WIN32
	printf("\nCount Character = %u\n", ITER.count);
	#else
	printf("\nCount Character = %lu\n", ITER.count);
	#endif

	return 0;

}