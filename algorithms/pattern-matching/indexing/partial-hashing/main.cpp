/* @imAlessas */

/*
    The partial hashing approach is a generalizaton of the hash-table approach. Instead of indexing a k-mer at every position of the sequence, we define an offset, that generally is k, and we read the k-mer in that position. Then, when the index is filled, we take all the possible offsets (n % k) in the pattern and we check the index. So if k = 3, we take on 3-mer of the pattern with offset 0, one 3-mer with offset one and one 3-mer with offset 2.
    This guarantess a better memory performance and a better time complexity than the hash table approach. This is because the time complexity of building the index is better than the hash table due to the jumps
*/


#include <bits/stdc++.h>

using namespace std;


// function definition

vector<int> find_pattern(const string& sequence, const string& pattern, unordered_map<string, vector<int>>& table, int k);

bool check_position(int sequence_idx, int pattern_idx, int k, const string& pattern, const string& sequence);

unordered_map<string, vector<int>> get_hash_table(const string& sequence, int k);




int main() {

    const string DATA_FOLDER_PATH = "../../../../data/";

    // defines the source files
    const string sequence_file = "sequence-10000000.txt";
    const string pattern_file = "pattern-20.txt";
    const string output_file = "partial-hashing-indexing-output.txt";

    const int K = 5;
    


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
    unordered_map<string, vector<int>> hash_table = get_hash_table(sequence, K);

    // gets positions
    vector<int> positions = find_pattern(sequence, pattern, hash_table, K);


    // calculates duration
    auto stop = chrono::high_resolution_clock::now();
    int duration = chrono::duration_cast<chrono::milliseconds>(stop - start).count();

    // ouputs duration and matches
    cout << endl << "Partial Hashing:" << endl;
    cout << "   Matches:    " << "\033[1m \033[33m" << positions.size() << "\033[37m \033[0m" << endl;
    cout << "   Duration:   " << "\033[34m" << duration << " ms" << "\033[37m" << endl << endl;


    // writes the indexes
    output << "Total Postions: " << positions.size() << endl << endl;
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

    // iterates throught the possible offsets of k
    for(int i = 0; i < k; i++){

        // extracts pattern[ i : i + k ]
        string pattern_subs = pattern.substr(i, k);

        // gets all the positions
        vector<int> positions_uncheck = table[pattern_subs];

        for(int pos : positions_uncheck)
            if(check_position(pos, i, k, pattern, sequence))
                positions.push_back(pos);

    }
    
    return positions;
} // find_pattern



// Checks if the position is the beginning of a pattern occurrency         
bool check_position(int sequence_idx, int pattern_idx, int k, const string& pattern, const string& sequence){

    int start_check = sequence_idx - pattern_idx;

    for(int i = 0; i < pattern.size(); i++){

        // skip the k position in the middle because already checked with the hash table
        if(i == pattern_idx)
            i += k;

        // if reached the end of the string or the pattern does not match
        if(sequence[start_check + i] == string::npos || sequence[start_check + i] != pattern[i])
            return false;
    }

    return true;
} // check_position



// Create and index by memorizing all the k-mers that are in a position multple of k-1
unordered_map<string, vector<int>> get_hash_table(const string& sequence, int k) {
    unordered_map<string, vector<int>> hash_table;
    string s;

    // Iterate through the sequence to create the index
    for (int i = 0; i < sequence.size(); i += k) {
        s = sequence.substr(i, k);
        auto pos = hash_table.find(s);  // O(1)

        // Handle collisions by updating existing entries or inserting new ones
        if (pos != hash_table.end())
            pos->second.push_back(i);
        else
            hash_table.emplace_hint(pos, s, vector<int>{i});
    }

    return hash_table;
} // get_hash_table
