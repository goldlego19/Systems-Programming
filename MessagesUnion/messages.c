#include <stdio.h>
#include <string.h>

enum MessageType { ERROR, TEMPERATURE, TEXT };

union MessageData {
        int errorCode;
        float temperature;
        char text[50];
    };

struct Message {
    enum MessageType type;
    union MessageData data;
};


struct Message fillErrorMessage(int c){
    struct Message m;
    m.type=ERROR;
    m.data.errorCode=c;
    return m;

}
struct Message fillTempMessage(float temp){
    struct Message m;
    m.type=TEMPERATURE;
    m.data.temperature=temp;
    return m;

}
struct Message fillTextMessage(char* t){
    struct Message m;
    m.type=TEXT;
    strcpy(m.data.text,t);
    return m;

}

void displayMessage(struct Message m){

    switch(m.type){
        case ERROR :
            printf("[ERROR CODE]  %d\n", m.data.errorCode);
            break;
        case TEMPERATURE:
            printf("[TEMPERATURE] %f\n", m.data.temperature);
            break;
        case TEXT:
            printf("[ERROR MESSAGE] %s\n", m.data.text);
            break;
    }

}
