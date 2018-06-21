# Minimalist UTF8 Iterator

This library is an iterator for UTF8 chains, in addition to converting characters from UTF8 to Unicode and vice versa.

### How does this library work inside?

I have created a document in Spanish that explains how this library works inside. You can read it and download it in PDF from this link. [Document in Google Doc](https://docs.google.com/document/d/1sqiEnZnchDRCWZffTAnKsU5Pyc28m3Lvg0UT2o4aClU/edit?usp=sharing)

## How to use the library?

Using UTF8 Iterator is very easy, it consists of a structure and two functions.

```c++
#include "UTF8.h"
#include <stdio.h>

int main() {
    
    const char* String = "Hello World, こんにちは世界, привет мир.";
    
    UTF8_Iterator ITER;
    UTF8_Init(&ITER, String);
    
    while (UTF8_Next(&ITER)) {
        
        printf("Character: %s \t Codepoint: %u\n", Unicode_to_UTF8(ITER.codepoint), ITER.codepoint);
        
    }
    
}
```

`UTF8_Iterator` is the structure, and contains important and useful data.

* `ptr` is the original pointer to the character string, it is assigned by `UTF8_Init()`.
* `codepoint` is the current character in Unicode.
* `position` is the current position in the string.
* `next` is the next position in the string.
* `count` is the number of characters currently.
* `length` is the length of the string with `strlen()`

`UTF8_Init(pointerIterator, string)` is used to start or restart the iterator. The first argument is a pointer to the Iterator, and the second argument is the character string.

`UTF8_Next(pointerIterator)` checks the string, the size of the next character and converts the character to Unicode. `Return: 1 -> Continue, 0 -> End or Error.`

### Other functions

These functions do not require the use of the Iterator:

* `UTF8_CharacterWidth(character)` returns the size of the character.
* `UTF8_StringLength(string)` returns the number of characters in the string. It is different from `strlen()`
* `UTF8_to_Unicode(character)` returns the codepoint in Unicode.
* `Unicode_to_UTF8(Unicode)` returns the pointer to a string with the character in UTF8.

## Compile Example

To compile in GCC, use the following commands within the library folder:

```
mkdir Build
gcc -ISource/ -Wall Main/main.c Source/UTF8.c -o Build/UTF8

In Windows: Build\UTF8.exe
In Linux: ./Build/UTF8
```

Tested with GCC, MinGW Visual Studio 2017.

## Issue Report

You can report a problem in English or Spanish.

## License

**UTF8 Iterator** is distributed with an MIT License. You can see LICENSE.txt for more info. 

## Screenshots

###### UFT8 Iterator in Ubuntu: 
![Terminal in Ubuntu](https://image.ibb.co/fqnMV8/Terminal_en_Ubuntu.png)

###### UTF8 Iterator in Windows, UTF8 not support in CMD :( 
![CMD](https://image.ibb.co/jBNoA8/Terminal_en_Windows.png)

###### UTF8 Iterator in Windows with Sublime Text: 
![Console Sublime Text](https://image.ibb.co/eHOvq8/Console_Sublime_Text.png)