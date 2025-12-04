#include <stdio.h>
#include "toys.h"  
#include "users.h"

int main(void) {  
    toy yoyo;
    yoyo.price = 9.61;
    child jon; 
    jon.gift = &yoyo;
    printf("you pay: %.2lf\n", jon.gift->price);
    return 0;
}