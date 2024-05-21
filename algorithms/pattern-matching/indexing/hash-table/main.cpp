/* @imAlessas */

/*
    The hash-table indexing technique uses the sequence-preporcessing to analyze and obtain the pattern positions in the sequence
    This approach uses more memory than the KMP-search: by using the 3.2B sequence the compiler is likely to throw a std::bad_alloc error
    By comparing this process with the vector<pattern, pos> we can see a major improvement time-wise: for 10 mln character this approach needs 5 seconds meanwhile the vector approach needs 40 seconds
    Nonetheless this approach is less efficient than the KMP search but allows to search different patterns at the same time by using the same index. On the other hand, for every pattern the KMP search needs a new oracle.
*/


#include <bits/stdc++.h>

using namespace std;


// function definition

vector<int> find_pattern(const string&, const string&, unordered_map<string, vector<int>>&, int);

bool check_position(int, int, const string&, const string&);

unordered_map<string, vector<int>> get_hash_table(const string&, int);



int main() {

    const string DATA_FOLDER_PATH = "../../../../data/";

    // defines the source files
    const string sequence_file = "sequence-100000000.txt";
    const string pattern_file = "pattern-10.txt";
    const string output_file = "hash-table-indexing-output.txt";

    const int k = 5;
    


    // uses files to address input and output
    ifstream input_sequence(DATA_FOLDER_PATH + sequence_file);
    ifstream input_pattern(DATA_FOLDER_PATH + pattern_file);
    ofstream output(output_file);

    // displays eventual errors
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


    // gets hash_table
    unordered_map<string, vector<int>> hash_table = get_hash_table(sequence, k);

    // gets positions
    vector<int> positions = find_pattern(sequence, pattern, hash_table, k);


    // calculates duration
    auto stop = chrono::high_resolution_clock::now();
    int duration = chrono::duration_cast<chrono::milliseconds>(stop - start).count();

    // ouputs duration and matches
    cout << endl << "Hash-Table:" << endl;
    cout << "   Matches:    " << "\033[1m \033[33m" << positions.size() << "\033[37m \033[0m" << endl;
    cout << "   Duration:   " << "\033[34m" << duration << " ms" << "\033[37m" << endl << endl;


    // writes the indexes
    output << "Total occurrences: " << positions.size() << endl << endl;
    for (int i : positions)
        output << i << endl;

    input_sequence.close();
    input_pattern.close();
    output.close();

    // opens output file
    
    system(("start " + output_file).c_str());


    return 0;
} // main




// This function returns all the positions of the pattern by analyzing the hash_table
vector<int> find_pattern(const string& sequence, const string& pattern, unordered_map<string, vector<int>>& table, int k){

    // vector with all positions
    vector<int> positions = {};

    // first k chars of the pattern
    string pattern_subs = pattern.substr(0, k);

    // gets all the positions
    vector<int> positions_uncheck = table[pattern_subs];

    // checks for the rest of the pattern
    for(int pos : positions_uncheck)
        if( check_position(pos, k, pattern, sequence) )
            positions.push_back(pos);

    return positions;
}


// Checks if the position is the beginning of a pattern occurrency
bool check_position(int sequence_idx, int k, const string& pattern, const string& sequence){

    int start_check = sequence_idx + k;

    for(int i = 0; i < pattern.size() - k; i++){
        
        // if reached the end of the string or the pattern does not match
        if(sequence[start_check + i] == string::npos || sequence[start_check + i] != pattern[k + i])
            return false;
    }


    return true;
} // check_position



// Function to generate an index of substrings of length k from a given sequence
// The hash_table unordered_map substrings to the positions where they occur in the sequence
unordered_map<string, vector<int>> get_hash_table(const string& sequence, int k) {
    unordered_map<string, vector<int>> hash_table;
    string s;

    // Iterate through the sequence to create the index
    for (int i = 0; i < sequence.size() - k; i++) {
        s = sequence.substr(i, k);
        auto pos = hash_table.find(s);  // O(1)

        // Handle collisions by updating existing entries or inserting new ones
        if (pos != hash_table.end())
            pos->second.push_back(i);
        else
            hash_table.emplace_hint(pos, s, vector<int>{i});
    }

    return hash_table; // Return the generated hash table
} // get_hash_table
