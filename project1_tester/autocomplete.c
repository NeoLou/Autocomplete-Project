#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "autocomplete.h"


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
    fclose(fp);
}

int lowest_match(struct term *terms, int nterms, char *substr)
{
	int cmp, mid;
	int l = 0;
    int r = nterms-1;
    int len = strlen(substr);
	if (strcmp(substr, terms[r].term) > 0)
	{
		return -1;
	}
    char *buff = (char*)malloc(len+1);
	buff[len] = '\0';

    while (l < r)
    {
        mid = (int)((l+r)/2);
        cmp = strcmp(substr, strncpy(buff, terms[mid].term, len));
        if (cmp <= 0)
        {
            r = mid;
        }
        else
        {
            l = mid+1;
        }
    }
	if (strcmp(substr, strncpy(buff, terms[l].term, len)) != 0)
	{
		free(buff);
		return -1;
	}
	free(buff);
    return l;
}

int highest_match(struct term *terms, int nterms, char *substr)
{
	int cmp, mid;
	int l = 0;
    int r = nterms-1;
    int len = strlen(substr);
	if (strcmp(substr, terms[r].term) > 0)
	{
		return -1;
	}
    char *buff = (char*)malloc(len+1);
	buff[len] = '\0';

    while (l < r)
    {
        mid = (int)((l+r)/2 + 1);
        cmp = strcmp(substr, strncpy(buff, terms[mid].term, len));
        if (cmp < 0)
        {
            r = mid-1;
        }
        else
        {
            l = mid;
        }
    }
	if (strcmp(substr, strncpy(buff, terms[r].term, len)) != 0)
	{
		free(buff);
		return -1;
	}
	free(buff);
    return l;
}

int weight_cmp(const void * a, const void* b)
{
    double c = ((struct term *)a)->weight;
    double d = ((struct term *)b)->weight;
    
    return d - c;
}

void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr)
{
    int lowest = lowest_match(terms, nterms, substr);
    int highest = highest_match(terms, nterms, substr);
    if (lowest == -1) { *n_answer = 0; }
    else { *n_answer = highest - lowest + 1; }
    
    *answer = (struct term *)malloc(sizeof (struct term) * *n_answer);

    for (int i = 0; i < *n_answer; i++)
    {
        (*answer)[i] = terms[lowest + i];
    }
    /*
    printf("--begin--\n");

    printf("LEFT: %d \nRIGHT: %d\n nans: %d\n", lowest, highest, *n_answer);

    printf("--end--\n");
    */

    qsort(*answer, *n_answer, sizeof(struct term), weight_cmp);

}