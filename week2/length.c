#include <stdio.h>
#include <cs50.h>
#include <string.h>

int string_length(string s);

int main(void){
    string name = get_string("Name: ");
    int length = string_length(name);
    printf("%i\n", length);

    // using strlen()
    int strlength = strlen(name);
    printf("using strlen: %i\n", strlength);
}

int string_length(string s) {
    int i = 0;
    while(s[i] != '\0'){
        i++;
    }
    return i;
}
