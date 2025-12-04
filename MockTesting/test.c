#include <stdio.h> 
#include <string.h> 
typedef union U { 
   char name[75]; 
   char surname[75]; 
} u; 
int main() { 
    u test;  
    strcpy(test.name, "Alicia");  
    printf("%s %s is a singer2\n", test.name, test.name); 

    strcpy(test.surname, "Keys");
    printf("%s %s is a singer\n", test.surname, test.name); 
} 