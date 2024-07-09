#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SHOWS 100

typedef struct {
    char name[100];
    char showID[50];
    char startTime[10];
    char date[15];
} Show;

Show shows[MAX_SHOWS];
int showCount = 0;

void addTheatreShow() {
    char choice;
    do {
        if (showCount >= MAX_SHOWS) {
            printf("Maximum show limit reached.\n");
            return;
        }

        printf("\nEnter the name of the drama : ");
        fgets(shows[showCount].name, sizeof(shows[showCount].name), stdin);
        shows[showCount].name[strcspn(shows[showCount].name, "\n")] = '\0';

        printf("Enter the show ID : ");
        fgets(shows[showCount].showID, sizeof(shows[showCount].showID), stdin);
        shows[showCount].showID[strcspn(shows[showCount].showID, "\n")] = '\0';  

        printf("Enter the start time : ");
        fgets(shows[showCount].startTime, sizeof(shows[showCount].startTime), stdin);
        shows[showCount].startTime[strcspn(shows[showCount].startTime, "\n")] = '\0';

        printf("Enter the date : ");
        fgets(shows[showCount].date, sizeof(shows[showCount].date), stdin);
        shows[showCount].date[strcspn(shows[showCount].date, "\n")] = '\0';  

        showCount++;
        printf("\nTheatre show added successfully!\n\n");
        printf("Do you want to add another theatre show? (Y/N): ");
        scanf(" %c", &choice);
        getchar();
    } while (choice == 'Y' || choice == 'y');
    printf("\n");
}

void displayTheatreSchedule() {

    printf("\n############################# Theatre Schedule Details ##############################\n\n");
    
    if (showCount == 0) {
        printf("No shows available.\n");
        return;
    }

    printf("----------------------------------------------------------------------------------------\n");
    printf("| %-30s | %-15s | %-15s | %-15s |\n", "Name", "Show ID", "Start Time", "Date");
    printf("----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < showCount; i++) {
        printf("| %-30s | %-15s | %-15s | %-15s |\n", shows[i].name, shows[i].showID, shows[i].startTime, shows[i].date);
    }

    printf("----------------------------------------------------------------------------------------\n\n");
}

int main() {
    int exit = 0;
    char option_no;
    
    printf("\n######################################################################\n\n");
    printf("  ▄██████▄            ▄▄█████⌐\n");
    printf("  ███  ▀██▌ ██▌  ╓██▄ ███▀└▀    ▄█████⌐ ╓▄████▄µ  ▄█████▄▄  ,▄████▄,\n");
    printf("  ████████  ▀██▌ ███⌐ ▀█████▄  ▄██▀` └ ▐███  ███∩ ███` ▀██▌ ███▄▄███\n");
    printf("  ███  ▐███  ███▄██▌  ▄   ▀███ ███▄    ▐██▌  ███▌ ███  ▐██▌ ███▀▀▀▀└\n");
    printf("  ████████▀   ▀███▌   ███████▀  ▀█████▌ ▀██████▀  ███████▀   ███████\n");
    printf("             ▄███▀                                ███\n");
    printf("             └▀▀                                  ╙▀▀\n");
    printf("################### ByScope Theatre Systems (BTS) ####################\n");
    printf("######################################################################\n\n");
    
   while (exit == 0) {
        printf("###########\n");
        printf("# Main Menu\n");
        printf("###########\n");

        printf("1 => Add Theatre Show\n");
        printf("2 => Display Theatre Schedule\n");
        printf("3 => Display Theatre Reservations\n");
        printf("4 => Reserve Seats\n");
        printf("5 => Exit\n\n");

        printf("Enter option number: ");
        scanf(" %c", &option_no);
        getchar();

        switch (option_no) {
            case '1':
                addTheatreShow();
                break;
            case '2':
                displayTheatreSchedule();
                break;
            case '3':
                printf("Display Theatre Reservations not implemented yet.\n");
                break;
            case '4':
                printf("Reserve Seats not implemented yet.\n");
                break;
            case '5':
                printf("\n######################################################################\n");
                printf("############################# Thank You! #############################\n");
                printf("######################################################################\n");
                exit = 1;
                break;
            default:
                printf("\nInvalid Input!\n\n");
                break;
        }
    }

    return (0);
}
