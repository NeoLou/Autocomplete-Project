#if !defined(AUTOCOMPLETE_H)
#define AUTOCOMPLETE_H

#pragma warning(disable : 4996)
#pragma warning(disable : 6386)
#pragma warning(disable : 6385)
#pragma warning(disable : 6011)
#pragma warning(disable : 6054)
#pragma warning(disable : 6001)

struct term {
    char term[200]; // assume terms are not longer than 200
    double weight;
};

void print_error_message(int case_num);
void printterms(struct term* arr_ptr, int N); 
int test_individual_case(int case_num, int print_everything);
void get_current_path(int num, char* str, int output);
void read_in_terms(struct term** terms, int* pnterms, char* filename);
int lowest_match(struct term* terms, int nterms, char* substr);
int highest_match(struct term* terms, int nterms, char* substr);
void autocomplete(struct term** answer, int* n_answer, struct term* terms, int nterms, char* substr);
//void print_terms(struct term* arr_ptr, int N);

#endif