/* @imAlessas */

#include <bits/stdc++.h>

using namespace std;

int main() {
    // defines the source files
    string sequence_file = "sequence-10000.txt";
    string pattern_file = "pattern-5.txt";

    

    // uses files to address input and output
    ifstream input_sequence("../../data-folder/" + sequence_file);
    ifstream input_pattern("../../data-folder/" + pattern_file);
    ofstream output("output.txt");

    // display eventual errors
    if (!input_sequence.is_open() || !input_pattern.is_open() || !output.is_open()) {
        cout << endl << "Error opening files." << endl << endl;
        return 1;
    }

    // defines sequence and pattern
    string sequence, pattern;
    getline(input_sequence, sequence);
    getline(input_pattern, pattern);


    // get the index



    return 0;
} // main