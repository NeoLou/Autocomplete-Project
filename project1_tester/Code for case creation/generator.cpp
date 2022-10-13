#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>

#include "autocomplete.c"

#define CASES 10000
#define PATH "fuck_praxis/fuck_praxis"

std::string generate_test_string() {
	std::string test_str = "";
	for (int x = 0; x < rand() % 3 + 1; x++) {
		if (rand() % 4) {
			test_str += 'a' + rand() % 26;
		}
		else {
			test_str += 'A' + rand() % 26;
		}
	}
	return test_str;
}

//pretty sure this causes a memory leak somewhere but fuck it I gotta do rfp
void generate_sample_output() {
	char filename[100];
	for (int x = 1; x <= CASES; x++) {
		std::cout << "CASE: " << x << '\n';

		std::string current_file = PATH + std::to_string(x) + ".txt";
		strcpy(filename, current_file.c_str());
		struct term* terms;
		int num_of_terms;
		read_in_terms(&terms, &num_of_terms, filename);
		std::string output_file = PATH + std::to_string(x) + "out.txt";
		std::ofstream write_file(output_file);
		int test_cases = rand() % 10;
		write_file << std::to_string(test_cases) << '\n';
		for (int i = 0; i < test_cases; i++) {
			std::string test_str = generate_test_string();
			char ye[15];
			strcpy(ye, test_str.c_str());
			struct term* answer;
			int answer_n;
			//std::cout << "GREAT " << ye << '\n';
			autocomplete(&answer, &answer_n, terms, num_of_terms, ye);
			write_file << test_str << ' ' << answer_n << '\n';
			for (int y = 0; y < answer_n; y++) {
				write_file << answer[y].term << '\n';
			}
			if (answer_n) {
				free(answer);
			}
		}
		free(terms);
		write_file.close();
	}
}

/*
int main() {

	/*
	struct term* terms;
	int n;
	char fuck[] = "fuck_praxis/fuck_praxis9.txt";
	read_in_terms(&terms, &n, fuck);
	//print_terms(terms, n);
	struct term* answer;
	int n_answer;
	char fuck1[] = "Q";
	autocomplete(&answer, &n_answer, terms, n, fuck1);
	print_terms(answer, n_answer);

	generate_sample_output();
}
*/