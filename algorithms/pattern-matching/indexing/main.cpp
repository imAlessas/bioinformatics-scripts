/* @imAlessas */

#include <bits/stdc++.h>

using namespace std;

int main() {
    // defines the source files
    string sequence_file = "sequence-10000.txt";
    string pattern_file = "pattern-5.txt";

    

    // uses files to address input and output
    ifstream input_sequence("../../../data/" + sequence_file);
    ifstream input_pattern("../../../data/" + pattern_file);
    ofstream output("output.txt");

    // uses files to address input and output
    ifstream input_sequence("../../../data/" + sequence_file);
    ifstream input_pattern("../../../data/" + pattern_file);
    ofstream output("output.txt");

    // display eventual errors
    if (!input_sequence.is_open() || !input_pattern.is_open() || !output.is_open()) {
        cout << endl << "          \033[31m" << "\033[1m" << "Error" << "\033[0m" << "\033[31m" << " opening files." << "\033[37m" << endl << endl;
        return 1;
    }

    cout << endl << "            \033[32m" << "Files " << "\033[1m" << "accepted" << "\033[0m\033[32m" << "." << "\033[37m" << endl << endl;

    
    // defines sequence and pattern
    string sequence, pattern;
    getline(input_sequence, sequence);
    getline(input_pattern, pattern);


    // get the index



    return 0;
} // main