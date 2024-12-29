#ifndef AUXILIAR_H
#define AUXILIAR_H

typedef char String[100];

typedef char LongString[1000];

void askForString(String str, char* message);

void askForLongString(LongString str, char *message);

float checkDecimal(String str);   //return 0 si false

int checkInt(String str);   //return 0 si false

int checkHashtag(String str);

void deleteLinespace(char* str);

char* itoa(int value, String str, int base);

#endif