#include "allheaders.h"

int main(int argc, char **argv) {
    int number = 1;

    // Loop through numbers from 1 to 1000
    while (number <= 10000) {
        int temp = number;
        int total = 0;
        int digits = (int)log10(number) + 1; // Calculate the number of digits in the number

        // Loop through each digit of the number
        while (temp != 0) {
            int digit = temp % 10; // Get the last digit
            total += pow(digit, digits); // Raise it to the power of 'digits' and add to total
            temp /= 10; // Remove the last digit
        }

        // Check if the sum of digits raised to the 'digits' power equals the original number
        if (total == number) {
            printf("%d is an Armstrong number\n", number);
        }

        ++number; // Move to the next number
    }
    return 0;
}
