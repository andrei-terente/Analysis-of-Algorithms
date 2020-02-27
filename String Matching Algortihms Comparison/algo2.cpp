// C++ program for implementation of RK pattern searching 
// algorithm 
#include <iostream>
#include <stdio.h> 
#include <string.h>
#include <vector>

#include "algo.h"

using namespace std;
  
 
#define d 72
  
/*  pat -> pattern 
    txt -> text 
    q -> A prime number 
*/
std::vector<int> search(char txt[], char pat[]) 
{
    std::vector<int> ret;
    int q = 101; // a prime number
    int M = strlen(pat); 
    int N = strlen(txt); 
    int i, j; 
    int p = 0; // hash value for pattern 
    int t = 0; // hash value for txt 
    int h = 1; 
  
    // The value of h would be "pow(d, M-1)%q" 
    for (i = 0; i < M-1; i++) 
        h = (h*d)%q; 
  

    for (i = 0; i < M; i++) 
    { 
        p = (d*p + pat[i])%q; 
        t = (d*t + txt[i])%q; 
    } 
  
    for (i = 0; i <= N - M; i++) 
    {
        if ( p == t ) 
        { 
            /* Check for characters one by one */
            for (j = 0; j < M; j++) 
            { 
                if (txt[i+j] != pat[j]) 
                    break; 
            } 
  
            // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1] 
            if (j == M) 
                ret.push_back(i); 
        } 
  
    
        if ( i < N-M ) 
        { 
            t = (d*(t - txt[i]*h) + txt[i+M])%q;  
            if (t < 0) 
            t = (t + q); 
        } 
    }
    return ret; 
} 