#include<stdio.h>
#include <stdlib.h>
#include "crypto.h"
#include<string.h>

int checkIllegalChars(const char* input, const char* allowedchars) {

	for (int i = 0; i < strlen(input); i++) {
		int found = 0;
		for (int j = 0; j < strlen(allowedchars); j++) {
			if (input[i] == allowedchars[j]) {
				found = 1;//input on pos i is allowed
				break;
			}
		}
		if (found == 0)//input on pos i is not found in allowed chars
			return 1;
	}

	return 0;
}

int crypt(KEY key, const char *input, char* output) {

	int keylength = strlen(key.chars);
	int len = strlen(input);
	int i = 0;
	int j = 0;
	for (i, j; i < len; i++) {
		output[i] = (((input[i] - 'A' + 1) ^ (key.chars[j] - 'A' + 1)) + 'A' - 1);
		j = (j + 1) % keylength;
	}
	return 0;
}


int encrypt(KEY key, const char* input, char* output) {
	if (strlen(key.chars) == 0)
		return E_KEY_TOO_SHORT;

	if (checkIllegalChars(key.chars, KEY_CHARACTERS))
		return E_KEY_ILLEGAL_CHAR;

	if (checkIllegalChars(input, MESSAGE_CHARACTERS))
		return E_MESSAGE_ILLEGAL_CHAR;

	crypt(key, input, output);

	return 0;

}

int decrypt(KEY key, const char* input, char* output) {
	if (strlen(key.chars) == 0)
		return E_KEY_TOO_SHORT;

	if (checkIllegalChars(key.chars, KEY_CHARACTERS))
		return E_KEY_ILLEGAL_CHAR;

	if (checkIllegalChars(input, MESSAGE_CHARACTERS))
		return E_MESSAGE_ILLEGAL_CHAR;

	crypt(key, input, output);

	return 0;
}

