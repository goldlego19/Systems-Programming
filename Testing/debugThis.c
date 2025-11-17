#include <stdio.h>
int main(int argc, char *argv[]){  
    int a = 5;
    char *n = "Johnny";
    #ifdef DEBUG
      	printf("Line %d: a=%d, n=%s\n", __LINE__, a, n);
    #endif
}
