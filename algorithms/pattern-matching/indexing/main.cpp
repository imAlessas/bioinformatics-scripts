/* @imAlessas */

#include <bits/stdc++.h>

using namespace std;


// function definition

map<string, vector<int>> get_index(const string&, int);




int main() {

    // defines the source files
    const string sequence_file = "sequence-1000000.txt";
    const string pattern_file = "pattern-5.txt";

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



    // gets the index
    map<string, vector<int>> index = get_index(sequence, k);

    // prints the index
    for (const auto& bucket : index) {
        cout << bucket.first << endl << "     ";
        
        for(int value : bucket.second)
            cout << " " << value;

        cout << endl;
    }


    return 0;
} // main



// Function to generate an index of substrings of length k from a given sequence
// The index maps substrings to the positions where they occur in the sequence
map<string, vector<int>> get_index(const string& sequence, int k){

    map<string, vector<int>> index = {};

    string s;
    map<string, vector<int>> :: iterator pos;

    // Iterate through the sequence to create the index
    for(int i = 0; i < sequence.size() - k; i++) {
        s = sequence.substr(i, k);

        pos = index.find(s);

        // Handle collisions by updating existing entries or inserting new ones
        if (pos != index.end())
            index[s].push_back(i);
        else
            index.insert({s, {i}});
    }

    return index; // Return the generated index
} // get_index