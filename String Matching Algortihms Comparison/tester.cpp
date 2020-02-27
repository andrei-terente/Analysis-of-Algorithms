#include <iostream>
#include <string.h>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

#include "algo.h"

using namespace std;

const int STANDARD_SETS = 6;

const int MAX_TEST_NAME_SIZE = 32;

const int NUM_TESTS = 15;

const int MAX_TEXT_SIZE = 1638401;

const int MAX_BIG_TEXT_SIZE = 2000001;

const int BIG_SETS = 3;

auto TOTAL_EXEC_TIME = std::chrono::steady_clock::now();


int parse_input(const char* input_file, char* text, char* pattern) {
	ifstream my_file (input_file);
	string line;
	
	if (my_file.is_open()) {
		getline(my_file, line);
		int T = line.length() + 1;
		strcpy(text, line.c_str());
		
		getline(my_file, line);
		int P = line.length() + 1;
		strcpy(pattern, line.c_str());
	
		my_file.close();
		return 0;

	} else {
		cout << "Error opening file: " << input_file << endl;
		return -1;
	}

}

void get_reference(const char *output_path, char *text, char *pattern) {
	std::vector<int> ref = search(text, pattern);
	ofstream out(output_path);
	if (!out.is_open()) {
		cout << "cant open ref: " << output_path << endl;
		return;
	}
	for(int i = 0; i < ref.size(); ++i) {
		out << ref[i] << " ";
	}
	out.close();
}

int parse_output(const char* reference_file, std::vector<int> &expected) {
	ifstream ref(reference_file);
	if(!ref.is_open()) {
		cout << "ERROR: file can't be opened: " << reference_file << endl;
		return -1;
	}

	int elem;
	while (ref >> elem) {
		expected.push_back(elem);
	}

	ref.close();
	return 0;
}

int run_test(const char* input_file, const char* reference_file) {
	
	std:std::vector<int> result, expected;
	char text[MAX_BIG_TEXT_SIZE];
	char pattern[MAX_BIG_TEXT_SIZE];
	
	parse_input(input_file, text, pattern);
	
	auto start = std::chrono::steady_clock::now();
	result = search(text, pattern);
	auto end = std::chrono::steady_clock::now();
	auto diff = end - start;
	TOTAL_EXEC_TIME += diff;
	std::cout << "execution time: " <<chrono::duration <double, milli> (diff).count() << " ms" << std::endl;
	

	result = search(text, pattern);
	parse_output(reference_file, expected);

	if (result == expected) {
		return 1;
	}

	return 0;

}

void run_standard_tests() {
	cout << "\t\tCurrently testing: STANDARD TESTS\n";
	
	char input_file[MAX_TEST_NAME_SIZE];
	char ref_file[MAX_TEST_NAME_SIZE];
	
	for (int curr_set = 1; curr_set <= STANDARD_SETS; ++curr_set) {
		cout << "\tSET " << curr_set << endl;
		for (int curr_test = 0; curr_test < NUM_TESTS; ++curr_test) {
			
			sprintf(input_file, "in/in%d/input%d.txt", curr_set, curr_test);
			sprintf(ref_file, "out/out%d/output%d.txt", curr_set, curr_test);

			cout << "TEST " << std::left << std::setw(2) << curr_test << "......................"
				 << (run_test(input_file, ref_file) == 1 ? "PASSED\n" : "FAILED\n");

		}
	}
	//cout << "SET execution time: " << chrono::duration <double, milli> (TOTAL_EXEC_TIME).count() << " ms" << std::endl;
}

void run_big_tests() {
	cout << "\t\tCurrently testing: BIG TESTS: ";
	
	char input_file[MAX_TEST_NAME_SIZE];
	char ref_file[MAX_TEST_NAME_SIZE];
	
	for (int curr_set = 1; curr_set <= BIG_SETS; ++curr_set) {
		cout << "\tBIG SET " << curr_set << endl;
		for (int curr_test = 0; curr_test < NUM_TESTS; ++curr_test) {
			
			sprintf(input_file, "in/big_in%d/input%d.txt", curr_set, curr_test);
			sprintf(ref_file, "out/big_out%d/output%d.txt", curr_set, curr_test);

			cout << "TEST " << std::left << std::setw(2) << curr_test << "......................"
				 << (run_test(input_file, ref_file) == 1 ? "PASSED\n" : "FAILED\n");

		}
	}
	//cout << "SET execution time: " << chrono::duration <double, milli> (TOTAL_EXEC_TIME).count() << " ms" << std::endl;
}


int main() {

	run_standard_tests();

	run_big_tests();

	return 0;
}
