#include <stdio.h>
#include </Users/shannonreid/Downloads/libcs50-11.0.1/build/include/cs50.h>

int main(void){
    int n;
    do {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    //for each row
    for (int i = 1; i <= n; i++) {
        for (int x = n; x > i; x--) {
            printf(" ");
        }
        for (int j = 1; j <= i; j++) {
            printf("#");
        }
        printf(" ");
        for (int z = 1; z <= i; z++) {
            printf("#");
        }
    printf("\n");
    }
   
}