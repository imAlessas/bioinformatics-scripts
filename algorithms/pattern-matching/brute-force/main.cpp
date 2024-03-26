/* @imAlessas */

/*
    This algorithm performs the simplest search through the sequence using the pattern resulting in an inefficient way to find the patterns in a sequence.
    Resonably, by analizing the algorithm its complexity is O(mn) which is quadratic through the length of the sequence (m) and the mattern (n).
        With 3.2 billion character and a pattern of 20 character: ~ 16s
*/


#include <bits/stdc++.h>

using namespace std;

// functions definition
vector<int> brute_force(const string&, const string&);


int main() {
    // defines the source files
    string sequence_file = "sequence-3200000000.txt";
    string pattern_file = "pattern-20.txt";
    string output_file = "brute-force-output.txt";

    

    // uses files to address input and output
    ifstream input_sequence("../../../data/" + sequence_file);
    ifstream input_pattern("../../../data/" + pattern_file);
    ofstream output(output_file);


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

    
    auto start = chrono::high_resolution_clock::now();
    
    // get the index
    vector<int> positions = brute_force(sequence, pattern);

    // calculates duration
    auto stop = chrono::high_resolution_clock::now();
    int duration = chrono::duration_cast<chrono::milliseconds>(stop - start).count();

    // ouputs duration and matches
    cout << endl << "Brute force:" << endl;
    cout << "   Matches:    " << "\033[1m \033[33m" << positions.size() << "\033[37m \033[0m" << endl;
    cout << "   Duration:   " << "\033[34m" << duration << " ms" << "\033[37m" << endl << endl;



    // writes the indexes
    for (int i : positions)
        output << i << endl;

    input_sequence.close();
    input_pattern.close();
    output.close();

    // opens output file
    system(("start " + output_file).c_str());
    
    return 0;
} // main




// brute_force implementation
vector<int> brute_force(const string& sequence, const string& pattern) {
    vector<int> positions = {};
    bool match;

    for(int i = 0; i < sequence.size(); i++){ // cycle through sequence
        match = true;

        for(int j = 0; j < pattern.size(); j++){ // cycles through pattern
             if( sequence[i + j] != pattern[j] ){
                match = false;
                break;
             }
        }   

        if(match) // adds position
            positions.push_back(i);
    }

    return positions;
}

