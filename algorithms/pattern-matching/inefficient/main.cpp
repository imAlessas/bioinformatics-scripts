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

    
    auto start = chrono::high_resolution_clock::now();
    
    // get the index
    vector<int> positions = brute_force(sequence, pattern);

    // calculates duration
    auto stop = chrono::high_resolution_clock::now();
    int duration = chrono::duration_cast<chrono::milliseconds>(stop - start).count();

    // ouputs duration and matches
    cout << endl << "Brute force:  " << duration << " ms" << endl;
    cout << "              " << positions.size() << " match(es)" << endl << endl;

    // writes the indexes
    for (int i : positions)
        output << i << endl;

    input_sequence.close();
    input_pattern.close();
    output.close();

    // opens output file
    system("start output.txt");

    return 0;


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

