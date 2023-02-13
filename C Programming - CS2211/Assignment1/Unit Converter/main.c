#include <stdio.h>

/* This program, 2211_unitConverter, serves the purpose of taking some user input in terms of one unit of measurement (n number of Gallons, x number of Hectares, etc.) and converts it to another form of measurement, returning that value to the user.
 * This program continues to prompt the user until he/she desires to quit.
 * Written by Benjamin Haller, student number 251 103 362
 */

int main() {

    float conversions[8] = {2.20462, 0.453593, 2.47105, 0.404686, 0.264172, 3.78541, 0.621371, 1.60934}; /* These define the conversion constants used to convert between units */
    int user_input, conversion_index; /* These are variables that change depending on user input */
    char conversion_character;

    while(true) {

        printf("Welcome to the unit conversion machine!\n----------\nPlease select an input:\n");
        printf("Enter 1 for conversion between Kilograms and Pounds.\n");
        printf("Enter 2 for conversion between Hectares and Acres.\n");
        printf("Enter 3 for conversion between Litres and Gallons.\n");
        printf("Enter 4 for conversion between Kilometres and Miles.\n");
        printf("Enter 5 to quit.\n");

        scanf("%d", &user_input);

        /* The statements at this indentation level represent the different user input cases; 1 to convert between Kg and lbs, 2 to convert between Hectares and Acres, etc. */
        if (user_input == 1) {
            bool i = true;
            while (i) {

                printf("You have selected conversion between Kilograms and Pounds.\n");
                printf("Enter K for conversion from Kilograms to Pounds.\n");
                printf("Enter P for conversion from Pounds to Kilograms.\n");
                scanf(" %c",
                      &conversion_character); /* the blank space prior to %c here allows the program to handle any leading space, tab or end of line character(s) */

                /* The statements at this indentation level represent the individual conversion cases; Kg to lbs, lbs to Kg, etc. */
                if (conversion_character == 'K') {
                    conversion_index = 0;
                    i = false;
                } else if (conversion_character == 'P') {
                    conversion_index = 1;
                    i = false;
                }
            }
        } else if (user_input == 2) {
            bool i = true;
            while (i) {

                printf("You have selected conversion between Hectares and Acres.\n");
                printf("Enter H for conversion from Hectares to Acres.\n");
                printf("Enter A for conversion from Acres to Hectares.\n");
                scanf(" %c", &conversion_character);

                if (conversion_character == 'H') {
                    conversion_index = 2;
                    i = false;
                } else if (conversion_character == 'A') {
                    conversion_index = 3;
                    i = false;
                }
            }
        } else if (user_input == 3) {
            bool i = true;
            while (i) {

                printf("You have selected conversion between Litres and Gallons.\n");
                printf("Enter L for conversion from Litres to Gallons.\n");
                printf("Enter G for conversion from Gallons to Litres.\n");
                scanf(" %c", &conversion_character);

                if (conversion_character == 'L') {
                    conversion_index = 4;
                    i = false;
                } else if (conversion_character == 'G') {
                    conversion_index = 5;
                    i = false;
                }
            }
        } else if (user_input == 4) {
            bool i = true;
            while (i) {

                printf("You have selected conversion between Kilometres and Miles.\n");
                printf("Enter K for conversion from Kilometres to Miles.\n");
                printf("Enter M for conversion from Miles to Kilometres.\n");
                scanf(" %c", &conversion_character);

                if (conversion_character == 'K') {
                    conversion_index = 6;
                    i = false;
                } else if (conversion_character == 'M') {
                    conversion_index = 7;
                    i = false;
                }
            }
        } else if (user_input == 5) exit(0); /* If user enters 5 the program exits with code 0 */

        if (1 <= user_input &&
            user_input <= 4) { /* If user input is between 1 and 4, the conversion calculation will occur */

            float user_value, result_value;

            printf("Please enter a value: ");
            scanf(" %f", &user_value);

            result_value = user_value *
                           conversions[conversion_index]; /* Resulting converted value is calculated based on conversion rate index in array */

            /* These nested print statements handle all possible conversion cases without dealing with string arrays for units (Kilograms, Pounds, Hectares, etc.) */
            if (conversion_index == 0)
                printf("Your conversion is %.5f Kilograms to %.5f Pounds.\n\n", user_value, result_value);
            else if (conversion_index == 1)
                printf("Your conversion is %.5f Pounds to %.5f Kilograms.\n\n", user_value, result_value);
            else if (conversion_index == 2)
                printf("Your conversion is %.5f Hectares to %.5f Acres.\n\n", user_value, result_value);
            else if (conversion_index == 3)
                printf("Your conversion is %.5f Acres to %.5f Hectares.\n\n", user_value, result_value);
            else if (conversion_index == 4)
                printf("Your conversion is %.5f Litres to %.5f Gallons.\n\n", user_value, result_value);
            else if (conversion_index == 5)
                printf("Your conversion is %.5f Gallons to %.5f Litres.\n\n", user_value, result_value);
            else if (conversion_index == 6)
                printf("Your conversion is %.5f Kilometres to %.5f Miles.\n\n", user_value, result_value);
            else if (conversion_index == 7)
                printf("Your conversion is %.5f Miles to %.5f Kilometres.\n\n", user_value, result_value);
        }
    }

}
