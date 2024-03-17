/* @imAlessas */

#include <bits/stdc++.h>
#include "../generate-data/generator.cpp"

using namespace std;

// function definition
vector<int> get_oracle(const string&);

vector<int> KMP_search(const string&, const string&, const vector<int>&);


int main() {
    // generates data
    generate_DNA_sequence(100000);


    // uses file to address input and output
    ifstream input("input.txt");
    ofstream output("output.txt");

    if (!input.is_open() || !output.is_open()) {
        cout << "Error opening files." << endl;
        return 1;
    }

    string sequence, pattern;
    getline(input, sequence);
    // getline(input, pattern);
    pattern = "ATGTG";

    // obtains oracle table
    vector<int> oracle = get_oracle(pattern);

    auto start = chrono::high_resolution_clock::now();
    
    // performs KMP-search
    vector<int> positions = KMP_search(sequence, pattern, oracle);

    // calculates duration
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);

    // ouputs duration and matches
    cout << endl << "KMP-search:  " << duration.count() << " ms" << endl;
    cout << "             " << positions.size() << " match(es)" << endl << endl;

    // writes the indexes
    for (int i : positions)
        output << i << endl;

    input.close();
    output.close();

    // opens output file
    system("start output.txt");

    return 0;
} // main




// implementation of Knuth–Morris–Pratt algorithm
vector<int> KMP_search(const string& sequence, const string& pattern, const vector<int>& oracle) {
    int j = 0, k = 0;
    vector<int> positions;

    while (j < sequence.size()) {
        if (pattern[k] == sequence[j]) {
            j++;
            k++;

            if (k == pattern.size()) {
                positions.push_back(j - k);
                k = oracle[k - 1];
            }

        } else {
            if(k)
                k = oracle[k - 1];
            else
                j++; 
        }
    }

    return positions;
} //  KMP_search




// oracle (lookup table) implementation
vector<int> get_oracle(const string& pattern) {
    int i = 0;
    vector<int> oracle(pattern.size());

    for (int j = 1; j < pattern.size(); j++) {
        while (i > 0 && pattern[i] != pattern[j])
            i = oracle[i - 1];
        
        if (pattern[i] == pattern[j])
            i++;
        
        oracle[j] = i;
    }

    return oracle;
} // get_oracle
