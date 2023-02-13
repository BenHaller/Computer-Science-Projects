#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_NUM_TEAMS 32
#define MAX_NAME_LENGTH 24

int num_teams = 0;

// Function prototypes, prevent main method from throwing errors
int find_team(int number);
void read_line(char str[], int n);
int search_names(char new_name[]);
int search_seeds(char new_letter, char new_number);
const char* letter_to_colour(char let);
void insert(void);
void search(void);
void update(void);
void print(void);

/* This is the basic structure of a team
 * team_code is an integer representing a team's Team Code
 * team_name is a character array of max  length 25 (or 24 characters plus /0), representing a team's Team Name
 * seed_letter is a character representing the group (letter) component of a team's Group Seeding
 * seed_number is an integer representing the seeding (number) component of a team's Group Seeding
 * uniform_colour is a character representing a team's Primary kit Colour */
struct team {
    int team_code;
    char team_name[MAX_NAME_LENGTH + 1];
    char seed_letter;
    int seed_number;
    char uniform_colour;
} teams[MAX_NUM_TEAMS];

int main() {
    char code;

    printf("-------------------------------------------\n"); // Prints when the program is first run
    printf("- Welcome to the 2211 World Cup Database! -\n");
    printf("-------------------------------------------\n\n");

    while (1) {
        /* This is the base program loop: whenever the program returns here the user is asked to insert another operation-code
         * until the user enters code 'q', at which time the program exits */
        printf("Enter the operation code you would like to perform: ");
        scanf(" %c", &code);
        switch (code) {
            case 'i':
                insert();
                break;
            case 's':
                search();
                break;
            case 'u':
                update();
                break;
            case 'p':
                print();
                break;
            case 'q':
                return 0;
            default:
                printf("Illegal code\n"); // If none of the above codes are entered the loop reiterates
        }
        printf("\n");
    }
}

/* The find_team function is a helper method used in multiple methods below.
 * This function takes a parameter 'number', and searches for that number in the list of team_codes.
 * If a team code is found matching the number then the index of that code in the teams array is returned.
 * Otherwise, the function returns -1. */
int find_team(int number) {
    int i;

    for (i = 0; i < num_teams; i++) {
        if (teams[i].team_code == number) {
            return i;
        }
    }
    return -1;
}

/* The read_line function is created to take user input in a way that is more suitable to this program.
 * This function skips leading white-space characters, then begins to read in from user input.
 * The read_line function stores the first n characters in 'str', then inserts the null character to truncate the string.
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

/* The search_names function is a helper function used to verify the validity of new team names.
 * This function takes in a character array 'new_name', and searches the existing list of Team Names.
 * If an existing Team Name is found matching the provided new_name string, this function returns 1.
 * Else, it returns 0. */
int search_names(char new_name[]) {

    for (int i = 0; i < num_teams; i++) {
        if (strcmp(new_name, teams[i].team_name) == 0) {
            return 1;
        }
    }

    return 0;
}

/* The search_seeds function is a helper function used to verify the validity of new team group seeding.
 * This function takes in two characters; new_letter and new_number.
 * These characters represent a new team's group and seed, respectively.
 * The function then searches the existing group seeding, returning 1 if a match is found.
 * If a match is not found, the function returns 0. */
int search_seeds(char new_letter, char new_number) {

    for (int i = 0; i < num_teams; i++) {
        if ((new_letter == teams[i].seed_letter) && ((int)new_number == teams[i].seed_number)) { // new_number is cast to type int in order to compare it with the int type seed_number
            return 1;
        }
    }

    return 0;
}

/* The letter_to_colour function is used within both the search and print functions shown below.
 * This function takes in a character parameter representing a team's uniform_colour.
 * The function then searches the 'letters' array for a character that matches the input one, and sets the index at which a match occurred to 'i'.
 * Then, the function returns the string at index i of the 'colours' array, in order for the search/print function to output the full colour name rather than abbreviation. */
const char* letter_to_colour(char let) {
    char letters[] = {'R', 'O', 'Y', 'G', 'B', 'I', 'V'};
    char* colours[] = {"Red", "Orange", "Yellow", "Green", "Blue", "Indigo", "Violet"};
    int length = 7;

    for (int i = 0; i < length; i++) {
        if (let == letters[i]) {
            return colours[i];
        }
    }
}

/* The insert function is called upon when the user selects the operation code 'i'.
 * This function attempts to insert a new team into the database */
void insert(void) {

    if (num_teams == MAX_NUM_TEAMS) { // If this is true then the database is full, as the max number of teams is already stored.
        printf("Error: cannot add another team, database is already full.\n");
        return; // Every time an error occurs within a function, the function simply returns to the main method and the user is prompted to enter a new operation code.
    }
    int new_team_code; // Stores the new team code

    printf("Enter the new team's code: "); // User is prompted to enter a new team code.
    scanf("%d", &new_team_code); // Integer code value is stored within new_team_code.

    if (new_team_code < 0 || new_team_code > 31) { // Error thrown if the new team code is outside the acceptable range.
        printf("Error: entered code is outside of acceptable range (0-31).\n");
        return;
    }
    else if (find_team(new_team_code) >= 0) { // Error thrown if a team already exists with the new team code.
        printf("Error: team code already exists.\n");
        return;
    }
    /* If none of the above errors occur, the new team code is valid and the program continues on to prompt the user for the team name.
     * Note that the team code is not actually inserted yet.
     * Instead, all the new team's values are not inserted until the team code, name, group seeding and primary kit colour have been proven valid.
     * This prevents team attributes from being stored in the database for a team that is later proven invalid. */


    char input_name[MAX_NAME_LENGTH + 1]; // Stores the new team name

    printf("Enter the new team's name: "); // User is prompted to enter a new team name.
    read_line(input_name, MAX_NAME_LENGTH); // Now, the team's name is set to the first 24 characters inputted string.

    if (search_names(input_name) == 1) { // This, meaning that a team_name already exists that is the same string as the new team's name string.
        printf("Error: team name already exists.\n");
        return;
    }
    /* If the above error does not occur, the new team name is valid and the program continues on to prompt the user for the team's group seeding */


    char input_letter, input_number; // Store the new team's group and seeding, respectively.

    printf("Enter the new team's group seeding: "); // User is prompted to enter the new group seeding.
    scanf("%c%c", &input_letter, &input_number); // Group and seeding stored in two characters.
    getchar(); // Handles newline character

    if (input_letter < 'A' || input_letter > 'H' || (int)input_number - '0' > 4 || (int)input_number - '0' < 1) { // Checks if either new team's group or seeding is outside the acceptable range.
        printf("Error: entered group seeding is outside of the acceptable range.\n");
        return;
    }

    if (search_seeds(input_letter, input_number) == 1) { // This, meaning that a team already exists with the same group seeding of that trying to be entered.
        printf("Error: team group seeding already exists\n");
        return;
    }
    /* If neither of the above errors occur, the new team group seeding is valid and the program continues on. */


    char input_colour; // Stores the new team's primary uniform colour.

    printf("Enter the new team's primary uniform colour; "); // User is prompted to enter the new uniform colour.
    scanf("%c", &input_colour);
    getchar(); // Handles newline character

    if (NULL == strchr("ROYGBIV", input_colour)) { // This checks the value of the 'input_colour' character, and is equal to NULL if the character is not found within the string "ROYGBIV" (all acceptable values).
        printf("Error: entered uniform colour is not one of the acceptable values.\n");
        return;
    }

    /* If all of the above operations are performed without any error,
     * the new team is inserted into the teams database and the number of teams is increased. */
    strcpy(teams[num_teams].team_name, input_name); // strcpy function is used to copy the input_name string into the new team's team_name.
    teams[num_teams].seed_letter = input_letter;
    teams[num_teams].seed_number = input_number;
    teams[num_teams].team_code = new_team_code;
    teams[num_teams].uniform_colour = input_colour;
    num_teams++;

    // The new team is now successfully inserted.
}


/* The search function is called upon when the user selects the operation code 's'.
 * This function searches the database for a team with the inserted team code.
 * If one is found, the function displays the team attributes. */
void search(void) {
    int i, number;

    printf("Enter the team code for which you'd like to search: ");
    scanf("%d", &number);
    i = find_team(number); // Sets i to the team index in 'teams' if a match is found, otherwise i is set to -1.
    if (i >= 0) { // If a team exists with the provided code,
        // The next three printf statements are used to align the team attribute names and values in vertical columns.
        printf("Team Code  Team Name                 ");
        printf("Group Seeding  Primary Kit Colour\n");
        printf("%-11d%-26s%c%-14c%-18s\n", teams[i].team_code, teams[i].team_name, teams[i].seed_letter, teams[i].seed_number, letter_to_colour(teams[i].uniform_colour));
    }
    else { // If no team exists with the provided code,
        printf("Error: no team exists with that team code.\n");
    }
}


/* The update function is called upon when the user selects the operation code 'u'.
 * This function searches the database for a team with the inserted team code.
 * Then, it allows the user to update the team's other attributes. */
void update(void) {
    int i, number;

    // Shown in search function.
    printf("Enter the team code for which you'd like to update: ");
    scanf("%d", &number);
    i = find_team(number);
    if (i < 0) {
        printf("Error: no team exists with that team code.\n");
        return;
    }

    // If above error does not occur, prompt for updated team attributes.

    /* The remainder of the code in the update function is very similar to that used in the insert function.
     * Comments are provided in the insert function displaying the functionality of this code.
     * Where minor differences occur here, the reasoning for such is provided */
    char input_name[MAX_NAME_LENGTH + 1];

    printf("Enter the team's updated name: "); // User prompts now ask for updated values rather than new ones.
    read_line(input_name, MAX_NAME_LENGTH);

    if (search_names(input_name) == 1) {
        printf("Error: team name already exists.\n");
        return;
    }

    char input_letter, input_number;

    printf("Enter the team's updated group seeding: ");
    scanf("%c%c", &input_letter, &input_number);
    getchar(); // Handles newline character

    if (input_letter < 'A' || input_letter > 'H' || (int)input_number - '0' > 4 || (int)input_number - '0' < 1) {
        printf("Error: entered group seeding is invalid; either seeding letter or number is outside of acceptable range.\n");
        return;
    }

    if (search_seeds(input_letter, input_number) == 1) {
        printf("Error: team group seeding already exists\n");
        return;
    }

    char input_colour;

    printf("Enter the team's updated primary uniform colour; ");
    scanf("%c", &input_colour);
    getchar(); // Handles newline character

    if (NULL == strchr("ROYGBIV", input_colour)) {
        printf("Error: entered uniform colour is not one of the acceptable values.\n");
        return;
    }

    /* If all of the above operations are performed without any error,
     * the team updates are all valid.
     * Here, the values of teams[i] are updated, rather than a new team inserted at position teams[num_teams].
     * This is because the team to update is at position i in the array, as determined by the find_team function. */
    strcpy(teams[i].team_name, input_name);
    teams[i].seed_letter = input_letter;
    teams[i].seed_number = input_number;
    teams[i].uniform_colour = input_colour;

    /* The team values are now successfully updated. */
}

/* The print function is called upon when the user selects the operation code 'p'.
 * This function is similar to the search function shown above, but instead prints all the teams and their attributes.
 * The teams are printed in the order in which they were inserted, from top to bottom. */
void print(void) {

    printf("Team Code  Team Name                 "); // Formatting strings to display vertical columns.
    printf("Group Seeding  Primary Kit Colour\n");

    for (int i = 0; i < num_teams; i ++) { // This loop iterates for each team in the teams array.
        printf("%-11d%-26s%c%-14c%-18s\n", teams[i].team_code, teams[i].team_name, teams[i].seed_letter, teams[i].seed_number, letter_to_colour(teams[i].uniform_colour)); // Each team has its attributes printed inline with the attribute name columns.
    }
}