#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
// #define _OPEN_SYS_ITOA_EXT

typedef struct 
{
    double time;
    double longitude;
    double latitude;
    double altitude;
    char name[50];
} user_t;

int search(int numberOfUsers, user_t user, double otherUsers[]);
user_t scan_user();
double distanceDifference(double, double, double, double, double, double);
int scanFile(void);
int scanManual(void);
 
// int search(int, user_t, double[]);

int main()
{

    // check if the first input is a character
    char scanFromFile;
    printf("Would you like to scan from console: Y/N\n");
    scanf("%c", &scanFromFile);
    if (scanFromFile == 'Y')
    {
        scanManual();
        
        return 0;
    }
    else if (scanFromFile == 'N')
    {
        scanFile();
    }
    else
    {
        printf("Not an option");
        return 0;
    }
}

int scanManual(void){
    user_t allUsers[100];
        printf("Enter your user data: ");
        allUsers[0] = scan_user();
        int numberOfOtherUsers;
        int numberOfUsers = 1;
        printf("How many other users do you want to add: ");
        scanf("%d", &numberOfOtherUsers);
        numberOfUsers = numberOfOtherUsers+1;
        for (int i = 1; i < numberOfUsers; i++)
        {
            printf("Enter other user #%d data: ", i+1);
            allUsers[i] = scan_user();
        }

        double differences[50];
        for(int i = 0; i < numberOfUsers; i++){
            printf("Name: %s\n", allUsers[i].name);
            printf("Time: %.2lf\n", allUsers[i].time);
            printf("Longitude: %.2lf\n", allUsers[i].longitude);
            printf("Latitude: %.2lf\n", allUsers[i].latitude);
            printf("Altitude: %.2lf\n", allUsers[i].altitude);
        }
        for (int i = 0; i < numberOfOtherUsers; i++)
        {
            double distance = distanceDifference(allUsers[i + 1].longitude, allUsers[0].longitude, allUsers[i + 1].latitude, allUsers[0].latitude, allUsers[i + 1].altitude, allUsers[0].altitude);
            differences[i] = distance;
            printf("%lf\n", differences[i] );
            printf("%s", allUsers[i + 1].name);
        }


        int closest = search(numberOfOtherUsers, allUsers[0], differences)+1;
        printf("%d", closest);
        
        printf("\nClosest: \n");
        printf("Name: %s\n", allUsers[closest].name);
        printf("Time: %.2lf\n", allUsers[closest].time);
        printf("Longitude: %.2lf\n", allUsers[closest].longitude);
        printf("Latitude: %.2lf\n", allUsers[closest].latitude);
        printf("Altitude: %.2lf\n", allUsers[closest].altitude);
        printf("Distance: %.2lf\n", differences[closest-1]);

}
user_t scan_user()
{
    user_t user;
    printf("\nEnter name: ");
    scanf("%s", &user.name);
    printf("Enter time: ");
    scanf("%lf", &user.time);
    printf("Enter longitude: ");
    scanf("%lf", &user.longitude);
    printf("Enter latitude: ");
    scanf("%lf", &user.latitude);
    printf("Enter altitude: ");
    scanf("%lf", &user.altitude);
    return user;
}

double distanceDifference(double longA, double longB, double latA, double latB, double altA, double altB)
{
    return sqrt((longA - longB) * (longA - longB) + (latA - latB) * (latA - latB) + (altA - altB) * (altA - altB));
}

int search(int numberOfOtherUsers, user_t user, double otherUsers[])
{
    int closest = 0;
    double closestDistance = otherUsers[0];
    for (int i = 0; i < numberOfOtherUsers; i++)
    {
        if (closestDistance > otherUsers[i])
        {
            closestDistance = otherUsers[i];
            closest = i;
        }
    }
    return closest+1;
}

int scanFile(void){
    user_t allUsers[100];

        char *ptr;
        // char *text = read("sample_users.txt");
        FILE *txtfile;
        char text[20];
        long bytes;
        char filename[50];
        printf("Enter file name: ");
        scanf("%s", filename);
        txtfile = fopen(filename, "r");

        if (txtfile == NULL)
        {
            printf("File Empty");
            return 0;
        }

        int counter = -1;
        int numberOfUsers = 0;
        int arraypositionCounter = 0;
        // char *ptr2;
        while (fgets(text, 20, txtfile))
        {
            if (counter == -1)
            {
                numberOfUsers = atoi(text);
                counter++;
                continue;
            }
            switch (counter)
            {
            case 0:
                strcpy(allUsers[arraypositionCounter].name, text);
                // printf("%s", text);
                break;
            case 1:
                allUsers[arraypositionCounter].time = strtod(text, &ptr);
                // printf("%f", time);
                break;
            case 2:
                allUsers[arraypositionCounter].longitude = strtod(text, &ptr);
                break;
            case 3:
                allUsers[arraypositionCounter].latitude = strtod(text, &ptr);
                break;
            case 4:
                allUsers[arraypositionCounter].altitude = strtod(text, &ptr);
                counter = -1;
                // printf("%f", time);
                // printf("%s", );
                // printf("%f", other_users[arraypositionCounter].time);
                arraypositionCounter++;

                break;
            }
            counter++;
        }
        fclose(txtfile);

        double differences[50];
        for (int i = 0; i < numberOfUsers; i++)
        {
        double distance = distanceDifference(allUsers[i + 1].longitude, allUsers[0].longitude, allUsers[i + 1].latitude, allUsers[0].latitude, allUsers[i + 1].altitude, allUsers[0].altitude);
            differences[i] = distance;
            printf("%lf\n", differences[i] );
            // printf("%s", allUsers[i + 1].name);
        }

        int closest = search(numberOfUsers, allUsers[0], differences);
        
        printf("\nClosest: ");
        printf("Name: %s", allUsers[closest].name);
        printf("Time: %.2lf\n", allUsers[closest].time);
        printf("Longitude: %.2lf\n", allUsers[closest].longitude);
        printf("Latitude: %.2lf\n", allUsers[closest].latitude);
        printf("Altitude: %.2lf\n", allUsers[closest].altitude);
        printf("Distance: %.2lf\n", differences[closest-1]);
}