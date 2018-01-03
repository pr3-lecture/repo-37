#include <stdio.h>
#include <string.h>
#include <stdlib.h> // malloc (warning)
#include "crypto.h"

int main(int argc, char* argv[]) {
  if (argc == 1) { // no param
    printf("Usage: KEY [file name]\n");
    return 0;
  }
  KEY k = {1, argv[1]}; // type 1 => XOR

  int bEncrypt = (strstr(argv[0], "encrypt") != 0);
  int error = 0;

  char input[255];
  char* output;
  if (argc == 2) {
    fgets(input, 254, stdin);
    input[strlen(input) - 1] = '\0'; // remove \n

    output = (char*) malloc(sizeof(char) * (strlen(input) + 1));
    error = (bEncrypt) ? encrypt(k, input, output) : decrypt(k, input, output);
    printf("%s\n", output);
    free(output);
  }

  if (argc == 3) {
    FILE* inputFile = fopen(argv[2], "r");

    if (inputFile == NULL) {
      fprintf(stderr, "Error: File '%s' not found\n", argv[2]);
      return 10;
    }

    while (fgets(input, 254, inputFile) && error == 0) {
      input[strlen(input) - 1] = '\0'; // remove \n
      output = (char*) malloc(sizeof(char) * (strlen(input) + 1));
      
      error = (bEncrypt) ? encrypt(k, input, output) : decrypt(k, input, output);
      printf("%s\n", output);
      free(output);
    }
    fclose(inputFile);
  }


  if (error == E_KEY_TOO_SHORT)
    fprintf(stderr, "Error: Length of key not sufficient\n");

  if (error == E_KEY_ILLEGAL_CHAR)
    fprintf(stderr, "Error: Key contains illegal characters\n");

  if (error == E_MESSAGE_ILLEGAL_CHAR)
    fprintf(stderr, "Error: Message contains illegal characters\n");

  if (error == E_CYPHER_ILLEGAL_CHAR)
    fprintf(stderr, "Error: Cypher text contains illegal characters\n");

  //free(output);
  return error;
}
