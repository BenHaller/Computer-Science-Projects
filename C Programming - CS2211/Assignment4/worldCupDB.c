#include <stdio.h>
#include "worldCupDB.h"

/* This file essentially serves as the user interface, taking user commands from the start of the program.
 * Here, number of commands are outlined, allowing the user to transition to either the team or player databases.
 * This file also allows the user to quit, and allows the user to see a help menu explaining the
 * functionality of the overall program. */

/* This is the main function, which loops until the user quits using the q command.
 * All other functions eventually return to this one, in the worldCupDB.c file
 * as well as the worldcup_team.c and worldcup_player.c files. */
int main() {
    char code;

    printf("------------------------------------------------------------------\n");
    printf("-      Welcome to the 2211 World Cup Database Version 2.0!       -\n");
    printf("------------------------------------------------------------------\n");

    while (1) {

        printf("Enter the command which you would like to perform: ");
        scanf(" %c", &code);
        switch (code) {
            case 'h':
                help_menu();
                break;
            case 'q':
                return 0;
            case 't':
                team_commands();
                break;
            case 'p':
                player_commands();
                break;
            default:
                printf("Invalid code.\n");
        }
    }
}

/* This is a helper function to print a basic message explaining some functionality of this program.
 * This function is called from the main function when the user executes the h command. */
void help_menu() {
    printf("-------------------------------------------------------------------\n");
    printf("- This program functions as a database for both teams and players -\n");
    printf("- participating in the 2211 World Cup.                            -\n");
    printf("-------------------------------------------------------------------\n");
    printf("- The 'q' function quits the program, losing all data.            -\n");
    printf("- The 't' function allows control of the teams database.          -\n");
    printf("- The 'p' function allows control of the players database.        -\n");
    printf("-------------------------------------------------------------------\n");
}
