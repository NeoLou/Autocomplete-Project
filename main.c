#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "autocomplete.h"

/*
Part 1
Write a function with the signature 
void read_in_terms(struct term **terms, int *pnterms, char *filename);
The function takes in a pointer to a pointer to struct term, a pointer to an int,
and the name of a file that is formatted like cities.txt.
The function allocates memory for all the terms in the file and stores a pointer to the block in *terms.
The function stores the number of terms in *pnterms.
The function reads in all the terms from filename, and places them in the block pointed to by *terms.
The terms should be sorted in lexicographic order.
*/

int cmpterms (const void * a, const void * b) {
   char *c = ((struct term *)a)->term;
   char *d = ((struct term *)b)->term;
   return strcmp(c, d);
}

void read_in_terms(struct term **terms, int *pnterms, char *filename){
    char line[200];
    FILE *fp = fopen(filename, "r");
    int nterms = atoi(fgets(line, sizeof(line), fp)); //reads first line for number of terms
    *pnterms = nterms;
    *terms = (struct term *)malloc(nterms * sizeof(struct term));
    for(int i = 0; i < nterms; i++){
        fgets(line, sizeof(line), fp); //read in at most sizeof(line) characters; (including '\0') into line.
        int j = 0;
        int l = 0;
        int is_term = 1;
        char cur_weight[50] = "";
        for(int k = 0; k < sizeof(line); k++){
            if (line[k] == '\t'){
                is_term = 0;
                k++;
            }
            if (line[k] == '\n'){
                (((*terms) + i)->term)[j] = '\0';
                break;
            }
            if (is_term == 0){ //extract term
                (((*terms) + i)->term)[j] = line[k];
                j++;
            }
            else if (isdigit(line[k]) > 0){ //extract weight
                cur_weight[l] = line[k];
                l++;
            }
        }
        (((*terms) + i)->weight) = atoi(cur_weight);
    }
    qsort(*terms, nterms, sizeof(struct term), cmpterms);
}

void print_terms(struct term **terms, int nterms){
    for(int i = 0; i < nterms; i++){
        printf("term: ");
        puts(((*terms) + i)->term);
        int cur_weight = ((*terms) + i)->weight;
        printf("weight: %ld\n", cur_weight);
    }
}

/*
Part 2(a)
Write a function with the signature
int lowest_match(struct term *terms, int nterms, char *substr);
The function returns the index in terms of the first term in lexicographic ordering that matches the string substr.
This function must run in O(log(nterms)) time, where nterms is the number of terms in terms.
You can assume that terms is sorted in ascending lexicographic ordering.
*/

int lowest_match(struct term *terms, int nterms, char *substr){
    int low = 0;
    int high = nterms - 1;
    int mid = 0;
    int len = strlen(substr);
    if (strcmp(substr, (terms + high)->term) > 0) {
        return -1;
    }
    char *temp = (char *)malloc(len + 1);
    temp[len] = '\0';
    while (high > low + 1) {
        mid = (int)((high + low)/2);
        char *mid_str = (terms + mid - 1)->term;
        strncpy(temp, mid_str, len);
        //printf("mid: %s\n", temp);  
        if (strcmp(temp, substr) >= 0){
            high = mid;
        }
        else{
            low = mid;
        }
        char *low_str = (terms + low - 1)->term;
        strncpy(temp, low_str, len);
        //printf("low: %ld\n", low);
        //printf("mid: %ld\n", mid);
        //printf("high: %ld\n", high);
        //printf("low: %s\n\n", temp);   
        if (strcmp(temp, substr) == 0){
            return low;
        }
    }
    char *high_str = (terms + high - 1)->term;
    strncpy(temp, high_str, len);
    if (strcmp(temp, substr) == 0){
        return high;
    }
    return -1;
}

/*
Part 2(b)
Write a function with the signature
int highest_match(struct term *terms, int nterms, char *substr);
The function returns the index in terms of the last term in lexicographic order that matches the string substr.
This function must run in O(log(nterms)) time, where nterms is the number of terms in terms.
You can assume that terms is sorted in ascending lexicographic ordering.
*/

int highest_match(struct term *terms, int nterms, char *substr){
    int low = 0;
    int high = nterms - 1;
    int mid = 0;
    int len = strlen(substr);
    if (strcmp(substr, (terms + high)->term) > 0) {
        return -1;
    }
    char *temp = (char *)malloc(len + 1);
    temp[len] = '\0';
    while (high > low + 1) {
        mid = (int)((high + low)/2);
        char *mid_str = (terms + mid - 1)->term;
        strncpy(temp, mid_str, len);
        if (strcmp(temp, substr) <= 0){
            low = mid;
        }
        else{
            high = mid;
        }
        char *high_str = (terms + high - 1)->term;
        strncpy(temp, high_str, len);
        //printf("low: %ld\n", low);
        //printf("mid: %ld\n", mid);
        //printf("high: %ld\n", high);
        //printf("%s\n\n", temp);
        if (strcmp(temp, substr) == 0){
            return high;
        }
    }
    char *low_str = (terms + low - 1)->term;
    strncpy(temp, low_str, len);
    if (strcmp(temp, substr) == 0){
        return low;
    }
    return -1;
}

/*
Part 3
Write a function with the signature 
void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr);
The function takes terms (assume it is sorted lexicographically), the number of terms nterms,
and the query string substr, and places the answers in answer, with *n_answer being the number of answers.
The answer should be sorted by weight.
*/

void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr){
    //highest_match - lowest_match;
    return;
}

/*
Reading in files
The following code can be used to read in N lines of a text file line-by-line.
char line[200];
FILE *fp = fopen(filename, "r");
for(int i = 0; i < N; i++){
    fgets(line, sizeof(line), fp); //read in at most sizeof(line) characters
                                   //(including '\0') into line.
}
================
Sorting with qsort
See here: https://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm
==================
Compilation instructions
You should use the provided autocomplete.h. Your code should compile without errors with
gcc -Wall autocomplete.c main.c
with autocomplete.h placed in the same folder as the C files. You should modify your main.c to test your work,
but we will be compiling your autocomplete.c with our version of autocomplete.h (which is the same as yourse) and our own main.c.
*/


int main(void)
{
    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, "cities_test.txt");
    print_terms(&terms, nterms);
    printf("%ld\n", lowest_match(terms, nterms, "Tor"));
    printf("%ld\n", highest_match(terms, nterms, "Tor"));
    
    /*
    struct term *answer;
    int n_answer;
    autocomplete(&answer, &n_answer, terms, nterms, "Tor");
    //free allocated blocks here -- not required for the project, but good practice
    */
    return 0;
}
