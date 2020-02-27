#include <vector>
#include <string.h>

#include "algo.h"

using namespace std;

/**
 * Naive method implementation for string matching. 
 * Was used to generate ref files.
*/
std::vector<int> search(char txt[], char pat[]) {
	
	std::vector<int> ret;
	int T = strlen(txt);
	int P = strlen(pat);
	for (int i = 0; i < T; ++i) {
		bool match = true;
		for (int j = 0; j < P; ++j) {
			if (i + j > T) {
				match = false;
				break;
			}
			if (txt[i + j] != pat[j]) {
				match = false;
				break;
			}
		}
		if (match) {
			ret.push_back(i);
		}
	}
	return ret;
}