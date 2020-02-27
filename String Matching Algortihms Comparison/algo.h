#ifndef ALGO_H
#define ALGO_H

#include <vector>

/**	
 * Searches for matches of the pattern in the text.
 * When a match is found, its shift relative to 
 * the text's starting index is added to the return
 * container
 */



std::vector<int> search(char txt[], char pat[]);


#endif