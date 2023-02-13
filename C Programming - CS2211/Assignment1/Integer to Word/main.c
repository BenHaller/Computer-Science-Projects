#include <stdio.h>

/* This program, 2211_integerToWord, serves the purpose of taking some user input of an integer from 1-999 and returning its English word representation.
 * This program continues to prompt the user until he/she desires to quit.
 * Written by Benjamin Haller, student number 251 103 362
 */

int main() {

    /* Here, the word representations for different integer numbers are given in string arrays to make conversion easier later on in the program. */
    char *one_digit_words[10] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    char *two_digit_words[10] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    char *multiples_of_ten[8] = {"twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

    int user_input;

    while(true) {

        printf("\nPlease enter a value (1-999, 0 to quit): ");
        scanf(" %d", &user_input); /* Here, the user integer input is taken */

        int length;


        if (user_input != 0) { /* Here, the number of digits in the user inputted integer is calculated to be used later */

            int test_num = user_input;
            length = 0;

            do {
                length++;
                test_num /= 10;
            } while(test_num != 0);

        }
        else exit(0); /* System exits if user input is 0 */

        if (length == 1) printf("\nYou entered the number %s", one_digit_words[user_input]); /* If user enters single-digit number then its English word is pulled from the array */

        else if (length == 2) { /* Multiple cases are created in the case that the user enters a two-digit number */

            if (10 <= user_input && user_input <= 19) printf("\nYou entered the number %s", two_digit_words[user_input - 10]); /* English representation is pulled from array in special cases */

            else {

                int tens_digit = user_input / 10;
                int ones_digit = user_input % 10;

                printf("\nYou entered the number %s", multiples_of_ten[tens_digit - 2]); /* Tens digit first printed */
                if (ones_digit != 0) printf("-%s", one_digit_words[ones_digit]); /* If ones digit is not 0 then it is printed */
            }
        }

        else if (length == 3) { /* Many cases accounted for if user enters three-digit number */

            int last_two_digits = user_input % 100;

            int hundreds_digit = user_input / 100;
            int tens_digit = last_two_digits / 10;
            int ones_digit = last_two_digits % 10;

            printf("\nYou entered the number %s hundred", one_digit_words[hundreds_digit]); /* Hundreds digit first printed */

            if (tens_digit != 0 || ones_digit != 0) {
                printf(" and "); /* If input is not a multiple of 100 'and' is printed to account for tens and/or ones section of number */

                if (10 <= last_two_digits && last_two_digits <= 19) printf("%s", two_digit_words[last_two_digits - 10]); /* Last two digits pulled from array in special cases */
                else {
                    if (tens_digit != 0 && ones_digit != 0) printf("%s-%s", multiples_of_ten[tens_digit - 2], one_digit_words[ones_digit]);
                    else if (tens_digit != 0) printf("%s", multiples_of_ten[tens_digit - 2]); /* Tens digit printed if it is not zero */
                    else if (ones_digit != 0) printf("%s", one_digit_words[ones_digit]); /* Ones digit printed if it is not zero */
                }
            }
        }
    }
}
