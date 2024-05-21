/* @imAlessas */

/*
    The vector<pattern, position> indexing technique uses the sequence-preporcessing to analyze and obtain the pattern positions in the sequence
    This approach uses more memory than the KMP-search and it is extremely less efficient time-wise even though the vector is sorted and the binary_search algorithm is used.
    To search in a 10 mln character sequence, the time needed is around 40 seconds (with the pattern length of 10)
*/

#include <bits/stdc++.h>

using namespace std;


// function definition

vector<int> find_pattern(const string&, const string&, vector<pair<string, int>>&, int);

vector<pair<string, int>> get_sorted_vector(const string&, int);



int main() {

    const string DATA_FOLDER_PATH = "../../../../data/";

    // defines the source files
    string sequence_file = "sequence-100000000.txt";
    string pattern_file = "pattern-10.txt";
    string output_file = "vector-indexing-output.txt";

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


    // gets vector
    vector<pair<string, int>> v = get_sorted_vector(sequence, k);

    // gets positions
    vector<int> positions = find_pattern(sequence, pattern, v, k);

    // calculates duration
    auto stop = chrono::high_resolution_clock::now();
    int duration = chrono::duration_cast<chrono::milliseconds>(stop - start).count();

    // ouputs duration and matches
    cout << endl << "Vector:" << endl;
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
vector<int> find_pattern(const string& sequence, const string& pattern, vector<pair<string, int>>& v, int k){

    // vector with all positions
    vector<int> positions = {};

    // first k chars of the pattern
    string pattern_subs = pattern.substr(0, k);

    // the vector will contain all the unchecked positions 
    vector<int> positions_uncheck = {};

    // finds the occurrencies using a binary_search
    // auto low = lower_bound(v.begin(), v.end(), pattern_subs);

    auto low = std::lower_bound(v.begin(), v.end(), pattern_subs, [](const std::pair<std::string, int>& p, const std::string& pattern) {
        return p.first < pattern;
    });

    positions_uncheck.push_back(low -> second);

    auto high = low + 1;

    // adds the possible positions
    while(low -> first == pattern_subs){
        positions_uncheck.push_back( low -> second);
        low--;
    }

    while(high -> first == pattern_subs){
        positions_uncheck.push_back( high -> second);
        high++;
    }



    // checks for the actual pattern, case where |k| < |pattern|
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
// The index vector<str, int> of substrings to the positions where they occur in the sequence
vector<pair<string, int>> get_sorted_vector(const string& sequence, int k){
    
    vector<pair<string, int>> v;
    string s;

    // populates the unsorted array
    for (int i = 0; i < sequence.size() - k; i++)
        v.push_back({sequence.substr(i, k), i});

    sort(v.begin(), v.end());

    return v;
} // get_sorted_vector
