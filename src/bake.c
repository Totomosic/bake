#include "bakeparser.h"

int process_bakefile(const char* bakefile, bool verbose)
{
    LIST_OF_BAKE_TARGETS targets;
    create_list_of_bake_targets(&targets);
    if (parse_bakefile(bakefile, &targets) == BAKE_SUCCESS)
    {
        printf("Successfully parsed %s\n", bakefile);
    }
    return BAKE_FAILURE;
}

int main(int argc, char** argv)
{
    const char* bakefile = "Bakefile";
    return process_bakefile(bakefile, true);
}