/* @imAlessas */

/*
    The KMP algorithm uses the pattern preprocessing to generate a lookup table, AKA oracle, that will point out where to jump in case of mismatch.
    This new approach helps to scan the sequence faster that a normal linear search (or brute force) by reducing te time complecity to O(m + n) ~ O(m)
        With 3.2 billion character and a pattern of 20 character: ~ 12s

*/

#include <bits/stdc++.h>

using namespace std;

// function definition
vector<int> get_oracle(const string&);

vector<int> KMP_search(const string&, const string&, const vector<int>&);


int main() {

    const string DATA_FOLDER_PATH = "../../../data/";

    // defines the source files
    const string sequence_file = "sequence-10000000.txt";
    const string pattern_file = "pattern-20.txt";
    const string output_file = "KMP-search-output.txt";
    

    // uses files to address input and output
    ifstream input_sequence(DATA_FOLDER_PATH + sequence_file);
    ifstream input_pattern(DATA_FOLDER_PATH + pattern_file);
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

    // obtains oracle table
    vector<int> oracle = get_oracle(pattern);

    auto start = chrono::high_resolution_clock::now();
    
    // performs KMP-search
    vector<int> positions = KMP_search(sequence, pattern, oracle);

    // calculates duration
    auto stop = chrono::high_resolution_clock::now();
    int duration = chrono::duration_cast<chrono::milliseconds>(stop - start).count();

    // ouputs duration and matches
    cout << endl << "KMP search:" << endl;
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




// Function to perform Knuth-Morris-Pratt (KMP) string matching algorithm
// This function searches for occurrences of a pattern within a given sequence using the provided Oracle vector
vector<int> KMP_search(const string& sequence, const string& pattern, const vector<int>& oracle) {
    int j = 0, k = 0;
    vector<int> positions;

    // Iterate through the sequence to find matches with the pattern
    while (j < sequence.size()) {
        // Check for matching characters between pattern and sequence
        if (pattern[k] == sequence[j]) {
            j++;
            k++;

            // If a complete match is found, store the position and update k based on Oracle vector
            if (k == pattern.size()) {
                positions.push_back(j - k);
                k = oracle[k - 1];
            }

        } else {
            // Update k based on Oracle vector or move to the next character in the sequence
            if(k)
                k = oracle[k - 1];
            else
                j++; 
        }
    }

    return positions; // Return the positions of pattern occurrences in the sequence
}




// Function to generate the Oracle vector for a given pattern
// This function creates an Oracle vector that stores the longest prefix that is also a suffix for each position in the pattern
vector<int> get_oracle(const string& pattern) {
    int i = 0;
    vector<int> oracle(pattern.size());

    // Iterate through the pattern to populate the Oracle vector
    for (int j = 1; j < pattern.size(); j++) {
        // Update the value of i based on matching prefixes and suffixes
        while (i > 0 && pattern[i] != pattern[j])
            i = oracle[i - 1];
        
        // Increment i if characters match
        if (pattern[i] == pattern[j])
            i++;
        
        // Store the value of i in the Oracle vector at position j
        oracle[j] = i;
    }

    return oracle; // Return the generated Oracle vector
} // get_oracle
