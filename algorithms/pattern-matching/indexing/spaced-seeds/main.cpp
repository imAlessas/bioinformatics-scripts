/* @imAlessas */

/*
    The spaced seeds approach is not designed for high computational capabilities but rather to handle the intrinsic variance of nature. This is indeed the slowest index-based algorithm but provides more versatilty by obsuring some position of the pattern using a mask. In a sense this might look like the first hint that will lead us to the profile matching algorithms,
*/


#include <bits/stdc++.h>

using namespace std;


// function definition

vector<int> find_pattern(const string&, unordered_map<string, vector<int>>&, const string&);

unordered_map<string, vector<int>> get_hash_table(const string&, const string&);

string get_seed(const string&, const string&);




int main() {

    const string DATA_FOLDER_PATH = "../../../../data/";

    // defines the source files
    const string sequence_file = "sequence-10000000.txt";
    const string pattern_file = "pattern-10.txt";
    const string output_file = "spaced-seeds-indexing-output.txt";

    const string mask = "1110001011";


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

    if( pattern.size() != mask.size() ) {
        cout << endl << "          \033[31m" << "Pattern and mask must be the same size." << "\033[37m" << endl << endl;
        return 1;
    }

    auto start = chrono::high_resolution_clock::now();


    // gets hash_table
    unordered_map<string, vector<int>> hash_table = get_hash_table(sequence, mask);

    // gets positions
    vector<int> positions = find_pattern(pattern, hash_table, mask);


    // calculates duration
    auto stop = chrono::high_resolution_clock::now();
    int duration = chrono::duration_cast<chrono::milliseconds>(stop - start).count();

    // ouputs duration and matches
    cout << endl << "Spaced seeds:" << endl;
    cout << "   Matches:    " << "\033[1m \033[33m" << positions.size() << "\033[37m \033[0m" << endl;
    cout << "   Duration:   " << "\033[34m" << duration << " ms" << "\033[37m" << endl << endl;


    // writes the indexes
    output << "Total occurrencies: " << positions.size() << endl << endl;
    for (int i : positions)
        output << i << endl;

    input_sequence.close();
    input_pattern.close();
    output.close();

    // opens output file
    
    system(("start " + output_file).c_str());


    return 0;
} // main




// This function returns all the positions of the masked pattern by analyzing the hash_table
vector<int> find_pattern(const string& pattern, unordered_map<string, vector<int>>& hash_table, const string& mask){
    return hash_table[get_seed(pattern, mask)];
} // find_pattern




// Create and index by memorizing all the k-mers masks
unordered_map<string, vector<int>> get_hash_table(const string& sequence, const string& mask) {
    unordered_map<string, vector<int>> hash_table;
    string s;

    // Iterate through the sequence to create the index
    for (int i = 0; i < sequence.size(); i++) {
        s = sequence.substr(i, mask.size());
        s = get_seed(s, mask);

        auto pos = hash_table.find(s);  // O(1)

        // Handle collisions by updating existing entries or inserting new ones
        if (pos != hash_table.end())
            pos->second.push_back(i);
        else
            hash_table.emplace_hint(pos, s, vector<int>{i});
    }

    return hash_table;
} // get_hash_table



// masks the kmer
string get_seed(const string& kmer, const string& mask){

    string spaced_seed = "";

    for(int i = 0; i < mask.size(); i++)
        if(mask[i] == '1')
            spaced_seed += std::string(1, kmer[i]);

    return spaced_seed;
} // get_seed