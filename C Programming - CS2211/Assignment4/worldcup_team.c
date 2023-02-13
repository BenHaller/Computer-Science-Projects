#pragma clang diagnostic push // Prevents warnings
#pragma ide diagnostic ignored "cert-err34-c"
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "worldcup_team.h"

/* This file outlines the entirety of the teams database for this program.
 * This file contains functions to insert, search, update, print or remove a team from the database.
 * The teams database in this assignment is created through means of a linked list. */

#define MAX_NAME_LENGTH 24 // Defines the max number of characters allowed in a team

// This is the structure of a team in the database.
struct team {
    int team_code; // The team's code, must be unique
    char team_name[MAX_NAME_LENGTH + 1]; // The name of the team, must be unique
    char seed_letter; // The letter portion of a team's seeding
    char seed_number; // The number portion of a team's seeding
    // No two teams can have the same combination of seed letter and number
    char uniform_colour; // The team's primary uniform colour
    struct team *next; // A pointer to the next team in the linked list
};

struct team *teams_list = NULL; // Points to the first team

/* The team_commands function is called upon by the main function in worldCupDB.c when the user selects the t command.
 * This function allows the user to call upon the functions provided to manipulate the teams database.
 * After a command is completed (i.e. a command function returns), this function returns to the main one. */
void team_commands(void) {
    char code;

    printf("------------------------------------------------------------------\n");
    printf("-  You are now working with the teams portion of this database.  -\n");
    printf("------------------------------------------------------------------\n");
    printf("Enter the operation code you would like to perform: ");
    scanf(" %c", &code);
    switch (code) {
        case 'i':
            insert();
            return;
        case 's':
            search();
            return;
        case 'u':
            update();
            return;
        case 'p':
            print();
            return;
        case 'd':
            delete();
            return;
        default:
            printf("Illegal code.\n");
            return;
    }
}

/* The find_team function is a helper method used in multiple methods below.
 * This function takes a parameter 'number', and searches for that number in the list of team_codes.
 * If a team code is found matching the number then the pointer to that team is returned.
 * Otherwise, the function returns null. */
struct team *find_team(int number) {
    struct team *p;

    for (p = teams_list; p != NULL && number >= p->team_code; p = p->next) { // Iterate through teams in linked list
        if (p != NULL && number == p->team_code) { // If current team's code equals number
            return p; // Return a pointer to the team
        }
    }

    return NULL; // If no team with the number is found, return NULL
}

/* The read_line function is created to take user input in a way that is more suitable to this program.
 * This function skips leading white-space characters, then begins to read in from user input.
 * The read_line function stores the first n characters in 'str',
 * then inserts the null character to truncate the string.
 * This implementation of the read_line function essentially discards of
 * any characters beyond the length n, preventing carry-over to later user input. */
void read_line(char str[], int n) {
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

/* The letter_to_colour function is used within both the search and print functions shown below.
 * This function takes in a character parameter representing a team's uniform_colour.
 * The function then searches the 'letters' array for a character that matches the input one,
 * and sets the index at which a match occurred to 'i'.
 * Then, the function returns the string at index i of the 'colours' array, in order for the
 * search/print function to output the full colour name rather than abbreviation. */
const char* letter_to_colour(char let) {
    char letters[] = {'R', 'O', 'Y', 'G', 'B', 'I', 'V'};
    char* colours[] = {"Red", "Orange", "Yellow", "Green", "Blue", "Indigo", "Violet"};
    int length = 7;

    for (int i = 0; i < length; i++) {
        if (let == letters[i]) {
            return colours[i];
        }
    }

    return "Invalid";
    // Return value indicates that the colour code was invalid if it does not
    // match anything in the array
}

/* The insert function is called upon when the user selects the operation code 'i'.
 * This function attempts to insert a new team into the database */
void insert(void) {
    struct team *curr, *prev, *new_node;

    new_node = malloc(sizeof(struct team));
    if (new_node == NULL) { // This occurs when the program does not have enough memory remaining to allocate.
        // If this is the case, the database is at capacity.
        printf("Error: Cannot insert any more teams, database is full.\n");
        return;
    }

    printf("Enter the new team's code: ");
    scanf("%d", &new_node->team_code);

    for (curr = teams_list; curr != NULL && new_node->team_code >= curr->team_code; curr = curr->next) {
        if (curr != NULL && new_node->team_code == curr->team_code) {
            // If this is true, a matching team code to the new one was found.
            printf("Error: team code already exists.\n");
            free(new_node); // Whenever an error occurs the memory allocated to new_node is simply cleared.
            return;
        }
    }

    // If the above error does not occur, the new team code is valid and the program continues

    printf("Enter the new team's name: ");
    read_line(new_node->team_name, MAX_NAME_LENGTH);

    for (curr = teams_list; curr != NULL; curr = curr->next) {
        if (curr != NULL && (strcmp(new_node->team_name, curr->team_name) == 0)) {
            // If this is true there is already a team with the new team name
            printf("Error: team name already exists.\n");
            free(new_node);
            return;
        }
    }

    // If the above error does not occur, the new team name is valid and the program continues

    printf("Enter the new team's group seeding: ");
    scanf("%c%c", &new_node->seed_letter, &new_node->seed_number);
    getchar();

    // This if statement checks if the value of the team seeding is within the A-H and 1-4 range.
    if (new_node->seed_letter < 'A' || new_node->seed_letter > 'H'
            || (int)new_node->seed_number - '0' > 4 || (int)new_node->seed_number - '0' < 1) {
        // Checks if either new team's group or seeding is outside the acceptable range.
        printf("Error: entered group seeding is outside of the acceptable range.\n");
        free(new_node);
        return;
    }

    for (curr = teams_list; curr != NULL; curr = curr->next) {
        if (curr != NULL && new_node->seed_letter == curr->seed_letter && new_node->seed_number == curr->seed_number) {
            // Error thrown if a team already exists with that seeding.
            printf("Error: team group seeding already exists.\n");
            free(new_node);
            return;
        }
    }

    // If neither of the above errors occur, the new team group seeding is valid and the program continues

    printf("Enter the new team's primary uniform colour: ");
    scanf("%c", &new_node->uniform_colour);
    getchar();

    if (NULL == strchr("ROYGBIV", new_node->uniform_colour)) { // If the uniform colour character is not in this string,
        printf("Error: entered uniform colour is not one of the accepted values.\n"); // It is not acceptable.
        free(new_node);
        return;
    }

    // If this error does not occur, all input for new_node is valid

    // Now, we insert the new node into its correct spot in the list of teams
    curr = teams_list;
    prev = NULL;
    // Iterates until we are at the right spot in the linked list
    while (curr != NULL && new_node->team_code > curr->team_code) {
        prev = curr;
        curr = curr->next;
    }

    new_node->next = curr;
    if (prev == NULL) { // If the new node is to go into the first spot in the list
        teams_list = new_node;
    }
    else {
        prev->next = new_node;
    }

    printf("Team successfully inserted! \nReturning to main menu.\n");
}


/* The search function is called upon when the user selects the operation code 's'.
 * This function searches the database for a team with the inserted team code.
 * If one is found, the function displays the team attributes. */
void search(void) {
    int number;
    struct team *p;

    printf("Enter the team code for which you'd like to search: ");
    scanf("%d", &number);
    p = find_team(number);
    if (p != NULL) {
        // The strings below are formatted to print in columns.
        printf("Team Code  Team Name                 ");
        printf("Group Seeding  Primary Kit Colour\n");
        printf("%-11d%-26s%c%-14c%-18s\n", p->team_code, p->team_name, p->seed_letter, p->seed_number, letter_to_colour(p->uniform_colour));
    }
    else {
        printf("Error: no team exists with that team code.\n");
    }
}


/* The update function is called upon when the user selects the operation code 'u'.
 * This function searches the database for a team with the inserted team code.
 * Then, it allows the user to update the team's other attributes.
 * The code here is very similar to that of the insert function and thus some comments are left out. */
void update(void) {
    int number;
    struct team *curr, *p;


    printf("Enter the team code of the team that you would like to update: ");
    scanf("%d", &number);
    p = find_team(number);
    if (p != NULL) {
        /* In this function, the node values are not changed until all input is proven valid.
         * This is to ensure that one attribute is not changed prior to seeing that the update is invalid,
         * leaving a partially updated node. */

        char input_name[MAX_NAME_LENGTH + 1];

        printf("Enter the team's updated name: ");
        read_line(input_name, MAX_NAME_LENGTH);

        for (curr = teams_list; curr != NULL; curr = curr->next) {
            if (curr != NULL && (strcmp(input_name, curr->team_name) == 0)) {
                printf("Error: team name already exists.\n");
                return;
            }
        }

        // If the above error doesn't occur, the new name is valid and the program continues

        char input_letter, input_number;

        printf("Enter the team's updated group seeding: ");
        scanf("%c%c", &input_letter, &input_number);
        getchar();

        if (input_letter < 'A' || input_letter > 'H' || (int)input_number - '0' > 4 || (int)input_number - '0' < 1) {
            printf("Error: entered group seeding is invalid; either seeding letter or number is outside of acceptable range.\n");
            return;
        }

        for (curr = teams_list; curr != NULL; curr = curr->next) {
            if (curr != NULL && input_letter == curr->seed_letter && input_number == curr->seed_number) {
                printf("Error: team group seeding already exists.\n");
                return;
            }
        }

        // If the above errors do not occur, the new seeding is valid and the program continues

        char input_colour;

        printf("Enter the team's updated primary uniform colour: ");
        scanf("%c", &input_colour);
        getchar();

        if (NULL == strchr("ROYGBIV", input_colour)) {
            printf("Error: entered uniform colour is not one of the acceptable values.\n");
            return;
        }

        /* If all of the above operations are performed without any errors occurring,
         * the team updates are all valid.
         * Now, the values of the team to be updated can all be adjusted.
         * At this point, we know we will not run into any more errors. */

        strcpy(p->team_name, input_name);
        p->seed_letter = input_letter;
        p->seed_number = input_number;
        p->uniform_colour = input_colour;

        // Now the team's values are updated in the system.
    }
    else {
        printf("Error: no team exists with that team code.\n");
    }
}

/* The print function is called upon when the user selects the operation code 'p'.
 * This function is similar to the search function shown above, but instead prints all the teams and their attributes.
 * The teams are printed in the order of player codes, from top to bottom. */
void print(void) {
    struct team *p;

    printf("Team Code  Team Name                 "); // Formatting strings to display vertical columns.
    printf("Group Seeding  Primary Kit Colour\n");

    for (p = teams_list; p != NULL; p = p->next) { // This loop iterates for each team in the teams array.
        printf("%-11d%-26s%c%-14c%-18s\n", p->team_code, p->team_name, p->seed_letter, p->seed_number, letter_to_colour(p->uniform_colour));
        // Each team has its attributes printed inline with the attribute name columns.
    }
}


/* The delete function is called upon when the user selects the operation code 'd'.
 * This function removes the team with the given team code from the linked list, deleting it from the database. */
void delete(void) {
    int number;
    struct team *curr, *prev, *p;


    printf("Enter the team code of the team that you would like to delete: ");
    scanf("%d", &number);
    p = find_team(number);
    if (p != NULL) {
        // The following for loop iterates until the 'curr' node is the node which we want to delete.
        for (curr = teams_list, prev = NULL; curr != NULL && curr->team_code != number; prev = curr, curr = curr->next);
        if (prev == NULL) { // If the node is the first in the list,
            teams_list = teams_list->next; // Simply make the teams_list pointer point to the next node in the list (or NULL)
        }
        else { // If the node is not the first,
            prev->next = curr->next; // Make the previous node point to the next one.
        }
        free(curr); // Clear the memory allocated to the now removed node.
    }
    else {
        printf("Error: no team exists with that team code.\n");
    }
}

#pragma clang diagnostic pop // Prevents warnings