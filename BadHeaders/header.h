// fileguard makes sure that the header file is included only once in the source code.
// you can use instead #pragma once at the top of the header file. 
#ifndef HEADER_H_INCLUDED //fileguard
    #define HEADER_H_INCLUDED
    #include <stdio.h>
    void test(void) {
        printf("Hello World\n");
    }
#endif