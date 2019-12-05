#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX(v0, v1) (((v0) > (v1)) ? (v0) : (v1))
#define MIN(v0, v1) (((v0) < (v1)) ? (v0) : (v1))

typedef struct {
    char* name;
    char* value;
} BAKE_VARIABLE;

void free_bake_variable(BAKE_VARIABLE* variable);

typedef struct {
    BAKE_VARIABLE* values;
    int size;
    int capacity;
} LIST_OF_BAKE_VARIABLES;

void create_list_of_bake_variables(LIST_OF_BAKE_VARIABLES* ptr);
void add_variable(LIST_OF_BAKE_VARIABLES* list, BAKE_VARIABLE variable);
void free_list_of_bake_variables(LIST_OF_BAKE_VARIABLES* list);
// variable_group can be NULL if only get values from environment
char* get_variable_value(LIST_OF_BAKE_VARIABLES* variables, const char* varname);

typedef struct {
    char* path;
} BAKE_OBJECT;

void free_bake_object(BAKE_OBJECT* object);

bool is_url_object(BAKE_OBJECT* object);
bool object_exists(BAKE_OBJECT* object);
time_t get_mod_time(BAKE_OBJECT* object);

typedef struct {
    BAKE_OBJECT* values;
    int size;
    int capacity;
} LIST_OF_BAKE_OBJECTS;

void create_list_of_bake_objects(LIST_OF_BAKE_OBJECTS* ptr);
void add_object(LIST_OF_BAKE_OBJECTS* list, BAKE_OBJECT object);
void free_list_of_bake_objects(LIST_OF_BAKE_OBJECTS* list);

typedef struct {
    char* command;
} BAKE_ACTION;

void free_bake_action(BAKE_ACTION* action);

typedef struct {
    BAKE_ACTION* values;
    int size;
    int capacity;
} LIST_OF_BAKE_ACTIONS;

void create_list_of_bake_actions(LIST_OF_BAKE_ACTIONS* ptr);
void add_action(LIST_OF_BAKE_ACTIONS* list, BAKE_ACTION action);
void free_list_of_bake_actions(LIST_OF_BAKE_ACTIONS* actions);

typedef struct {
    struct _BAKE_TARGET* values;
    int size;
    int capacity;
} LIST_OF_BAKE_TARGETS;

typedef struct _BAKE_TARGET {
    BAKE_OBJECT target;
    LIST_OF_BAKE_TARGETS dependencies;
    LIST_OF_BAKE_ACTIONS actions;
} BAKE_TARGET;

void create_list_of_bake_targets(LIST_OF_BAKE_TARGETS* ptr);
void add_target(LIST_OF_BAKE_TARGETS* list, BAKE_TARGET target);
void free_list_of_bake_targets(LIST_OF_BAKE_TARGETS* list);

void create_target(BAKE_TARGET* ptr);
void free_bake_target(BAKE_TARGET* target);