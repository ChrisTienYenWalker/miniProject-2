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
    if (arguments >= 6)
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
            double time, longitude, latitude, altitude;
            int arraypositionCounter = 0;
            int numberOfUsers;
            while (fgets(text, 20, txtfile))
            {
                if(counter == -1){
                    numberOfUsers = atoi(text);
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
                        longitude = strtod(text, &ptr);
                        break;
                    case 3:
                        latitude = strtod(text, &ptr);
                        break;
                    case 4:
                        altitude = strtod(text, &ptr);
                        counter = -1;
                        // printf("%f", time);
                        other_users[arraypositionCounter] = {altitude, time, longitude, latitude, name};
                        arraypositionCounter++;
                        
                        break;
                }
                counter++;
            }
            
            struct user_t differences[50];
            for(int i = 0; i<numberOfUsers; i++){
                differences[i] = {our_user.altitude-other_users[i].altitude, our_user.time-other_users[i].time, our_user.longitude-other_users[i].longitude, our_user.latitude-other_users[i].latitude, (char*) other_users[i].name};
            }
            fclose(txtfile);

        }
    }
}

