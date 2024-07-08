#include <stdio.h>

int main(void) {
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
      
      if ((int)option_no < 49 || (int)option_no > 53) {
        printf("\nInvalid Input!\n\n");
      } else if ((int)option_no == 53) {
        printf("\n######################################################################\n");
        printf("############################# Thank You! #############################\n");
        printf("######################################################################\n");
        exit = 1;
      }
    }
    
    return (0);
}
