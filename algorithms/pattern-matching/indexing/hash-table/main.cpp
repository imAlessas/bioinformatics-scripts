/* @imAlessas */

/*
    The hash-table indexing technique uses the sequence-preporcessing to analyze and obtain the pattern positions in the sequence
    This approach uses more memory than the KMP-search: by using the 3.2B sequence the compiler is likely to throw a std::bad_alloc error
    Nonetheless this approach is less efficient than the KMP search but allows to search different patterns at the same time by using the same index. On the other hand, for every pattern the KMP search needs a new oracle.
*/


#include <bits/stdc++.h>

using namespace std;


// function definition

unordered_map<string, vector<int>> get_hash_table(const string&, int);

vector<int> find_pattern(const string&, const string&, unordered_map<string, vector<int>>&, int);



int main() {

    // defines the source files
    string sequence_file = "sequence-10000000.txt";
    string pattern_file = "pattern-10.txt";

    const int k = 5;
    

    // uses files to address input and output
    ifstream input_sequence("../../../data/" + sequence_file);
    ifstream input_pattern("../../../data/" + pattern_file);
    ofstream output("output.txt");

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
    for (int i : positions)
        output << i << endl;

    input_sequence.close();
    input_pattern.close();
    output.close();

    // opens output file
    system("start output.txt");


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


    bool flag;
    int start_check;

    // checks for the rest of the pattern
    for(int pos : positions_uncheck){

        flag = true;
        start_check = pos + k;

        for(int i = 0; i < pattern.size() - k; i++){
            // if reached the end of the string or the pattern does not match
            if(sequence[start_check + i] == string::npos || sequence[start_check + i] != pattern[k + i]){
                    flag = false;
                    break;
                }
        }

        if(flag)
            positions.push_back(pos);
        
    }

    return positions;
}




// Function to generate an index of substrings of length k from a given sequence
// The hash_table unordered_map substrings to the positions where they occur in the sequence
unordered_map<string, vector<int>> get_hash_table(const string& sequence, int k) {
    unordered_map<string, vector<int>> hash_table;
    string s;

    // Iterate through the sequence to create the index
    for (int i = 0; i < sequence.size() - k; i++) {
        s = sequence.substr(i, k);
        auto pos = hash_table.find(s);

        // Handle collisions by updating existing entries or inserting new ones
        if (pos != hash_table.end())
            pos->second.push_back(i);
        else
            hash_table.emplace_hint(pos, s, vector<int>{i});
    }

    return hash_table; // Return the generated hash table
} // get_hash_table