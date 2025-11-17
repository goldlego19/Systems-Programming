#include <stdio.h>
#include <stdlib.h>


void print(int buf){
    printf("Hello %d!", buf);
}


void do_user_input(){
    int buf;

    printf("Please enter your name: ");
    scanf("%d",&buf);
    print(buf);
}


int main(int argc, char **argv) {
	do_user_input();
	return 0;
}
