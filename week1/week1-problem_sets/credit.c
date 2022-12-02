#include <cs50.h>
#include <stdio.h>
#include <string.h>

long check_card_length(long card);
long checksum(long card);
long check_card_starting_digits (long card);


int main (void){

    long card = get_long("Number: ");
    long check_sum = checksum(card);
    long check_card_len = check_card_length(card);
    long check_card_digits = check_card_starting_digits(card);
    

}




















long checksum(long card) {
    char num_string[255];
    //converts card number to a string
    sprintf(num_string, "%li", card);
    // gets the length of the number (in string form) and saves it as 'n'
    long n = strlen(num_string);

    // just a bunch of initalization here
    long second_total = 0;
    long secondmult = 0;
    long x = card;
    long y = card;
    long z = 0;
    long total = 0;

    //calculates every other digit
    while (x > 0) {
        long second_digit = (x % 100) / 10;
        // seperates the digits of numbers over 10
        // multiplies the second digit by 2
        secondmult = second_digit * 2;
        if (secondmult > 10) {
            while (secondmult > 0) {
                z = secondmult % 10;
                secondmult = secondmult / 10;
                second_total += z;
            }
        }
        // adds the multiplied digits together
        second_total += secondmult;
        x = x / 100;
    }

    // calculates every other other (lol) digit
    long other_total = 0;

    while (y > 0) {
        long other_digit = (y % 10);
        // multiplies the second digit by 2
        other_total += other_digit;
        // adds the multiplied digits together
        y = y / 100;
    }

    //gets the total of the second other digit and the other other digits
    total = second_total + other_total;
    // retrieves the last digit of the total
    long mod_total = total % 10;
    printf("mod_total %li\n", mod_total);
    // calculates if the total ends with a 0
    if (mod_total == 0) {
        return 0;
    }
    else {
        printf("INVALID!\n");
    }
    // returning zero as there's no actual variable i want to have returned here
    return 0;
}


long check_card_length(long card){
    char num_string[255];
    //converts card number to a string
    sprintf(num_string, "%li", card);
    // gets the length of the number (in string form) and saves it as 'n'
    long n = strlen(num_string);
    printf("n %li\n", n);
    // checks if the length of the card is between the correct numbers for the three credit cards
    if (n == 13 || n == 15 || n == 16) {
        return 0;
    }
    else {
        printf("INVALID!\n");
    }
    // returning zero as there's no actual variable i want to have returned here
    return 0;
}
long check_card_starting_digits (long card) {
    long starting_digits = card;
    // isolates the two starting digits 
    while (starting_digits >= 100){
        starting_digits = starting_digits / 10;
    }
    
    // checks if starting digits are between the range for mastercard
    if (starting_digits >= 51 && starting_digits <= 55){
        printf("MASTERCARD!\n");
    }
    // checks if starting digits match the correct nums of AMEX
    else if (starting_digits == 34 || starting_digits == 37){
        printf("AMEX!\n");
    }
    // checks if starting digits are between the range for VISA
    else if (starting_digits >= 40 && starting_digits <= 49)  {
        printf("VISA!\n");
    }
    else {
        printf("INVALID!\n");
    }
    // returning zero as there's no actual variable i want to have returned here
    return 0;
}
   
