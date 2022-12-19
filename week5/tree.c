//implements a list of numbers as a binary search tree
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

//represents a node
typedef struct node{
    int number;
    struct node *left;
    struct node *right;
}node;

void free_tree(node *root);
void print_tree(node *root);
bool search (node *tree, int number);

int main(void){
    //tree of size 0

    node *tree = NULL;

    //add number to list
    node *n = malloc(sizeof(node));
    if(n  == NULL){
        return 1;
    }
    n->number = 2;
    n->left = NULL;
    n->right = NULL;
    tree = n;

    n = malloc(sizeof(node));
    if (n == NULL){
        return 1;
    }
    n->number = 1;
    n->left = NULL;
    n->right = NULL;
    tree->left = n;

    //add number to list
    n = malloc(sizeof(node));
    if(n == NULL){
        return 1;
    }
    n->number = 3;
    n->left = NULL;
    n->right = NULL;
    tree->right = n;

    //print tree
    print_tree(tree);
    

    //free tree
    free_tree(tree);
}

void free_tree(node *root){
    if (root == NULL){
            return;
        }
    free_tree (root->left);
    free_tree(root->right);
    free(root);
}

void print_tree (node *root){
    if (root == NULL){
        return;
    }
    print_tree (root->left);
    printf("%i\n", root->number);
    print_tree(root->right);
}
//how to do a binary tree search
bool search (node *tree, int number){
    if (tree == NULL){
        return false;
    }
    else if (number < tree->number){
        return search(tree->left, number);
    }
    else if(number > tree->number){
        return search(tree->right, number);
    }
    else {
        return true;
    }
    return false;
}