#include "bakeutils.h"
#include <sys/wait.h>
#include <sys/stat.h>

char** strsplit(const char* str, char delimiter, char quote, size_t* outCount)
{
    // Calculate and allocate enough memory to copy the string
    size_t strlength = strlen(str);
    char* buffer = malloc(sizeof(char) * (strlength + 1));
    if (buffer == NULL)
    {
        return NULL;
    }
    strcpy(buffer, str);
    size_t count = 0;

    // Count the number of potential elements in the resulting vector (count number of delimiters that aren't consecutive)
    bool tokenizing = true;
    char prev = delimiter;
    for (int i = 0; i < strlength; i++)
    {
        if (buffer[i] == quote)
        {
            buffer[i] = '\0';
            tokenizing = !tokenizing;
        }
        if (buffer[i] == delimiter && tokenizing)
        {
            // Set all delimiter characters to the null byte
            buffer[i] = '\0';
            if (prev != delimiter)
            {
                count++;
            }
        }
        prev = str[i];
    }
    // Always need to store on more string that the number of delimiters unless the last character is a delimiter or str is the empty string
    if (strlength > 0 && str[strlength - 1] != delimiter)
    {
        count++;
    }

    // str only contains delimiter characters, return vector of empty string
    if (count == 0)
    {
        *outCount = 0;
        char** vector = (char**)malloc(sizeof(char*));
        vector[0] = (char*)malloc(1 * sizeof(char));
        vector[0][0] = '\0';
        return vector;
    }

    // Allocate memory to store vector of strings
    char** vector = (char**)malloc(sizeof(char*) * count);
    if (vector == NULL)
    {
        return NULL;
    }

    // Iterate through elements of string and set all delimiter characters to '\0'
    // If the string begins with several delimiter characters, erase them by keeping track of the first non delimiter character (nonNull)
    prev = '\0';
    int index = 0;
    int nonNull = -1;
    for (int i = 0; i < strlength; i++)
    {
        // If the current character is not '\0' but the previous character was,
        // This must be the start of a new string, add its pointer to the vector
        if (buffer[i] != '\0' && prev == '\0')
        {
            // Find the first non delimiter character
            if (nonNull == -1)
            {
                nonNull = i;
            }
            // - nonNull to account for any shifting that will occur later due to string beginning with delimiter characters
            vector[index++] = buffer + i - nonNull;
        }
        prev = buffer[i];
    }

    // The string began with delimiter characters, shift everything left to erase them
    if (nonNull != -1 && nonNull != 0) 
    {
        memmove(buffer, buffer + nonNull, strlength - nonNull);
        buffer[strlength - nonNull] = '\0';
    }

    if (outCount != NULL)
    {
        *outCount = count;
    }
    return vector;
}

void freesplit(char** strsplitresult)
{
    // Ptr to the allocated buffer will always be the first element
    free(strsplitresult[0]);
    free(strsplitresult);
}

char* read_text_file(const char* path, size_t* outSize)
{
    struct stat sbuffer;
    if (stat(path, &sbuffer) == 0)
    {
        if (outSize != NULL)
        {
            *outSize = sbuffer.st_size;
        }
        char* buffer = (char*)malloc(sbuffer.st_size + 1);
        if (buffer == NULL)
        {
            free(buffer);
        }
        FILE* file = fopen(path, "r");
        if (file != NULL)
        {
            fread(buffer, sbuffer.st_size, 1, file);
            fclose(file);
            buffer[sbuffer.st_size] = '\0';
            return buffer;
        }
    }
    return NULL;
}

char* clean_string(char* str, const char* characters)
{
    return str;
}

char* remove_trailing_and_prevailing_characters(char* str, const char* characters)
{
    return str;
}

char** create_argument_list(const char* progname, const char* args)
{
    size_t count;
    char** result = strsplit(args, ' ', '"', &count);
    result = (char**)realloc(result, count + 2);
    for (int i = count; i >= 1; i--)
    {
        result[i] = result[i - 1];
    }
    result[0] = strdup(progname);
    result[count + 1] = NULL;
    return result;
}

int exec_and_wait_for(const char* progname, const char* args, int* status)
{
    switch (fork())
    {
    case -1:
        return BAKE_FAILURE;
    case 0:
    {
        // Child Processes
        char** argsList = create_argument_list(progname, args);
        execvp(progname, argsList);
        freesplit(argsList);
        return BAKE_FAILURE;
    }
    default:
        wait(status);
    }
    return BAKE_SUCCESS;
}