#include <stdio.h>
#include <stdlib.h>

#include "FireDragon.h"

int NumCharacters(const char *str);

int main() {
	
	const int MAX_NUM_CHAR = 256;

	const int MAX_STR_SIZE = sizeof(char) * MAX_NUM_CHAR;

	char *str = (char*)malloc(MAX_STR_SIZE);
	str = "whasssssuuuuuuuppppppp";
	int numChar = NumCharacters(str);

	printf("There are %d in this str", numChar);

	FireDragon fireDragon;
	fireDragon.numScales = 2;
	return 0;
}

int NumCharacters(const char *str) {
	int numChar = 0;
	//TODO: Get it Working...
	if(str == NULL) {
		return numChar;
	}
	//For loop Example 
	/*
	for (int i = 0; i < 256; ++i) {
		if (str[i] == '\0') {
			break;
		}
		++numChar; 
	}*/
	

	const char *nextChar = str;
	//While loop example...
	while (*nextChar != '\0') {
		++numChar;
		++nextChar;
	}

	return numChar;

}