#include <stdio.h>
#include </Users/shannonreid/Downloads/libcs50-11.0.1/build/include/cs50.h>

int main(void)
{
    //prompt user to agree
    char c = get_char("Do you agree? ");
    //check whether user agreed
    if (c == 'y' || c == 'Y'){
        printf("Agreed.\n");
    }
    else if (c == 'n' || c == 'N'){
        printf("Not agreed.\n");
    }
}