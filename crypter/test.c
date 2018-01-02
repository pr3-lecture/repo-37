#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "crypto.h"

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)

static int tests_run = 0;


static char* test_key_too_short() {
	KEY temporaryKey = { 1, "" };
	const char* input = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char* output = (char*)malloc(sizeof(char) * (strlen(input) + 1));

	int result = encrypt(temporaryKey, input, output);
	mu_assert("encrypt fail -> key too short", result == E_KEY_TOO_SHORT);

	result = decrypt(temporaryKey, input, output);
	mu_assert("decrypt fail -> key too short", result == E_KEY_TOO_SHORT);

	return 0;
}

static char* test_key_contains_illegal_char() {
	KEY temporaryKey = { 1, "+" };
	const char* input = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char* output = (char*)malloc(sizeof(char) * (strlen(input) + 1));

	int result = encrypt(temporaryKey, input, output);
	mu_assert("encrypt fail -> key has illegal chars", result == E_KEY_ILLEGAL_CHAR);

	result = decrypt(temporaryKey, input, output);
	mu_assert("decrypt fail -> key has illegal chars", result == E_KEY_ILLEGAL_CHAR);

	return 0;
}

static char* test_encrypt_input_contians_illegal_char() {
	KEY temporaryKey = { 1, "TPERULES" };
	const char* input = "ABCDEFGHIJKLMNOPQRSTUVWXYZ+";
	char* output = (char*)malloc(sizeof(char) * (strlen(input) + 1));

	int result = encrypt(temporaryKey, input, output);
	mu_assert("encrypt fail -> input has illegal chars", result == E_MESSAGE_ILLEGAL_CHAR);

	return 0;
}

static char* test_decrypt_input_contians_illegal_char() {
	KEY temporaryKey = { 1, "TPERULES" };
	const char* input = "URFVPJB[]ZN^XBJCEBVF@ZRKMJ+";
	char* output = (char*)malloc(sizeof(char) * (strlen(input) + 1));

	int result = encrypt(temporaryKey, input, output);
	mu_assert("decrypt fail -> input has illegal chars", result == E_MESSAGE_ILLEGAL_CHAR);

	return 0;
}

static char* test_encrypt() {
	KEY temporaryKey = { 1, "TPERULES" };
	char *input = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *output = (char*)malloc(sizeof(char) * (strlen(input) + 1));

	encrypt(temporaryKey, input, output);
	mu_assert("output error from encrypt", strcmp(output, "URFVPJB[]ZN^XBJCEBVF@ZRKMJ") == 0);

	free(output);
	return 0;
}

static char* test_decrypt() {
	KEY temporaryKey = { 1, "TPERULES" };
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