#include <stdio.h>
#include </Users/shannonreid/Downloads/libcs50-11.0.1/src/cs50.h>

int main(void)
{
    long x = get_long("x: ");
    long y = get_long("y: ");
    long z = x + y;
    printf("%li\n", z);
}