#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BAKE_SUCCESS 0
#define BAKE_FAILURE 1

char** strsplit(const char* str, char delimiter, char quote, size_t* outLength);
void freesplit(char** splitresult);

char* read_text_file(const char* path, size_t* outSize);
char* clean_string(char* str, const char* characters);
char* remove_trailing_and_prevailing_characters(char* str, const char* characters);

char** create_argument_list(const char* progname, const char* args);
int exec_and_wait_for(const char* progname, const char* args, int* status);