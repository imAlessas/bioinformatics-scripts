/* @imAlessas */

#include <bits/stdc++.h>

using namespace std;

// function definition
void fill_table(int[], const string&);
int* KMP_search(const string&, const string&, int[]);

int main() {
    string sequence, pattern;

    cin >> sequence >> pattern;

    int lookup[pattern.size()] = {0};

    fill_table(lookup, pattern);




    return 0;
} // main


void fill_table(int lookup[], const string& pattern){
    int i = 0;

    for(int j = 1; j < pattern.size(); j++){
        while(i > 0 && pattern[i] != pattern[j])
            i = lookup[i - 1];
        
        if(pattern[i] == pattern[j])
            i++;
        
        lookup[j] = i;
    }
} // fill_table


int* KMP_search(const string& sequence, const string& pattern, int[] lookup){


} //  KMP_search