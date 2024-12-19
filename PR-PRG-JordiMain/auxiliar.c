#include "auxiliar.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "voyage.h"

void deleteLinespace(char *line) {
    line[strlen(line)-1] = '\0';
}

void askForString(String str, char* message) {
    //el message es el mensaje que se muestra antes de pedir el string
    int error = 1;

    while (error) {
        printf("%s", message);
        fgets(str, 100, stdin);
        str[strlen(str)-1] = '\0';
        error = checkHashtag(str);
        if (error) {
            printf("the string contains '#'.\n");
        }
    }
}

void askForLongString(LongString str, char* message) {
    int error = 1;

    while (error) {
        printf("%s", message);
        fgets(str, 1000, stdin);
        str[strlen(str)-1] = '\0';
        error = checkHashtag(str);
        if (error) {
            printf("the string contains '#'.\n");
        }
    }
}

float checkDecimal(String str) {
    float num;
    int check = 1;
    for(int i = 0; i < strlen(str); i++){
        if(!isdigit(str[i]) && str[i] != '.'){
            check = 0;
        }
    }
    if(check == 1) {
        num = atof(str);
    }else{
        num = -1;
    }
    return num;
}

int checkInt(String str){
    int check = 1, num;
    for(int i = 0; i < strlen(str); i++){
        if(!isdigit(str[i])){
            check = 0;
        }
    }
    if(check == 1) {
        num = atoi(str);
    }else{
        num = -1;
    }
    return num;
}

int checkHashtag(String str){
    int error = 0;
    for(int i = 0; i < strlen(str); i++){
        if(str[i] == '#') {
            error = 1;
            i = strlen(str);
        }
    }
    return error;
}