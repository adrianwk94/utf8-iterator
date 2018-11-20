/*
Minimalist UTF8 Iterator.

Original code by Adrian Guerrero Vera (adri.coin2010@gmail.com)
MIT License
Copyright (c) 2016 Adrian Guerrero Vera

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef UTF8_H
#define UTF8_H

#include <stdint.h>
#include <string.h>

typedef uint32_t Unicode;

typedef struct UTF8_Iterator {

	const char* ptr;
	Unicode	codepoint;

	uint8_t size; 		//character size in bytes
	size_t position; 	//current character position
	size_t next; 		//next character position
	size_t count; 		//number of counter characters currently
	size_t length; 		//strlen()

} UTF8_Iterator;

void 	UTF8_Init(UTF8_Iterator* iter, const char* ptr); //All values to 0 and set ptr.
int 	UTF8_Next(UTF8_Iterator* iter); //returns 1 if there is a character in the next position. If there is not, return 0.

size_t	UTF8_StringLength(const char* string); //calculates the number of multi-byte characters in a string. It is not the same as strlen()
Unicode	UTF8_to_Unicode(const char* character); //UTF8 to Unicode.
const char* Unicode_to_UTF8(Unicode codepoint); //Unicode to UTF8

//Internal use / Advanced use.
uint8_t	UTF8_CharacterSize(const char* character); //calculate the number of bytes a UTF8 character occupies in a string.
uint8_t Unicode_CharacterSize(Unicode codepoint); //calculates the number of bytes occupied by a Unicode character in UTF8.

Unicode UTF8_Converter(const char* character, uint8_t N);
const char* Unicode_Converter(Unicode codepoint, uint8_t N);

#endif
