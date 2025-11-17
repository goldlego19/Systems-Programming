#include <stdio.h>

//gcc -DFULL .\fulldemo.c -o fulldemo.exe for full version


int main(void) {
    printf("Full Demo Program\n");

    #ifdef FULL
        printf("This is the full version\n");
    #else
        printf("This is the demo version\n");
    #endif
    return 0;
}