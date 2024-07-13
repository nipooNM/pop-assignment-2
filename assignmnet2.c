#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SHOWS 100
#define MAX_RESERVATIONS 320

typedef struct {
    char name[100];
    char showID[50];
    char startTime[10];
    char date[15];
    char seats[10];
} Show;

typedef struct{
	char row;
	int coloumn;
} Seat;

typedef struct{
	char showID[50];
	Seat seats[320];
	int numberOfSeats;
} Reservation;


Show shows[MAX_SHOWS];
Reservation reservations[MAX_RESERVATIONS];

int showCount = 0;
int reservationCount=0;

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

void displayTheaterReservationss(){
	/*
	stpcpy(reservations[0].showID,"FF9");
	reservations[0].seats[0].row='A';
	reservations[0].seats[0].coloumn=10;
	reservations[0].numberOfSeats=1;
	
	reservationCount++;
	*/
	
	printf("\n=================Current reservations=================\n");

	for(int i=0;i<reservationCount;i++){			
		for(int j=0;j<showCount;j++){
			if(strcmp(reservations[i].showID,shows[j].showID)==0){
				printf("Show ID: %s\n",shows[j].showID);
				printf("Show name: %-30s\n",shows[j].name);
				printf("Show start time: %s\n",shows[j].startTime);
				printf("Short date: %s\n",shows[j].date);
				printf("\n");
				break;
			}				
		}		
	}

	printf("\n=================Summery of reservations=================\n");
	
	int vvip_total=98;
	int vip_total=120;
	int twin_total=22;
	int economy_total=80;	
	
	int vvip_count=0;
	int vip_count=0;
	int twin_count=0;
	int economy_count=0;
	
	for(int i=0;i<reservationCount;i++){
		for(int j=0;j<MAX_RESERVATIONS;j++){
			if((reservations[i].seats[j].row=='A')||(reservations[i].seats[j].row=='B')){
				if(reservations[i].seats[j].coloumn>4&&reservations[i].seats[j].coloumn<16){
					twin_count++;
				}else{
					vvip_count++;
				}
			}else if((reservations[i].seats[j].row=='C')||(reservations[i].seats[j].row=='D')||(reservations[i].seats[j].row=='E')||(reservations[i].seats[j].row=='F')){
				vvip_count++;			
			}else if((reservations[i].seats[j].row=='G')||(reservations[i].seats[j].row=='H')||(reservations[i].seats[j].row=='I')||(reservations[i].seats[j].row=='J')||(reservations[i].seats[j].row=='K')||(reservations[i].seats[j].row=='L')){
				vip_count++;
			}else if((reservations[i].seats[j].row=='M')||(reservations[i].seats[j].row=='N')||(reservations[i].seats[j].row=='O')||(reservations[i].seats[j].row=='P')){
				economy_count++;
			}else{
				//nothing to increase
			}
		}			
	}
	
	printf("Reservations in VVIP category: %d\n",vvip_count);
	printf("Available in VVIP category: %d\n",vvip_total-vvip_count);	
	printf("\nReservations in VIP category: %d\n",vip_count);
	printf("Available in VIP category: %d\n",vip_total-vip_count);	
	printf("\nReservations in Twin seat category: %d\n",twin_count);
	printf("Available in Twin seat category: %d\n",twin_total-twin_count);	
	printf("\nReservations in Economy seat category: %d\n",economy_count);
	printf("Available in Economy category: %d\n",economy_total-economy_count);
	
	printf("\n=================Summery of Profits=================\n");
	double vvip_seat_price=5000.00;
	double vip_seat_price=2000.00;
	double twin_seat_price=1000.00;
	double economy_seat_price=500.00;
	
	printf("Profit from VVIP category: %.2lf\n",vvip_count*vvip_seat_price);
	printf("Profit from VIP category: %.2lf\n",vip_count*vip_seat_price);
	printf("Profit from Twin seat category: %.2lf\n",twin_count*twin_seat_price);
	printf("Profit from Economy seat category: %.2lf\n\n",economy_count*economy_seat_price);

	
	
}

#define TOTAL_ROWS 16
#define TOTAL_COLUMNS 20
#define SEAT_SYMBOL_AVAILABLE '*'
#define SEAT_SYMBOL_RESERVED '#'
#define SEAT_SYMBOL_UNPAID 'o'

char seatLayout[TOTAL_ROWS][TOTAL_COLUMNS];

void initializeSeatLayout() {
    for (int i = 0; i < TOTAL_ROWS; i++) {
        for (int j = 0; j < TOTAL_COLUMNS; j++) {
            seatLayout[i][j] = SEAT_SYMBOL_AVAILABLE;
        }
    }
}
void updateSeatLayout() {
    for (int i = 0; i < reservationCount; i++) {
        for (int j = 0; j < reservations[i].numberOfSeats; j++) {
            int row = reservations[i].seats[j].row - 'A';  // Convert row character to index
            int column = reservations[i].seats[j].coloumn - 1;  // Convert column to 0-based index

            // You can decide on the logic for reserved, unpaid, or paid seats
            seatLayout[row][column] = SEAT_SYMBOL_RESERVED;
        }
    }
}

void displaySeatLayout() {
    printf("\nTheatre Seat Layout:\n");
    printf("   ");
    for (int j = 1; j <= TOTAL_COLUMNS; j++) {
         printf(" %2d", j); // Print column numbers with padding
    }
    printf("\n");

    for (int i = 0; i < TOTAL_ROWS; i++) {
        printf("%c  ", 'A' + i);  // Print row labels (A, B, C, ...)
        for (int j = 0; j < TOTAL_COLUMNS; j++) {
            printf(" %c ", seatLayout[i][j]);
        }
        printf("\n");
    }
}


void displayTheaterReservations() {
    // Initialize seat layout
    initializeSeatLayout();
    
    // Update seat layout with reservations
    updateSeatLayout();
    
    // Display the seating arrangement
    displaySeatLayout();
    
    // Additional information
    printf("\n=================Summery of Reservations=================\n");
    
    int vvip_total = 98;
    int vip_total = 120;
    int twin_total = 22;
    int economy_total = 80;  
    
    int vvip_count = 0;
    int vip_count = 0;
    int twin_count = 0;
    int economy_count = 0;
    
    for (int i = 0; i < reservationCount; i++) {
        for (int j = 0; j < reservations[i].numberOfSeats; j++) {
            char row = reservations[i].seats[j].row;
            int column = reservations[i].seats[j].coloumn;
            
            if ((row == 'A') || (row == 'B')) {
                if (column > 4 && column < 16) {
                    twin_count++;
                } else {
                    vvip_count++;
                }
            } else if ((row == 'C') || (row == 'D') || (row == 'E') || (row == 'F')) {
                vvip_count++;            
            } else if ((row == 'G') || (row == 'H') || (row == 'I') || (row == 'J') || (row == 'K') || (row == 'L')) {
                vip_count++;
            } else if ((row == 'M') || (row == 'N') || (row == 'O') || (row == 'P')) {
                economy_count++;
            }
        }            
    }
    
    printf("Reservations in VVIP category: %d\n", vvip_count);
    printf("Available in VVIP category: %d\n", vvip_total - vvip_count);    
    printf("\nReservations in VIP category: %d\n", vip_count);
    printf("Available in VIP category: %d\n", vip_total - vip_count);    
    printf("\nReservations in Twin seat category: %d\n", twin_count);
    printf("Available in Twin seat category: %d\n", twin_total - twin_count);    
    printf("\nReservations in Economy seat category: %d\n", economy_count);
    printf("Available in Economy category: %d\n", economy_total - economy_count);
    
    printf("\n=================Summery of Profits=================\n");
    double vvip_seat_price = 5000.00;
    double vip_seat_price = 2000.00;
    double twin_seat_price = 1000.00;
    double economy_seat_price = 500.00;
    
    printf("Profit from VVIP category: %.2lf\n", vvip_count * vvip_seat_price);
    printf("Profit from VIP category: %.2lf\n", vip_count * vip_seat_price);
    printf("Profit from Twin seat category: %.2lf\n", twin_count * twin_seat_price);
    printf("Profit from Economy seat category: %.2lf\n\n", economy_count * economy_seat_price);
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
        printf("4 => Display Theatre Reservations\n");
        printf("5 => Reserve Seats\n");
        printf("6 => Exit\n\n");

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
				displayTheaterReservationss();
                break;
            case '4':
                displayTheaterReservations();
                break;
            case '5':
                printf("Reserve Seats not implemented yet.\n");
                break;
            case '6':
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
