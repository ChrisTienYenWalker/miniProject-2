#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#define _OPEN_SYS_ITOA_EXT

struct user_t scan_user(char*, double, double, double, double);
double distanceDifference(double, double, double, double, double, double);
int search(int, user_t, double[]);
typedef struct user_t
{
    double altitude;
    double time;
    double longitude;
    double latitude;
    char *name[50];
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
            user_t our_user = scan_user(inputs[1], strtod(inputs[2], &ptr), strtod(inputs[3], &ptr), strtod(inputs[4], &ptr), strtod(inputs[5], &ptr));
            FILE *txtfile;
            char text[20];
            long bytes;
            txtfile = fopen("sample_users.txt", "r");

            if (txtfile == NULL)
            {
                printf("File Empty");
            }

            int counter = -1;
            char *name;
            struct user_t other_users[50];
            double time, longitude, latitude, altitude;
            int arraypositionCounter = 0;
            int numberOfUsers;
            // char *ptr2;
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
                        // printf("%s", );
                        other_users[arraypositionCounter] = scan_user(name, time, longitude, latitude, altitude);
                        printf("%f", other_users[arraypositionCounter].time);
                        arraypositionCounter++;
                        
                        break;
                }
                counter++;
            }
            
            fclose(txtfile);

            double differences[50];
            for(int i = 0; i<numberOfUsers; i++){
                double distance = distanceDifference(other_users[i].longitude, our_user.longitude, other_users[i].latitude, our_user.latitude, other_users[i].altitude, other_users[i].altitude);
                differences[i] = distance;
            }

            int closest = search(numberOfUsers, our_user, differences);
            printf("closest: %s", other_users[1].name);

        }
    }
}

user_t scan_user(char* name, double time, double longitude, double latitude, double altitude){
    return user_t{altitude, time, longitude, latitude, name};
}

double distanceDifference(double longA, double longB, double latA, double latB, double altA, double altB){
    return sqrt((longA-longB)*(longA-longB) + (latA-latB)*(latA-latB) + (altA-altB));
}

int search(int numberOfUsers, user_t user, double otherUsers[] ){
            int closest = 0;
            double closestDistance = otherUsers[0];
            for(int i = 1; i < numberOfUsers; i++){
                if(closestDistance > otherUsers[i]){
                    closestDistance = otherUsers[i];
                    closest = i;
                }
            }
            return closest;
}