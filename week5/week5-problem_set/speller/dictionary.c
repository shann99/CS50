// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"
#include <ctype.h>

#define MULT (97)

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1500;
bool loader = false;
unsigned int count = -1;


// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //hash word
    unsigned int index = 0;
    index = hash(word);
    //set search equal to the index of the hashed word to find the word in the right linkedlist
    node *search = table[index];
    //while search (the first node) does not equal null, search for the word
    //if the word can't be found and the first node, set search equal to the next node and continue
    while(search != NULL){
       if(strcasecmp(search->word, word) == 0){
            return true;
        }
        else {
            search = search->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //sources to figure out hashing function:
    //https://stackoverflow.com/questions/16348512/getting-the-first-10-characters-of-a-string
    //https://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)HashTables.html?highlight=%28CategoryAlgorithmNotes%29
    unsigned int hash_word = 0;
    char *lower = calloc(sizeof(char), 11);
    //gets first 10 characters of word, then converts them to lowercase
    for(int i = 0; i < 10 && word[i] != '\0'; i++) {
        lower[i] = tolower(word[i]);
    }
    //gets the length of the word and hashes it by getting the ascii value of each character and multiplying it
    //by 97. then calling modulo on the hash so it fits into the table size of 1,500
    int n = strlen(lower);
    for (int j = 0; j < n; j++){
        hash_word += lower[j] * MULT;
        hash_word = hash_word % N;
    }
    free(lower);
    return hash_word;
}
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return false;
    }
    char *word = calloc(46, sizeof(char));
    unsigned int hashWord = 0;
    //node *dict = malloc(sizeof(node));
    //read strings from file one at a time
    do {
        //create a new node for each word
       node *dict = malloc(sizeof(node));
        memset(dict, 0, sizeof(node));
        //check if node returns null and if it does, return false
        if (dict == NULL){
             return false;
        }
        strcpy(dict->word, word);
        //hash word to obtain a hash value
        hashWord = hash(dict->word);
        //insert word into hashtable
        if (table[hashWord] == NULL) {
            table[hashWord] = dict;
            dict->next = NULL;
        }
        else {
           dict->next = table[hashWord];
           table[hashWord] = dict;
        }
        count++;
    } while (fscanf(file, "%s", word) != EOF);

    //setting loader to true in load -> this way once size is called, it will return count
    free(word);
    fclose(file);
    loader = true;
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    //i declared at the top a boolean named loader thats set to false and declared an unsigned int named count
    //in load(), i change loader = true this way once load is ran, the "switch" will basically be flipped and allow for the count to be
    //returned here, else return 0
    if (loader != true){
        return 0;
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //loop through table (hashmap)
     for (int i = 0; i <= N; i++){
       //if i does not equal NULL, access that list
           node *head = table[i];
          //while head (aka the first node in the linkedlist) is not null
           //set the temp value to head, head equals head->next and free tmp and continue
           while(head != NULL){
              node *temp = head;
              head = head->next;
              free (temp);
         }
     }
     return true;
}
