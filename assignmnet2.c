#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SHOWS 100


typedef struct {
    char name[100];
    char showID[50];
    char startTime[10];
    char date[15];
    char seats[10];
} Show;

Show shows[MAX_SHOWS];
int showCount = 0;

void loadShowsFromFile() {
    FILE *file = fopen("show_schedules.txt", "r");
    if (file == NULL) {
        return;
    }

    while (fscanf(file, "%99[^;];%49[^;];%9[^;];%14[^;];%9[^;]\n", shows[showCount].name, shows[showCount].showID, shows[showCount].startTime, shows[showCount].date, shows[showCount].seats) == 5) {
        showCount++;
        if (showCount >= MAX_SHOWS) {
            printf("Maximum show limit reached while loading from file.\n");
            break;
        }
    }

    fclose(file);
}

int isDuplicateShow(Show newShow) {
    for (int i = 0; i < showCount; i++) {
        if (strcmp(shows[i].startTime, newShow.startTime) == 0 && strcmp(shows[i].date, newShow.date) == 0) {
            return 1; // Duplicate show found
        }
    }
    return 0;
}

void saveShowToFile(Show show) {
    FILE *file = fopen("show_schedules.txt", "a");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    printf("%s;%s;%s;%s;%s\n", show.name, show.showID, show.startTime, show.date, show.seats);
    fprintf(file, "%s;%s;%s;%s;%s\n", show.name, show.showID, show.startTime, show.date, show.seats);
    fclose(file);
}

void addTheatreShow() {
    char choice;
    do {
        if (showCount >= MAX_SHOWS) {
            printf("Maximum show limit reached.\n");
            return;
        }

        Show newShow;
        printf("\nEnter the name of the drama : ");
        fgets(newShow.name, sizeof(newShow.name), stdin);
        newShow.name[strcspn(newShow.name, "\n")] = '\0';

        printf("Enter the show ID : ");
        fgets(newShow.showID, sizeof(newShow.showID), stdin);
        newShow.showID[strcspn(newShow.showID, "\n")] = '\0';

        printf("Enter the start time : ");
        fgets(newShow.startTime, sizeof(newShow.startTime), stdin);
        newShow.startTime[strcspn(newShow.startTime, "\n")] = '\0';

        printf("Enter the date : ");
        fgets(newShow.date, sizeof(newShow.date), stdin);
        newShow.date[strcspn(newShow.date, "\n")] = '\0';

        printf("Enter the seat count : ");
        fgets(newShow.seats, sizeof(newShow.seats), stdin);
        newShow.seats[strcspn(newShow.seats, "\n")] = '\0';

        if (isDuplicateShow(newShow)) {
            printf("A show is already scheduled at this time and date.\n");
        } else {

            shows[showCount++] = newShow;
            saveShowToFile(newShow);
            printf("\nTheatre show added successfully!\n\n");
        }

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

    printf("----------------------------------------------------------------------------------------------\n");
    printf("| %-30s | %-15s | %-15s | %-15s | %-15s |\n", "Name", "Show ID", "Start Time", "Date", "Seats");
    printf("----------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < showCount; i++) {
        printf("| %-30s | %-15s | %-15s | %-15s | %-15s |\n", shows[i].name, shows[i].showID, shows[i].startTime, shows[i].date,shows[i].seats);
    }

    printf("----------------------------------------------------------------------------------------------\n\n");
}

int main() {
    loadShowsFromFile();

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
