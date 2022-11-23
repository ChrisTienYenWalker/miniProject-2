#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#define _OPEN_SYS_ITOA_EXT

int *read(char *, char**);

typedef struct user_t {
    char name[50];
    double time;
    double latitude;
    double longitude;
    double altitude;
};

int main(int arguments, char* inputs[]){
    //makes sure that the user enters the right data
    if(arguments >= 5){
        //check if the first input is a character
        if(inputs[1][0] >40 && inputs[1][0] < 122){
            
        }
    }
}


