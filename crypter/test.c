#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "crypto.h"

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)
									
static int tests_run = 0;

	static char* test_invalid_key_type_error() {
	char *key = "TPERULES";
    KEY temporaryKey;
	temporaryKey.type = 0;
    temporaryKey.chars = key;

    int result = encrypt(temporaryKey, input, output);
    mu_assert("encrypt fail -> invalid key type", result == E_KEY_ILLEGAL_TYPE);

    result = decrypt(temporaryKey, input, output);
    mu_assert("decrypt fail -> invalid key type", result == E_KEY_ILLEGAL_TYPE);

    return 0;
}								
static char* test_key_too_short() {
	char *key = "";
    KEY temporaryKey;
	temporaryKey.type = 1;
    temporaryKey.chars = key;

    int result = encrypt(temporaryKey, input, output);
    mu_assert("encrypt fail -> key is too short", result == KEY_TOO_SHORT);

    result = decrypt(temporaryKey, input, output);
    mu_assert("decrypt fail -> key is too short", result == KEY_TOO_SHORT);

    return 0;
}

static char* test_key_contains_illegal_char() {
	char *key = "`";
    KEY temporaryKey;
	temporaryKey.type = 1;
    temporaryKey.chars = key;

    int result = encrypt(temporaryKey, input, output);
    mu_assert("encrypt fail -> key contains illiegal chars", result == KEY_ILLEGAL_CHAR);

    result = decrypt(temporaryKey, input, output);
    mu_assert("decrypt fail -> key contains illiegal chars", result == KEY_ILLEGAL_CHAR);

    return 0;
} 

static char* test_encrypt_input_contians_illegal_char() {
	char *key = "TPERULES";
    KEY temporaryKey;
	temporaryKey.type = 1;
    temporaryKey.chars = key;
    char *input = "ABCD[";
    int result = encrypt(temporaryKey, input, output);
    mu_assert("encrypt fail -> input contains illiegal chars", result == MESSAGE_ILLEGAL_CHAR);

    return 0;
}

static char* test_decrypt_input_contians_illegal_char() {
	char *key = "TPERULES";
    KEY temporaryKey;
	temporaryKey.type = 1;
    temporaryKey.chars = key;
    char *input = "UZGD+";
    int result = decrypt(temporaryKey, input, output);
    mu_assert("decrypt fail -> input contains an illiegal char", result == CYPHER_ILLEGAL_CHAR);

    return 0;
}

static char* test_encrypt() {
	char *key = "TPERULES";
    KEY temporaryKey;
	temporaryKey.type = 1;
    temporaryKey.chars = key;

	char *input = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *output = (char*)malloc(sizeof(char) * (strlen(input) + 1));
    
    encrypt(temporaryKey, input, output);
    mu_assert("output error from encrypt", strcmp(output, "URFVPJB[]ZN^XBJCEBVF@ZRKMJ") == 0);
	
    free(output);
    return 0;
}

static char* test_decrypt() {
	char *key = "TPERULES";
    KEY temporaryKey;
	temporaryKey.type = 1;
    temporaryKey.chars = key;

	char *input = "URFVPJB[]ZN^XBJCEBVF@ZRKMJ";
    char *output = (char*)malloc(sizeof(char) * (strlen(input) + 1));
    
    encrypt(temporaryKey, input, output);
    mu_assert("output error from decrypt", strcmp(output, "ABCDEFGHIJKLMNOPQRSTUVWXYZ") == 0);
	
    free(output);
    return 0;
}


static char* allTests() {
    mu_run_test(test_key_too_short);
	mu_run_test(test_key_contains_illegal_char);
	mu_run_test(test_encrypt_input_contians_illegal_char);
    mu_run_test(test_decrypt_input_contians_illegal_char);
    mu_run_test(test_encrypt);
	mu_run_test(test_decrypt);
    return 0;
}

int main() {
    char *result = allTests();

    if (result != 0) printf("%s\n", result);
    else             printf("ALL TESTS PASSED\n");

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}