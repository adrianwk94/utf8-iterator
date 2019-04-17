#include "UTF8.h"

#include <stdio.h>
#include <string.h>

int main() {

	const char* String = "Hello World, こんにちは世界, привет мир.";
	const char* Character;

	UTF8_Iterator ITER;

	UTF8_Init(&ITER, String);

	printf("\nString = %s\n\n", ITER.ptr);	

	while (UTF8_Next(&ITER)) {

		Character = UTF8_GetCharacter(&ITER);

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
