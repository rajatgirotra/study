#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* globalsrc = "Hello";

int main(int argc, char *argv[]) {
    printf("location of code : %p\n", (void*)main);
    printf("location of heap : %p\n", (void *) malloc(1));
    int x = 3;
    printf("location of stack : %p\n", (void *) &x);

    const char* src = "Hello";
    printf("%p\n", (void*)(&src));
    printf("Global Src %p\n", (void*)(&globalsrc));
    return x;
}
