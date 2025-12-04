#ifndef MESSAGES_H_INCLUDED
    #define MESSAGES_H_INCLUDED

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


    struct Message fillErrorMessage(int c);
    struct Message fillTempMessage(float temp);
    struct Message fillTextMessage(char* t);

    void displayMessage(struct Message m);
#endif
