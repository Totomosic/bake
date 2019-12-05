#include "baketypes.h"

void free_bake_variable(BAKE_VARIABLE* variable)
{
    free(variable->name);
    free(variable->value);
}

void create_list_of_bake_variables(LIST_OF_BAKE_VARIABLES* ptr)
{
    ptr->capacity = 5;
    ptr->values = (BAKE_VARIABLE*)malloc(ptr->capacity * sizeof(BAKE_VARIABLE));
    ptr->size = 0;
}

void add_variable(LIST_OF_BAKE_VARIABLES* list, BAKE_VARIABLE variable)
{
    list->size++;
    if (list->size > list->capacity)
    {
        int newCapacity = MAX(list->size, list->capacity * 2);
        list->values = realloc(list->values, newCapacity * sizeof(BAKE_VARIABLE));
    }
    list->values[list->size - 1] = variable;
}

void free_list_of_bake_variables(LIST_OF_BAKE_VARIABLES* list)
{
    for (int i = 0; i < list->size; i++)
    {
        free_bake_variable(&list->values[i]);
    }
    free(list->values);
}
// variable_group can be NULL if only get values from environment
char* get_variable_value(LIST_OF_BAKE_VARIABLES* variables, const char* varname)
{
    for (int i = 0; i < variables->size; i++)
    {
        BAKE_VARIABLE* var = &variables->values[i];
        if (strcmp(var->name, varname) == 0)
        {
            return strdup(var->value);
        }
    }
    char* value = getenv(varname);
    if (value == NULL)
    {
        value = "";
    }
    return strdup(value);
}

void free_bake_object(BAKE_OBJECT* object)
{
    free(object->path);
}

bool is_url_object(BAKE_OBJECT* object)
{
    return false;
}

bool object_exists(BAKE_OBJECT* object)
{
    int result = access(object->path, F_OK);
    return result == 0;
}

time_t get_mod_time(BAKE_OBJECT* object)
{
    return time(NULL);
}

void create_list_of_bake_objects(LIST_OF_BAKE_OBJECTS* ptr)
{
    ptr->capacity = 5;
    ptr->values = (BAKE_OBJECT*)malloc(ptr->capacity * sizeof(BAKE_OBJECT));
    ptr->size = 0;
}

void add_object(LIST_OF_BAKE_OBJECTS* list, BAKE_OBJECT object)
{
    list->size++;
    if (list->size > list->capacity)
    {
        int newCapacity = MAX(list->size, list->capacity * 2);
        list->values = realloc(list->values, newCapacity * sizeof(BAKE_OBJECT));
    }
    list->values[list->size - 1] = object;
}

void free_list_of_bake_objects(LIST_OF_BAKE_OBJECTS* list)
{
    for (int i = 0; i < list->size; i++)
    {
        free_bake_object(&list->values[i]);
    }
    free(list->values);
}

void free_bake_action(BAKE_ACTION* action)
{
    free(action->command);
}

void create_list_of_bake_actions(LIST_OF_BAKE_ACTIONS* ptr)
{
    ptr->capacity = 5;
    ptr->values = (BAKE_ACTION*)malloc(ptr->capacity * sizeof(BAKE_ACTION));
    ptr->size = 0;
}

void add_action(LIST_OF_BAKE_ACTIONS* list, BAKE_ACTION action)
{
    list->size++;
    if (list->size > list->capacity)
    {
        int newCapacity = MAX(list->size, list->capacity * 2);
        list->values = realloc(list->values, newCapacity * sizeof(BAKE_ACTION));
    }
    list->values[list->size - 1] = action;
}

void free_list_of_bake_actions(LIST_OF_BAKE_ACTIONS* actions)
{
    for (int i = 0; i < actions->size; i++)
    {
        free_bake_action(&actions->values[i]);
    }
    free(actions->values);
}

void create_target(BAKE_TARGET* ptr)
{
    create_list_of_bake_targets(&ptr->dependencies);
    create_list_of_bake_actions(&ptr->actions);
}

void free_bake_target(BAKE_TARGET* target)
{
    free_list_of_bake_actions(&target->actions);
    free_list_of_bake_targets(&target->dependencies);
}

void create_list_of_bake_targets(LIST_OF_BAKE_TARGETS* ptr)
{
    ptr->capacity = 5;
    ptr->values = (BAKE_TARGET*)malloc(ptr->capacity * sizeof(BAKE_TARGET));
    ptr->size = 0;
}

void add_target(LIST_OF_BAKE_TARGETS* list, BAKE_TARGET target)
{
    list->size++;
    if (list->size > list->capacity)
    {
        int newCapacity = MAX(list->size, list->capacity * 2);
        list->values = realloc(list->values, newCapacity * sizeof(BAKE_TARGET));
    }
    list->values[list->size - 1] = target;
}

void free_list_of_bake_targets(LIST_OF_BAKE_TARGETS* list)
{
    for (int i = 0; i < list->size; i++)
    {
        free_bake_target(&list->values[i]);
    }
    free(list->values);
}