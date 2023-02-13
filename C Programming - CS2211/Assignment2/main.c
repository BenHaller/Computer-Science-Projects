#include <stdio.h>

/* This program takes an array ranging in size from 5 to 12 integers from the user.
 * This program contains a number of functions that display the elements of the inputted array in varying orders, depending on the function performed.
 * Being that all operations are embedded within functions, the initial array remains unchanged throughout the program.
 * Written by Benjamin Haller, student number 251 103 362
 */

void elem_and_position(int integer_array[], int num_integers) { /* This prints out the elements of the array and their respective positions */

    printf("\nElements of array and which position they are in:\n");

    for (int i = 0; i < num_integers; i++) {
        printf("index %d: ", i + 1);
        printf("%d ", integer_array[i]);
    }

    printf("\n");
}

void largest_value(int integer_array[], int num_integers) { /* This prints out the largest value in the array */

    printf("\nLargest value in the array:\n");

    int max = integer_array[0];
    for (int i = 1; i < num_integers; i++) {
        if (integer_array[i] > max) max = integer_array[i];
    }

    printf("%d", max);
    printf("\n");
}

void reverse_order(int integer_array[], int num_integers) { /* This prints out the array's values in reverse order */

    printf("\nElements of the array in reverse order:\n");

    for (int i = num_integers - 1; i >= 0; i--) {
        printf("%d ", integer_array[i]);
    }

    printf("\n");
}

void sum_of_values(int integer_array[], int num_integers) { /* This prints out the sum of all the array's values */

    printf("\nSum of all values in the array:\n");

    int sum = 0;
    for (int i = 0; i < num_integers; i++) {
        sum += integer_array[i];
    }

    printf("%d", sum);
    printf("\n");
}

void descending_order(int integer_array[], int num_integers) { /* This prints out the array elements in descending order */

    printf("\nElements of the array from largest to smallest (descending order):\n");

    int temp = 0;
    int temp_array[num_integers];

    for (int i = 0; i < num_integers; i++) {
        temp_array[i] = integer_array[i];
    }

    for (int i = 0; i < num_integers; i++) {
        for (int j = i + 1; j < num_integers; j++) {
            if(temp_array[i] < temp_array[j]) {
                temp = temp_array[i];
                temp_array[i] = temp_array[j];
                temp_array[j] = temp;
            }
        }
    }

    for (int i = 0; i < num_integers; i++) {

        printf("%d ", temp_array[i]);
    }

    printf("\n");
}

void elements_swapped(int integer_array[], int num_integers) { /* This prints out the array elements but with the first and last swapped */

    printf("\nElements of the array except the first and last element are swapped:\n");

    printf("%d ", integer_array[num_integers - 1]);

    for (int i = 1; i < num_integers - 1; i++) {
        printf("%d ", integer_array[i]);
    }

    printf("%d", integer_array[0]);

    printf("\n");

}

int main() {

    int num_integers;

    printf("How many integers would you like to input (between 5 and 12): "); /* Here the program asks how many elements they would like the array to have */
    scanf(" %d", &num_integers);

    int integer_array[num_integers];

    printf("The size of your integer array is %d bytes.\n", sizeof(integer_array)); /* Using the sizeof command, the program shows the user how many bytes are allocated to the array */

    while (1) {
        printf("Enter your list of integers, each separated by a space: "); /* Here, the user input array is taken */
        for (int i = 0; i < num_integers; i++) {
            scanf(" %d", &integer_array[i]);
        }

        if (integer_array[num_integers - 1] != NULL) break;
    }

    for (int i = 0; i < num_integers; i++) {
        printf(" %d", integer_array[i]);
    }
    printf("\n");

    elem_and_position(integer_array, num_integers);

    largest_value(integer_array, num_integers);

    reverse_order(integer_array, num_integers);

    sum_of_values(integer_array, num_integers);

    descending_order(integer_array, num_integers);

    elements_swapped(integer_array, num_integers);
}

