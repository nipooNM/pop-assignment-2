#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SHOWS 100
#define ROWS 16
#define COLUMNS 20

typedef struct {
    char status; // *: available, #: reserved with pay, o: reserved without pay
    char category[10];
} Seat;

typedef struct {
    char name[100];
    char showID[50];
    char startTime[10];
    char date[15];
    Seat seats[ROWS][COLUMNS];
} Show;

Show shows[MAX_SHOWS];
int showCount = 0;

void initializeSeats(Seat seats[ROWS][COLUMNS]);
void displayAvailableSeats(Seat seats[ROWS][COLUMNS], char *category);
void reserveSeats(Seat seats[ROWS][COLUMNS], char *showID);
void loadShowsFromFile();
void saveShowToFile(Show show);
int isDuplicateShow(Show newShow);
void addTheatreShow();
void displayTheatreSchedule();
void displayTheatreReservations();

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
                displayTheatreReservations();
                break;
            case '4':
                printf("Enter the show ID: ");
                char showID[50];
                fgets(showID, sizeof(showID), stdin);
                showID[strcspn(showID, "\n")] = '\0';
                for (int i = 0; i < showCount; i++) {
                    if (strcmp(shows[i].showID, showID) == 0) {
                        reserveSeats(shows[i].seats, shows[i].showID);
                        break;
                    }
                }
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

    return 0;
}

void initializeSeats(Seat seats[ROWS][COLUMNS]) {
    // Initialize all seats as available and assign categories based on seat layout
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            seats[i][j].status = '*';

            if ((i == 0 || i == 1) && (j >= 4 && j <= 14)) {
                strcpy(seats[i][j].category, "Twin");
            } else if (i >= 0 && i <= 5) {
                strcpy(seats[i][j].category, "VVIP");
            } else if (i >= 6 && i <= 11) {
                strcpy(seats[i][j].category, "VIP");
            } else {
                strcpy(seats[i][j].category, "Economy");
            }
        }
    }
}

void displayAvailableSeats(Seat seats[ROWS][COLUMNS], char *category) {
    printf("Available seats for category %s:\n", category);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (strcmp(seats[i][j].category, category) == 0 && seats[i][j].status == '*') {
                printf("%c%d ", 'A' + i, j + 1);
            }
        }
    }
    printf("\n");
}

void reserveSeats(Seat seats[ROWS][COLUMNS], char *showID) {
    int numSeats;
    char category[10];
    char selectedSeats[50];
    char action;

    printf("Enter the number of seats required: ");
    scanf("%d", &numSeats);
    getchar();

    printf("Desired seat category (Twin/VVIP/VIP/Economy): ");
    fgets(category, sizeof(category), stdin);
    category[strcspn(category, "\n")] = '\0';

    displayAvailableSeats(seats, category);

    printf("Choose seats (e.g., A5,B6): ");
    fgets(selectedSeats, sizeof(selectedSeats), stdin);
    selectedSeats[strcspn(selectedSeats, "\n")] = '\0';

    printf("Action: x/o/# (#: reserve with pay, o: reserve without pay, x : cancel reservation): ");
    scanf(" %c", &action);
    getchar();

    char *seatToken = strtok(selectedSeats, ",");
    while (seatToken != NULL) {
        int row = seatToken[0] - 'A';
        int col = atoi(seatToken + 1) - 1;

        if (row >= 0 && row < ROWS && col >= 0 && col < COLUMNS) {
            if (action == '#') {
                seats[row][col].status = '#';
                printf("Seat %s confirmed as reserved with pay\n", seatToken);
            } else if (action == 'o') {
                seats[row][col].status = 'o';
                printf("Seat %s confirmed as reserved without pay\n", seatToken);
            } else if (action == 'x') {
                seats[row][col].status = '*';
                printf("Reservation for seat %s cancelled\n", seatToken);
            }
        } else {
            printf("Invalid seat: %s\n", seatToken);
        }

        seatToken = strtok(NULL, ",");
    }
}

void loadShowsFromFile() {
    FILE *file = fopen("show_schedules.txt", "r");
    if (file == NULL) {
        return;
    }

    while (fscanf(file, "%99[^;];%49[^;];%9[^;];%14[^;]\n", shows[showCount].name, shows[showCount].showID, shows[showCount].startTime, shows[showCount].date) == 4) {
        initializeSeats(shows[showCount].seats);
        showCount++;
        if (showCount >= MAX_SHOWS) {
            printf("Maximum show limit reached while loading from file.\n");
            break;
        }
    }

    fclose(file);
}

void saveShowToFile(Show show) {
    FILE *file = fopen("show_schedules.txt", "a");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(file, "%s;%s;%s;%s\n", show.name, show.showID, show.startTime, show.date);
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

void addTheatreShow() {
    char choice;
    do {
        if (showCount >= MAX_SHOWS) {
            printf("Maximum show limit reached.\n");
            return;
        }

        Show newShow;
        printf("\nEnter the name of the drama: ");
        fgets(newShow.name, sizeof(newShow.name), stdin);
        newShow.name[strcspn(newShow.name, "\n")] = '\0';

        printf("Enter the show ID: ");
        fgets(newShow.showID, sizeof(newShow.showID), stdin);
        newShow.showID[strcspn(newShow.showID, "\n")] = '\0';

        printf("Enter the start time: ");
        fgets(newShow.startTime, sizeof(newShow.startTime), stdin);
        newShow.startTime[strcspn(newShow.startTime, "\n")] = '\0';

        printf("Enter the date: ");
        fgets(newShow.date, sizeof(newShow.date), stdin);
        newShow.date[strcspn(newShow.date, "\n")] = '\0';

        if (isDuplicateShow(newShow)) {
            printf("A show is already scheduled at this time and date.\n");
        } else {
            initializeSeats(newShow.seats);
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
    printf("| %-30s | %-15s | %-15s | %-15s |\n", "Name", "Show ID", "Start Time", "Date");
    printf("----------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < showCount; i++) {
        printf("| %-30s | %-15s | %-15s | %-15s |\n", shows[i].name, shows[i].showID, shows[i].startTime, shows[i].date);
    }

    printf("----------------------------------------------------------------------------------------------\n\n");
}

void displayTheatreReservations() {
    printf("\n############################# Theatre Reservations ##############################\n\n");

    if (showCount == 0) {
        printf("No shows available.\n");
        return;
    }

    for (int i = 0; i < showCount; i++) {
        printf("Show ID: %s | Show Name: %s\n", shows[i].showID, shows[i].name);
        printf("----------------------------------------------------------------------------------------------\n");
        printf("Seat Layout: (Categories - *: available, #: reserved with pay, o: reserved without pay)\n");
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLUMNS; c++) {
                printf("%c ", shows[i].seats[r][c].status);
            }
            printf("\n");
        }
        printf("----------------------------------------------------------------------------------------------\n\n");
    }
}
