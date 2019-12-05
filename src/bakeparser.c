#include "bakeparser.h"

#define BAKEFILE_LINE_ENDING '\n'

#define BAKE_COMMENT_CHAR '#'
#define BAKE_ACTION_CHAR '\t'
#define BAKE_VARIABLE_CHAR '='
#define BAKE_TARGET_CHAR ':'

#define BAKE_VAR_PATTERN "$("

void replace_variables(char* line, LIST_OF_BAKE_VARIABLES* variables)
{

}

void process_variable_definition(char* line, char* equals, LIST_OF_BAKE_VARIABLES* variables)
{
    size_t index = (size_t)(equals - line);
    *equals = '\0';
    char* name = line;
    char* value = line + index + 1;
    name = clean_string(name, " \t\r\n");
    value = remove_trailing_and_prevailing_characters(value, " \t\r\n");
    BAKE_VARIABLE variable;
    variable.name = strdup(name);
    variable.value = strdup(value);
    add_variable(variables, variable);
}

void process_action_definition(char* line, BAKE_TARGET* currentTarget)
{

}

int parse_bakefile(const char* path, LIST_OF_BAKE_TARGETS* outTargets)
{
    LIST_OF_BAKE_VARIABLES variables;
    create_list_of_bake_variables(&variables);
    BAKE_TARGET* currentTarget = NULL;

    size_t size;
    char* text = read_text_file(path, &size);
    if (text != NULL)
    {
        size_t lineCount;
        char** lines = strsplit(text, BAKEFILE_LINE_ENDING, 0, &lineCount);
        if (lines != NULL)
        {
            for (int i = 0; i < lineCount; i++)
            {
                char* line = lines[i];
                char firstChar = line[0];
                if (firstChar == BAKE_COMMENT_CHAR)
                {
                    // Comment
                    continue;
                }
                replace_variables(line, &variables);
                if (firstChar == BAKE_ACTION_CHAR)
                {
                    // Action
                }
                else
                {
                    // Variable or Target definition
                    char* colon = strchr(line, BAKE_TARGET_CHAR);
                    char* equal = strchr(line, BAKE_VARIABLE_CHAR);
                    if (colon != NULL && equal != NULL)
                    {
                        if (colon < equal)
                        {
                            
                        }
                        else
                        {
                            process_variable_definition(line, equal, &variables);
                        }
                        
                    }
                    else if (colon != NULL)
                    {
                        
                    }
                    else if (equal != NULL)
                    {
                        process_variable_definition(line, equal, &variables);
                    }
                }
            }
            freesplit(lines);
        }
        free(text);
        return BAKE_SUCCESS;
    }
    return BAKE_FAILURE;
}