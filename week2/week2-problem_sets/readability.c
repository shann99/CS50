#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int get_grade(float letters, float words, float sentences);

int main(void){
    string text = get_string("Text: ");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    int grade = get_grade(letters, words, sentences);
}























int count_letters(string text){
    int length = strlen(text);
    int letters = 0;
    
    //calculating letters
    for(int i = 0; i < length; i++){
        if (isalpha(text[i])){
            letters++;
        }
    }
    return letters;
}

int count_words(string text){
    int length = strlen(text);
    int words = 1;
   
   //calculating words
    for(int i = 0; i < length; i++){
        if(isspace(text[i])){
            words++;
        }
    }
    return words;
}

int count_sentences(string text){
    int length = strlen(text);
    int sentences = 0;
   
   //calculating sentences
    for(int i = 0; i < length; i++){
        if(text[i] == '!' || text[i] == '?' || text[i] == '.'){
            sentences++;
        }
    }
    return sentences;
}

int get_grade(float letters, float words, float sentences){
    float L = (letters/words) * 100;
    float S = (sentences/words) * 100;
    int index = round((0.0588 * L) - (0.296 * S) - 15.8);
    if (index >= 16){
        printf("Grade 16+\n");
    }
    else if(index < 1){
        printf("Before Grade 1\n");
    }
    else {
      printf("Grade %i\n", index);  
    }
    return index;
}