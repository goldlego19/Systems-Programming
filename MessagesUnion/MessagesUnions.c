#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "messages.h"

int main() {
    int choice;
    struct Message oneMessage;
    //FILL IN
    printf("Press 1 to enter code\n");
    printf("Press 2 to enter temperature\n");
    printf("Press 3 to enter text\n");
    scanf("%d", &choice);
    switch(choice){
        case 1:
            printf("Enter error code: ");
            int error;
            scanf("%d", &error); //test
            oneMessage = fillErrorMessage(error);
            break;
        case 2:
            printf("Enter temperature: ");
            float temp;
            scanf("%f", &temp); 
            oneMessage = fillTempMessage(temp);
            break;
        case 3:
            printf("Enter error message: ");
            getchar();
            char* msg = (char*)malloc(sizeof(char)*50);
            scanf("%49[^\n]", msg);  //test because of leading whitespace
            oneMessage = fillTextMessage(msg);
            break;
        default:
            break;
    }
    //DISPLAY
    displayMessage(oneMessage);
}
    