#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char encipher(string key, string text);

int main(int argc, string argv[]) 
{
    string key;
    string text; 
    int length = 0;
    int count = 0;
    char upper1;
    char upper2;
    char encrypt;
    

    if (argc == 2)  {
        key = argv[1];
        //gets the length of the key and if it doesn't equal 26, throw an error
        length = strlen(key);
        if (length != 26) {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else {
            for (int i = 0; i < length; i++) {
                if(isalpha(key[i])) {
                    // for each letter in the string, change it to uppercase (for uniformity) and see if there are any duplicates
                    // by adding up where each letter matches (aka it should equal 26 for an equal match), if it's greater than 26, throw an error
                        for(int k = 0; k < length ; k++){
                            upper1 = toupper(key[i]);
                            upper2 = toupper(key[k]);
                            if(upper1 == upper2) {
                                count++;
                            }             
                        }
                }
                else {
                    printf("Key must only contain alphabetical characters.\n");
                    return 1;
                }
            }
            if (count > 26) {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
            // gets the plain text for the cipher and outputs the cipher text
            else {
                text = get_string("plaintext: ");
                printf("ciphertext: ");
                encrypt = encipher(key, text);
            }  
            printf("\n"); 
        }    
    }
    else if (argc > 2){ 
        printf("Usage: ./substitution key\n");
        return 1;
    } 
    else {
        printf("Usage: ./substitution key\n");
        return 1;
    } 
}


char encipher (string key, string text) {
    string key_cipher = key;
    char keyU;
    char keyL;
    int indexU = 0;
    int indexL = 0;
    //creating arrays for both uppercase and lowercase 
    char isUpper[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char isLower[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't' , 'u', 'v', 'w', 'x', 'y', 'z'};
    //goes through the plaintext string and if the character is uppercase or lowercase, it will go to the correct array to find where the letters match
    // if they match, return the index of that location and then apply that same index to the key index
    for(int i = 0, n = strlen(text); i < n; i++){
        if(islower(text[i])){
            for(int j = 0, x = strlen(isLower); j < x; j++){
                if(isLower[j] == text[i]){
                    indexL = j;
                    //if the text character is lowercase, make it match by also lowercasing the key
                    keyL = tolower(key_cipher[indexL]);
                    printf("%c", keyL);
                }
            }
        }
        else if(isupper(text[i])) {
            for(int k = 0, y = strlen(isUpper); k < y; k++){
                if(isUpper[k] == text[i]){
                    indexU = k;
                    //if the text character is upper, make it match by also uppercasing the key
                    keyU = toupper(key_cipher[indexU]);
                    printf("%c", keyU);
                }
            }
        }
        else {
            printf("%c", text[i]);
        }
    }
    return 0;
}