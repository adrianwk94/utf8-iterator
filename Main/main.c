#include "utf-8.h"

#include <stdio.h>
#include <string.h>

int main() {

	const char* String = "Hello World, Γεια σου κόσμο, こんにちは世界, привет мир.";
	const char* Character;

	utf8_iter ITER;

	utf8_init(&ITER, String);

	printf("\nString = %s\n\n", ITER.ptr);

	while (utf8_next(&ITER)) {

		Character = utf8_getchar(&ITER);

		printf("Character =  %s\t Codepoint =  %u\t\t BYTES:  ", Character, ITER.codepoint);

		for (int i = 0; i < 8; i++) {
			if (Character[i] == 0) break;
			printf("%u  ", (unsigned char)Character[i]);
		}

		printf("\n");
	}

	printf("\n");
	printf("Character Count = %u\n", ITER.count);
	printf("Length in BYTES = %u\n", ITER.length);

	return 0;
}
