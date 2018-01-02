#include<stdio.h>
#include <stdlib.h>
#include "crypto.h"
#include<string.h>

int keytest(KEY key){
    int keylength = strlen(key.chars);
    if(keylength < 1) {
        return KEY_TOO_SHORT;
    }
	
    for(int i = 0; i < keylength; i++) {
        char key_char = key.chars[i];
        if(key_char < '@' || key_char > '_') {
            return KEY_ILLEGAL_CHAR;
        }
    }
	return 0;
}

int crypt(KEY key, const char *input, char* output, char lowlimit, char upperlimit, int errorName) {
    int error = keytest(key);
    if(error != 0) {
        return error;
    }

    int keylength = strlen(key.chars);
    int len = strlen(input);
    int i = 0;
    for(i = 0; len; i++) {
        //validate current input char
        char input_char = input[i];
        if(input_char < lowlimit || input_char > upperlimit) {
            return errorName;
        }
	}
	
	int i = 0;
	int j = 0;
	
	
	for (i, j; i < len; i++) {
		output[i] = (((input[i] - 'A' + 1) ^ (key.chars[j] - 'A' + 1)) + 'A' - 1);
		j = (j + 1) % keylength;
	}
	return 0;
}
	  

int encrypt(KEY key, const char* input, char* output) {
   return crypt(key,input,output,'A','Z', MESSAGE_ILLEGAL_CHAR);
}

int decrypt(KEY key, const char* input, char* output) {
	return crypt(key,input,output,'@','_', CRYPTER_ILLEGAL_CHAR);
}

