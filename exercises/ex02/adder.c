#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define BUFFER_LEN 12
#define ARRAY_LEN 20

/**
 * Function to sum all integers in an array of integers
 * and return a value of type long.
 * @param integers
 * @param finalIndex
 * @return sum of integers
 */
long sum(int integers[], int finalIndex) {
    long result = 0;
    for (int i = 0; i < finalIndex; i++) {
        result += integers[i];
    }
    return result;
}

/**
 * Function to check whether user input exceeds the buffer
 * @param inputBuffer
 * @return 1 if true; otherwise 0
 */
int validInputLength(char inputBuffer[]) {
    if (inputBuffer[strlen(inputBuffer) - 1] != '\n') {
        int dropped = 0;

        // Drop other extra input characters if they exist
        while (fgetc(stdin) != '\n')
            dropped++;

        if (dropped > 0)
            return 0;
    }
    return 1;
}

/**
 * Function to check whether the input buffer is zero.
 * i.e. 0, 00, 000, etc.
 * @param inputBuffer
 * @return 1 if true; otherwise 0
 */
int isZero(char inputBuffer[]) {
    for (int i = 0; i < strlen(inputBuffer); i++) {
        if (inputBuffer[i] != '0' && inputBuffer[i] != '\n')
            return 0;
    }
    return 1;
}

/**
 * Function to check whether the input buffer a valid integer
 * If it's valid, then add the integer to the given integer array.
 * @param inputBuffer
 * @param integers
 * @param index
 * @return 1 if true; otherwise 0
 */
int parseInteger(char inputBuffer[], int integers[], int index) {
    int temp = atoi(inputBuffer);
    if (temp == 0 && !isZero(inputBuffer)) {
        return 0;
    }
    integers[index] = temp;
    printf("%d\n", integers[index]);
    return 1;
}

/**
 * Evaluate the sum. If the sum exceeds the largest integer, print error.
 * Otherwise, print the sum
 * @param integers
 * @param finalIndex
 */
void evaluate(int integers[], int finalIndex) {
    long result = sum(integers, finalIndex);
    if (result > INT_MAX || result < INT_MIN) {
        printf("\nError: Sum exceeds the largest integer that can be represented!\n");
    } else {
        printf("\nYour sum is %ld\n", result);
    }
}

int main() {
    printf("Buffer length: %d\n", BUFFER_LEN);
    printf("Array length: %d\n", ARRAY_LEN);

    char inputBuffer[BUFFER_LEN];
    int integers[ARRAY_LEN];
    int index = 0;
    while (1) {
        printf("Please enter your input: ");
        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL)
            break;

        if (!validInputLength(inputBuffer)) {
            printf("Error: Input exceeds the length of the input buffer!\n");
            continue;
        }

        if (!parseInteger(inputBuffer, integers, index)) {
            printf("Error: Input cannot be converted to an integer!\n");
            continue;
        }

        if (++index >= ARRAY_LEN) {
            printf("Array limit reached!\n");
            break;
        }
    }

    evaluate(integers, index);
    return 0;
}
