#include <stdio.h>
#include <string.h>

enum MessageType{ERROR,TEMPERATURE,TEXT};

union MessageData {
    int errorCode;
    float temperature;
    char text[50];
};

struct Message{
    enum MessageType type;
    union MessageData data;
};



int main(){
    int choice;
    struct Message oneMessage;
    printf("Press 1 to enter code\n");
    printf("Press 2 to enter temperature\n");
    printf("Press 3 to enter text\n");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        oneMessage.type = ERROR;
        printf("\nEnter errorCode");
        scanf("%d",&oneMessage.data.errorCode);
        break;
    case 2:
        oneMessage.type = TEMPERATURE;
        printf("\nEnter temperature");
        scanf("%f",&oneMessage.data.temperature);
        break;
    case 3:
        oneMessage.type = TEXT;
        printf("\nEnter text: ");
        getchar();
        scanf("%49[^\n]",oneMessage.data.text);
        break;
    default:
        break;
    }

    switch (oneMessage.type)
    {
    case ERROR:
        printf("\n[ERROR CODE]: %d",oneMessage.data.errorCode);
        break;
    case TEMPERATURE:
        printf("\n[TEMPERATURE]: %f",oneMessage.data.temperature);
        break;
    case TEXT:
        printf("\n[TEXT]: %s",oneMessage.data.text);
        break;
    default:
        break;
    }

}
