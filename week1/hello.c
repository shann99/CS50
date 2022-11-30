#include <stdio.h>
#include </Users/shannonreid/Downloads/libcs50-11.0.1/build/include/cs50.h>

int main(void)
{
    string answer = get_string("What's your name? ");
    printf("hello, %s\n", answer);
}