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

#include "UTF8.h"

#include <stdio.h>

//UTF8_Iterator
void 	UTF8_Init(UTF8_Iterator* iter, const char* ptr) {

    if (iter) {
    	iter -> ptr = ptr;
    	iter -> codepoint = 0;
    	iter -> position = 0;
    	iter -> next = 0;
    	iter -> count = 0;
    	iter -> length = strlen(ptr);
    }

}
int 	UTF8_Next(UTF8_Iterator* iter) {

    if (iter == NULL) return 0;
	if (iter -> ptr == NULL) return 0;

	const char* t_pointer;

	if (iter -> next < iter -> length) {

		iter -> position = iter -> next;

		t_pointer = iter -> ptr + iter -> next; //Set Current Pointer
		iter -> size = UTF8_CharacterSize(t_pointer);

		if (iter -> size == 0) return 0;

        iter -> next = iter -> next + iter -> size;
		iter -> codepoint = UTF8_Converter(t_pointer, iter -> size);

		if (iter -> codepoint == 0) return 0;

		iter -> count++;

		return 1;

	}
	else
	{
		return 0;
	}

}

//////
size_t  UTF8_StringLength(const char* string) {

    if (string == NULL) return 0;

    const char* t_pointer = string;
    size_t      t_length = 0;

    while (*t_pointer) {
        t_pointer = t_pointer + UTF8_CharacterSize(t_pointer);
        t_length++;
    }

    return t_length;

}

Unicode UTF8_to_Unicode(const char* character) {

    if (!character) return 0;

    uint8_t N = UTF8_CharacterSize(character);

    if (N == 0) return 0;
    
    return UTF8_Converter(character, N);

}

const char* Unicode_to_UTF8(Unicode codepoint) {

    uint8_t N = Unicode_CharacterSize(codepoint);

    if (N == 0) return 0;

    return Unicode_Converter(codepoint, N);

}

//////

uint8_t UTF8_CharacterSize(const char* character) {

    if (!character) return 0;

    if (character[0] == 0) return 0;

    if ((character[0] & 0x80) == 0) return 1;
    else if ((character[0] & 0xE0) == 0xC0) return 2;
    else if ((character[0] & 0xF0) == 0xE0) return 3;
    else if ((character[0] & 0xF8) == 0xF0) return 4;
    else if ((character[0] & 0xFC) == 0xF8) return 5;
    else if ((character[0] & 0xFE) == 0xFC) return 6;

    return 0;

}

static const uint8_t ToUnicode[] = {0, 0, 0x1F, 0xF, 0x7, 0x3, 0x1};

Unicode UTF8_Converter(const char* character, uint8_t N) {

    if (!character || N == 0) return 0;

    static Unicode codepoint = 0;

    if (N == 1) {
        return character[0];
    }

    codepoint = ToUnicode[N] & character[0];

    for (uint8_t i = 1; i < N; i++) {
        codepoint = codepoint << 6;
        codepoint = codepoint | (character[i] & 0x3F);
    }
    
    return codepoint;

}

//////

uint8_t Unicode_CharacterSize(Unicode codepoint) {

    if (codepoint == 0) return 0;

    if (codepoint < 0x80) return 1;
    else if (codepoint < 0x800) return 2;
    else if (codepoint < 0x10000) return 3;
    else if (codepoint < 0x200000) return 4;
    else if (codepoint < 0x4000000) return 5;
    else if (codepoint <= 0x7FFFFFFF) return 6;

    return 0;

}

static const uint8_t ToUTF8[] = {0, 0,  0xC0,  0xE0, 0xF0,  0xF8,  0xFC};

const char* Unicode_Converter(Unicode codepoint, uint8_t N) {

    if (codepoint == 0 || N == 0) return 0;

    static char str[10];
    
    str[N] = '\0';

    if (N == 1) {
        str[0] = codepoint;
        return str;
    }
    
    for (uint8_t i = N - 1; i > 0; i--) {
        str[i] = 0x80 | (codepoint & 0x3F);
        codepoint = codepoint >> 6;
    }

    str[0] = ToUTF8[N] | codepoint;
    
    return str;

}
