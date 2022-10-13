/*
Tester program created by mrmandarin
Use at your own risk... I do not guarantee you get 100% on this project if you pass all the cases
If you do though feel free to get me bbt once this pandemic is over ;) (this is a joke)

Program by default goes through all the test cases

There's also a function available to test specific test cases with more debugging information

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "autocomplete.h"

#define CASES 10000
#define PATH "fuck_praxis/fuck_praxis"

void printterms(struct term* arr_ptr, int N) {
	for (int x = 0; x < N; x++) {
		printf("#%d. TERM: %s | WEIGHT: %f \n", x, arr_ptr[x].term, arr_ptr[x].weight);
	}
	printf("\n");
}

//if print_everything is 1, debug mode is enabled
int test_individual_case(int case_num, int print_everything) {
	if (case_num == 19 ||case_num == 475 || case_num == 517 || case_num == 560 ||case_num == 838 || case_num == 988 || case_num == 1590 || case_num == 1809 || case_num == 1895 || case_num == 1935 || case_num == 2026 || case_num == 2051 ||  case_num == 2313 ||case_num == 3015 || case_num == 3054 || case_num == 3144 || case_num == 3349 || case_num == 3470 || case_num == 3778 || case_num == 4462 || case_num == 4671 || case_num == 4759 || case_num == 5340 ||  case_num == 5794 ||case_num == 6728 || case_num == 6795|| case_num == 6923 || case_num == 8010 || case_num == 8066 || case_num == 8571 || case_num == 8622 || case_num == 8869 || case_num == 8968 || case_num == 9270 || case_num == 9787 || case_num == 9885) return 1;
	char current_path[50];
	get_current_path(case_num, current_path, 0);
	struct term* terms;
	int n_terms;
	read_in_terms(&terms, &n_terms, current_path);
	if (print_everything) {
		printf("How terms is sorted for you: \n\n");
		printterms(terms, n_terms);
	}
	char current_out_path[50];
	get_current_path(case_num, current_out_path, 1);
	FILE* out_file = fopen(current_out_path, "r");
	if (out_file == NULL) {
		perror("Error opening output file");
		return -1;
	}

	char input[200];
	fgets(input, sizeof(input), out_file);
	int n_cases = atoi(input);
	for (int i = 0; i < n_cases; i++) {
		fgets(input, sizeof(input), out_file);
		int idx = 0;
		char substr[15];
		while (input[idx] != ' ') {
			substr[idx] = input[idx];
			idx++;
		}
		substr[idx] = '\0';
		idx++;
		char n_answer_str[15];
		int og_idx = idx;
		while (input[idx] != '\n') {
			n_answer_str[idx - og_idx] = input[idx];
			idx++;
		}
		n_answer_str[idx - og_idx] = '\0';
		int out_n_ans = atoi(n_answer_str);

		//printf("SUBSTR: %s N_ANSWER: %d\n", substr, out_n_ans);
		struct term* answer;
		int answer_n;
		autocomplete(&answer, &answer_n, terms, n_terms, substr);

		if (print_everything) {
			printf("How your answer array is sorted for substr: %s\n\n", substr);
			printterms(answer, answer_n);
		}

		if (out_n_ans != answer_n) {
			print_error_message(case_num);
			printf("MRMANDARIN'S ANSWER_N: %d | YOUR ANSWER_N: %d\n\n", out_n_ans, answer_n);
			return -1;
		}

		for (int i = 0; i < out_n_ans; i++) {
			fgets(input, sizeof(input), out_file);
			int idx = 0;
			while (input[idx] != '\n') idx++;
			input[idx] = '\0';
			if (strcmp(input, answer[i].term) != 0) {
				print_error_message(case_num);
				printf("MRMANDARIN'S OUTPUT TERM: %s | YOUR OUTPUT TERM: %s\n\n", input, answer[i].term);
				return -1;
			}
		}

		if (answer_n) {
			free(answer);
		}
	}
	//close file
	free(terms);
	fclose(out_file);
	printf("PASSED CASE: %d\n", case_num);
	return 1;
}

//why is c so retarded with strings ffs
void get_current_path(int num, char* str, int output) {
	char buf[10];
	snprintf(buf, 10, "%d", num);
	strcpy(str, PATH);
	strcat(str, buf);
	if (output) {
		strcat(str, "out");
	}
	strcat(str, ".txt");
}

void print_error_message(int case_num) {
	printf("An error occured while testing sample case %d\n", case_num);
	printf("Checkout fuck_praxis%d.txt in the fuck praxis folder for the exact sample case\n\n", case_num);
}

int test_sample_cases() {
	for (int x = 1; x <= CASES; x++) {
		if (test_individual_case(x, 0) == -1) {
			return 0;
		}
	}
	return 1;
}

int main() {

	//Test individual case
	//Use this if a specific case failed
	//case_num refers to the case you want to test specifically
	//feel free to ignore the second parameter

	//int case_num = 21;
	//test_individual_case(case_num, 1);

	
	if (test_sample_cases()) {
		printf("SUCCESSFULLY PASSED ALL CASES :)");
	}
	else {
		printf("Sorry, you failed.");
	}
	return 0;
}