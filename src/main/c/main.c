#include <string.h>
#include <stdio.h>

int main (int argc, char** argv) {
    char buf[40];
    strcpy(buf, argv[1]);

    printf("%s\n", buf);

    return 0;
}