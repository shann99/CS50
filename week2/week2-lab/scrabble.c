#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>


int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2){
        printf("Player 1 wins!\n");
    }
    else if(score1 < score2){
        printf("Player 2 wins!\n");
    }
    else{
        printf("Tie!\n");
    }
}























int compute_score(string word)
{
    // TODO: Compute and return score for string
    int score = 0;
    int index = 0;
    char upper; 
    char same;
    int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    char alpha[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'W', 'X', 'Y', 'Z'};

    for (int j = 0, x = strlen(word); j < x; j++) {
        //loops the string for each player and checks if each character is alphabetical. if it isn't basically do nothing
        if (isalpha(word[j])){
                // checks if the word is lowercase, if it is, it makes it uppercase
                if(islower(word[j])) {
                upper = toupper(word[j]);
                    // loops through the alpha array to see where the characters from upper matches and it it does, get the index of alpha 
                    // then get the same index in points[] in order to return how much the letter is worth and add those points to score
                    for(int i = 0, n = strlen(alpha); i < n; i++){
                        if (alpha[i] == upper) {
                            index = i;
                            score += POINTS[index];
                        }
                    }
                }
                // checks if the word is upper , if it is, leave it alone and return the index where the character matches in alpha[] 
                // then just get the point from the points[] index since the indexes of both arrays match up 
                else if (isupper(word[j])){
                    same = word[j];
                    for(int i = 0, n = strlen(alpha); i < n; i++){
                        if (alpha[i] == same) {
                            index = i;
                            score += POINTS[index];
                    }
                }
            }
        }
        else {
            score += 0;
        }
    }   
    return score;
}
