#include "crypto.h"
//#include <stdio.h>
#include <string.h>
#include <stdlib.h> // malloc (warning)

void enlarge(const char* input, char* output, int newsize) {
  int i, j;
  for(i = 0, j = 0; i < newsize; i++, j++) {
    if (j == strlen(input)) {
      j = 0;
    }
    output[i] = input[j];
  }
}

int hasIllegalChars(const char* input, const char* allowed) {
  int i;
  for (i = 0; i < strlen(input); i++) {

    int found = 0;
    int j;
    for (j = 0; j < strlen(allowed); j++) {
      if (input[i] == allowed[j]) {
        found = 1;
        break;
      }
    }

    if (found == 0) 
      return 1;
  }

  return 0;
}

void xor(KEY key, const char* input, char* output) {
  char* longkey = (char*) malloc(sizeof(char) * (strlen(input) + 1));
  enlarge(key.chars, longkey, strlen(input));

  int i;
  for (i = 0; i < strlen(input); i++) {
    output[i]  = input[i]   - 'A' + 1; //
    longkey[i] = longkey[i] - 'A' + 1; // map to num for xor
    
    output[i] = output[i] ^ longkey[i];
    output[i] = output[i] + 'A' - 1;
  }
  output[i] = '\0'; // end for "new" string
}

int encrypt(KEY key, const char* input, char* output) {
  if (strlen(key.chars) == 0)
    return E_KEY_TOO_SHORT;

  if (hasIllegalChars(key.chars, KEY_CHARACTERS))
    return E_KEY_ILLEGAL_CHAR;

  if (hasIllegalChars(input, MESSAGE_CHARACTERS))
    return E_MESSAGE_ILLEGAL_CHAR;


  xor(key, input, output);

  return 0;
}

int decrypt(KEY key, const char* cypherText, char* output) {
  if (strlen(key.chars) == 0)
    return E_KEY_TOO_SHORT;

  if (hasIllegalChars(key.chars, KEY_CHARACTERS))
    return E_KEY_ILLEGAL_CHAR;

  if (hasIllegalChars(cypherText, CYPHER_CHARACTERS))
    return E_CYPHER_ILLEGAL_CHAR;


  xor(key, cypherText, output);

  return 0;
}