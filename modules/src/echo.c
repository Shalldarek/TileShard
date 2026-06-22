#include <stdio.h>
#include "echo.h"

void echo(const char *message) {
    printf("%s\n", message);
    fflush(stdout);
}