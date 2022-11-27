#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#define _OPEN_SYS_ITOA_EXT

char *read(char *);

typedef struct user_t
{
    double altitude;
    double time;
    double longitude;
    double latitude;
    const char *name[50];
};

int main(int arguments, char *inputs[])
{
    //inputs should be filename, name, time, longitude, latitude, altitude
    // makes sure that the user enters the right data
    if (arguments >= 5)
    {
        // check if the first input is a character
        if (inputs[1][0] > 40 && inputs[1][0] < 122)
        {
            char *ptr;
            // char *text = read("sample_users.txt");
            user_t our_user = {strtod(inputs[5], &ptr), strtod(inputs[2], &ptr), strtod(inputs[3], &ptr), strtod(inputs[4], &ptr), inputs[1]};
            FILE *txtfile;
            char text[20];
            long bytes;
            txtfile = fopen("sample_users.txt", "r");

            if (txtfile == NULL)
            {
                printf("File Empty");
            }

            int counter = -1;
            const char *name;
            struct user_t other_users[50];
            double time, logitude, latitude, altitude;
            int arraypositionCounter = 0;
            while (fgets(text, 20, txtfile))
            {
                if(counter == -1){
                    int numberOfUsers = atoi(text);
                    counter++;
                    continue;
                }
                switch (counter){
                    case 0:
                        name = text;
                        // printf("%s", text);
                        break;
                    case 1:
                        time = strtod(text, &ptr);
                        // printf("%f", time);
                        break;
                    case 2:
                        logitude = strtod(text, &ptr);
                        break;
                    case 3:
                        latitude = strtod(text, &ptr);
                        break;
                    case 4:
                        altitude = strtod(text, &ptr);
                        counter = -1;
                        // printf("%f", time);
                        other_users[arraypositionCounter] = {altitude, time, logitude, latitude, name};
                        arraypositionCounter++;
                        
                        break;
                }
                counter++;
            }

            fclose(txtfile);
            // int numberOfEnteries = 0;
            // int digits = 0;
            // for(int i = 0; i < strlen(text); i++){
            //     if(text[i] == '\n'){
            //         break;
            //     }
            //     numberOfEnteries = numberOfEnteries*10 + (int) text[i]-'0';
            //     digits++;
            // }
            // printf("%d", numberOfEnteries);

            // struct user_t other_users[50];
            // for(int i = 0; i < numberOfEnteries; i++){
            //     other_users[i] = {"", 0, 0, 0, 0};
            // }
            // char *textArray[250][16];
            // int textArraycounter = 0;
            // digits++;
            // int referencePosition = text[digits];
            // int positionInUserArray = 0;
            // for(int i = digits; i < strlen(text); i++){
            //     if(text[i] == '\n'){
            //         char copiedText[50] = "15.02";
            //         // strncpy(copiedText,&text[referencePosition],i - referencePosition);                                            printf("hi");
            //                                 printf("hi");

            //         if((i-digits)%5 == 0){
            //             other_users[positionInUserArray].altitude = atoi(copiedText);
            //             continue;
            //         }
            //         else if((i-digits)%4 == 0){
            //             other_users[positionInUserArray].latitude = atoi(copiedText);
            //             continue;
            //         }
            //         else if((i-digits)%3 == 0){
            //             other_users[positionInUserArray].longitude =atoi(copiedText);
            //             continue;
            //         }
            //         else if((i-digits)%2 == 0){
            //             other_users[positionInUserArray].time =15;
            //             continue;
            //         }
            //         else if((i-digits)%1 == 0){
            //             // other_users[positionInUserArray].name = copiedText;
            //             continue;
            //         }
            //         textArraycounter++;
            //         referencePosition = i + 1;

            //     }
            // }

            //     printf("\n%d\n\n", other_users[1].time);
        }
    }
}

char *read(char *fileName)
{
    FILE *txtfile;
    char *text;
    long bytes;
    // open and read file

    return text;
}
