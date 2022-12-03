#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool only_digits(string key_check);
char rotate (char chr, int key); 

int main(int argc, string argv[]) {
    string key_check;
    int key = 0;
    string text;
    char chr;
    char encrypt;

    // checks if there is an argument provided when calling program
    if (argc == 2) {
        key_check = argv[1];
        bool digit_check = only_digits(key_check);
            if (digit_check == true) {
               key = atoi(key_check); 
               text = get_string("plaintext: ");
               printf("ciphertext: ");
               //for the length of the plaintext, run the encryption on each character
               for (int i = 0, n = strlen(text); i < n; i++){
                    chr = text[i];
                    char encrypt = rotate(chr, key); 
               }
               printf("\n");
            }
            else {
               printf("Usage: ./caesar key\n");
               return 1;
            }
        return 0;
    }
    else if (argc > 2){ 
        printf("Usage: ./caesar key\n");
        return 1;
    } 
    else {
        printf("Usage: ./caesar key\n");
        return 1;
    }  
}








//checks if the argument provided when calling the program is a number or not
bool only_digits(string s){
    int n = strlen(s);
    for (int i = 0; i < n; i++) {
        if (isdigit(s[i]) && s[i] >= 0 || s[i] <= 9) {
            return true;  
        }
        else {
            return false;
        }
    }
    return true;
}




char rotate (char chr, int key){
    int new_indexU = 0;
    int new_indexL = 0;
    int indexU = -1;
    int indexL = -1;
    // creating arrays that makes it easier to call the array location and add to it to form the new cipher
    //created two arrays for both upper + lower for easy segmenation
    char isUpper[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char isLower[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't' , 'u', 'v', 'w', 'x', 'y', 'z'};
    
    //checks if a letter in the string is uppercase and if is, checks the location in the isUpper array where the char matches
    //gets the index of the matched char and then adds the key to it (now known as new index). if the new index is over 25, get the remainder and return the position
    if (isupper(chr)){
        for (int i = 0, xU = strlen(isUpper); i < xU; i++) {
            if (isUpper[i] == chr) {
                indexU = i;
                new_indexU = indexU + key;
                if (new_indexU < 25){
                    printf("%c", isUpper[new_indexU]);
                }
                else {
                    int overflow_index = (indexU + key) % 26;
                    printf("%c", isUpper[overflow_index]);
                }
            }
        }
    }

    //checking if a letter in the string is uppercase
    else if (islower(chr)){
        for (int j = 0, xL = strlen(isLower); j < xL; j++) {
            //checks where the cipher char as its going through the for loop in the main function is located
            if (isLower[j] == chr) { 
                int indexL = j;
                new_indexL = indexL + key;
                if (new_indexL < 25){
                    printf("%c", isLower[new_indexL]);
                }
                else {
                    int overflow_index = (indexL + key) % 26;
                    printf("%c", isLower[overflow_index]);
                }
            }
        }
    }
    else {
        printf("%c", chr);
    }
    
    return 0;
}