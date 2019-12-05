#include "bakeutils.h"

int main(int argc, char** argv)
{
    int status;
    exec_and_wait_for("bash", "-c curl", &status);
    printf("%i\n", status);
    return EXIT_SUCCESS;
}