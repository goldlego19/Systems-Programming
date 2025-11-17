//write a program that accepts two numbers at command line and displays the addition of these numbers
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if(argc!=3){
        printf("You need to enter two numbers");
        return 0;
    }

    int num1 = atoi(argv[1]); //converts numeric string to integer
    int num2 = atoi(argv[2]);
    printf("The Addition of %d and %d is %d",num1,num2,num1+num2);
}