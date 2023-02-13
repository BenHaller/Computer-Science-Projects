#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "worldcup_player.h"

/* This file outlines the entirety of the players database for this program.
 * This file contains functions to insert, search, update, print or remove a player from the database.
 * The players database in this assignment is created through means of a linked list. */

#define MAX_PLAYER_NAME_LENGTH 49 // Defines the max number of characters allowed in a player name
#define MAX_CLUB_AFFIL_LENGTH 49 // Defines the max number of characters allowed in a club affiliation name

// This is the structure of a player in the database.
struct player {
    int player_code; // The player code, must be unique
    char player_name[MAX_PLAYER_NAME_LENGTH + 1]; // The player's name
    int player_age; // The player's age
    char club_affil[MAX_CLUB_AFFIL_LENGTH + 1]; // The player's club affiliation
    struct player *next; // A pointer to the next player in the linked list
};

struct player *players_list = NULL; // Points to the first player

/* The player_commands function is called upon by the main function in worldCupDB.c when the user selects the p command.
 * This function allows the user to call upon the functions provided to manipulate the players database.
 * After a command is completed (i.e. a command function returns), this function returns to the main one. */
void player_commands(void) {
    char code;

    printf("------------------------------------------------------------------\n");
    printf("- You are now working with the players portion of this database. -\n");
    printf("------------------------------------------------------------------\n");
    printf("Enter the operation code you would like to perform: ");
    scanf(" %c", &code);
    switch (code) {
        case 'i':
            p_insert();
            return;
        case 's':
            p_search();
            return;
        case 'u':
            p_update();
            return;
        case 'p':
            p_print();
            return;
        case 'd':
            p_delete();
            return;
        default:
            printf("Illegal code.\n");
            return;
    }
}

/* The find_player function is a helper method used in multiple methods below.
 * This function takes a parameter 'number', and searches for that number in the list of player_codes.
 * If a player code is found matching the number then the pointer to that player is returned.
 * Otherwise, the function returns null. */
struct player *find_player(int number) {
    struct player *p;

    for (p = players_list; p != NULL && number >= p->player_code; p = p->next) {
        // Iterate through the players in the linked list
        if (p != NULL && number == p->player_code) { // If current player's code equals number
            return p; // Return a pointer to the player
        }
    }

    return NULL; // If no player with the number is found, return NULL
}

/* The p_read_line function is created to take user input in a way that is more suitable to this program.
 * This function skips leading white-space characters, then begins to read in from user input.
 * The p_read_line function stores the first n characters in 'str', inserts null character to truncate the string.
 * This implementation of the p_read_line function essentially discards of
 * any characters beyond the length n, preventing carry-over to later user input. */
void p_read_line(char str[], int n) {
    int ch, i = 0;

    while(isspace(ch = getchar())) // Skip past white-space
        ;
    while (ch != '\n' && ch != EOF) {
        if (i < n)
            str[i++] = ch;
        ch = getchar();
    }
    str[i] = '\0'; // Terminate with null character
}

/* The insert function is called upon when the user selects the operation code 'i'.
 * This function attempts to insert a new player into the database */
void p_insert(void) {
    struct player *curr, *prev, *new_node;

    new_node = malloc(sizeof(struct player));
    if (new_node == NULL) { // This occurs when the program does not have enough memory remaining to allocate.
        // If this is the case, the database is at capacity.
        printf("Error: Cannot insert any more players, database is full.\n");
        return;
    }

    printf("Enter the new player's code: ");
    scanf("%d", &new_node->player_code);

    for (curr = players_list; curr != NULL && new_node->player_code >= curr->player_code; curr = curr->next) {
        if (curr != NULL && new_node->player_code == curr->player_code) {
            // If this is true, a matching player code to the new one was found.
            printf("Error: player code already exists.\n");
            free(new_node);
            return;
        }
    }

    // If the above error does not occur, the new player code is valid and the program continues

    printf("Enter the new player's name: ");
    p_read_line(new_node->player_name, MAX_PLAYER_NAME_LENGTH);

    // The new player name is stored, and the program continues

    printf("Enter the new player's age: ");
    scanf("%d", &new_node->player_age);
    getchar();

    if (new_node->player_age < 17 || new_node->player_age > 99) {
        // Checks if either new player's age is outside the acceptable range.
        printf("Error: entered player age is outside of the acceptable range.\n");
        free(new_node);
        return;
    }

    // If the above error does not occur, the new player age is valid and the program continues

    printf("Enter the new player's club affiliation: ");
    p_read_line(new_node->club_affil, MAX_CLUB_AFFIL_LENGTH);

    // Now all input for new_node is taken and verified for validity.

    // Now, we insert the new node into its correct spot in the list of players.
    curr = players_list;
    prev = NULL;
    while (curr != NULL && new_node->player_code > curr->player_code) {
        prev = curr;
        curr = curr->next;
    }

    new_node->next = curr;
    if (prev == NULL) {
        players_list = new_node;
    }
    else {
        prev->next = new_node;
    }

    printf("Player successfully inserted! \nReturning to main menu.\n");
}

/* The p_search function is called upon when the user selects the operation code 's'.
 * This function searches the database for a player with the inserted team code.
 * If one is found, the function displays the player attributes. */
void p_search(void) {
    int number;
    struct player *p;

    printf("Enter the player code for which you'd like to search: ");
    scanf("%d", &number);
    p = find_player(number);
    if (p != NULL) {
        // The strings below are formatted to print in columns.
        printf("Player Code  Player Name                                        ");
        printf("Player Age  Club Affiliation\n");
        printf("%-13d%-51s%-12d%-18s\n", p->player_code, p->player_name, p->player_age, p->club_affil);
    }
    else {
        printf("Error: no player exists with that player code.\n");
    }
}

/* The p_update function is called upon when the user selects the operation code 'u'.
 * This function searches the database for a player with the inserted team code.
 * Then, it allows the user to update the player's other attributes.
 * The code here is very similar to that of the p_insert function and thus some comments are left out. */
void p_update(void) {
    int number;
    struct player *p;


    printf("Enter the player code of the player that you would like to update: ");
    scanf("%d", &number);
    p = find_player(number);
    if (p != NULL) {
        /* In this function, the updated values are not taken right away.
         * Instead, all player values are changed to the updated ones at once at the end of the function.
         * This ensures that all input is valid and ensures that no changes are made
         * before realizing the update is invalid. */

        char input_name[MAX_PLAYER_NAME_LENGTH + 1];

        printf("Enter the player's updated name: ");
        p_read_line(input_name, MAX_PLAYER_NAME_LENGTH);

        // Now, the new player name is recorded and the program continues

        int input_age;

        printf("Enter the new player's age: ");
        scanf("%d", &input_age);
        getchar();

        if (input_age < 17 || input_age > 99) { // Checks that the updated age is within the acceptable range.
            printf("Error: entered player age is outside of the acceptable range.\n");
            return;
        }

        // If the above error does not occur, the new player age is valid and the program continues

        char input_affil[MAX_CLUB_AFFIL_LENGTH + 1];

        printf("Enter the new player's club affiliation: ");
        p_read_line(input_affil, MAX_CLUB_AFFIL_LENGTH);

        strcpy(p->player_name, input_name);
        p->player_age = input_age;
        strcpy(p->club_affil, input_affil);
        // Now the player's values are updated in the system.
    }
    else {
        printf("Error: no player exists with that player code.\n");
    }
}

/* The p_print function is called upon when the user selects the operation code 'p'.
 * This function is similar to the p_search function shown above,
 * but instead prints all the players and their attributes.
 * The players are printed in order of their player codes, from top to bottom. */
void p_print(void) {
    struct player *p;

    // Formatting strings, ensure vertical columns.
    printf("Player Code  Player Name                                        ");
    printf("Player Age  Club Affiliation\n");

    for (p = players_list; p != NULL; p = p->next) { // This loop iterates for each player in the players array.
        printf("%-13d%-51s%-12d%-18s\n", p->player_code, p->player_name, p->player_age, p->club_affil);
    }
}

/* The delete function is called upon when the user selects the operation code 'd'.
 * This function removes the team with the given team code from the linked list, deleting it from the database. */
void p_delete(void) {
    int number;
    struct player *curr, *prev, *p;


    printf("Enter the player code of the player that you would like to delete: ");
    scanf("%d", &number);
    p = find_player(number);
    if (p != NULL) {
        // The following for loop iterates until the 'curr' node is the node which we want to delete.
        for (curr = players_list, prev = NULL; curr != NULL && curr->player_code != number; prev = curr, curr = curr->next);
        if (prev == NULL) { // If the node is the first in the list,
            players_list = players_list->next; // Simply make the teams_list pointer point to the next node in the list (or NULL)
        }
        else { // If the node is not the first,
            prev->next = curr->next; // Make the previous node point to the next one.
        }
        free(curr); // Clear the memory allocated for the now removed node.
    }
    else {
        printf("Error: no player exists with that player code.\n");
    }
}
#pragma clang diagnostic pop