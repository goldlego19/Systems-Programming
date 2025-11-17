#include <stdio.h>
#include <stdlib.h>

int global_init = 10;
int global_uninit;

void test(void){
    int local = 20;
    static int local_static =50;
    printf("Local %d Address %p\n", local,&local); //this variable dies with the function                   
    printf("Local Static %d Address %p\n", local_static,&local_static); 
    global_init++;
    local_static++; // the new value is incremented, this variable stays alive!!

}

void main(void){
    printf("Global_init %d Address %p\n",global_init,&global_init);
    printf("Global_uninit %d Address %p\n",global_uninit,&global_uninit);
    // printf("Local %d", local);                   
    // printf("Local Static %d", local_static);     // cannot refer outside of function
    test();
    int * p = (int*)malloc(sizeof(int));
    printf("The Address of th pointer %p (stack)\n",&p);
    printf("The Stack frame of test is at address %p\n",test);
    printf("The Stack frame of est is at address %p\n",main);
    printf("Global_init %d", global_init);

}