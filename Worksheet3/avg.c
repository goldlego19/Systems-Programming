// Program: add.c
// Usage: add <num1> [<num2> ...]
// Sums any number of numeric arguments (supports integers and decimals).

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]){
    if(argc < 2){
        printf("Usage: %s <num1> [<num2> ...]\n", argv[0]);
        return 0;
    }

    double sum = 0.0;
    for(int i = 1; i < argc; ++i){
        const char *p = argv[i];
        while(*p){
            while(*p == ' ' || *p == ',' || *p == '\t') ++p;
            if(*p == '\0') break;

            errno = 0;
            char *endptr = NULL;
            double val = strtod(p, &endptr);

            if(endptr == p){
                // no conversion happened at this position -> invalid token
                fprintf(stderr, "Error: '%s' is not a valid number\n", argv[i]);
                return 1;
            }
            if(errno == ERANGE){
                fprintf(stderr, "Error: '%s' out of range\n", argv[i]);
                return 1;
            }

            sum += val;

            p = endptr;

            if(*p != '\0' && *p != ',' && *p != ' ' && *p != '\t'){
                fprintf(stderr, "Error: unexpected character '%c' in '%s'\n", *p, argv[i]);
                return 1;
            }
        }
    }

    printf("Average of sum %g with count %d: %g\n", sum, argc - 1, sum / (argc - 1));
    return 0;
}