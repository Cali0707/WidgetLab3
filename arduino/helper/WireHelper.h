#ifndef ARDUINOHELPER_WIREHELPER_H
#define ARDUINOHELPER_WIREHELPER_H

void readFromWire(char *dest, int num);
void sendMessage(const char* message, int address);

#endif //ARDUINOHELPER_WIREHELPER_H
