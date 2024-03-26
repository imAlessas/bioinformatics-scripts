/* @imAlessas */

/*
    Execution:
        g++ main.cpp -o main ; ./main suspects.txt dna_trace.txt
*/

#include <bits/stdc++.h>

using namespace std;


// function definition

vector<string> split_string(const string&, char);

vector<int> get_oracle(const string&);

vector<int> KMP_search(const string&, const string&, const vector<int>&);

int longest_STR(const string&, const string&);




int main(int argc, char* argv[]) {

    // initial inputs
    string suspects_file_name, sequence_file_name;

    if(argc == 3){
        suspects_file_name = argv[1];
        sequence_file_name = argv[2];
    } else {
        cout << endl << "\033[31m" << "Invalid input arguments." << "\033[37m" << endl << endl;
        return 1;
    }

    // check input
    cout << endl;
    cout << "Files: " << endl;
    cout << "     Suspects:    " << "\033[34m" << suspects_file_name << "\033[37m" << endl;
    cout << "     DNA:         " << "\033[34m" << sequence_file_name << "\033[37m" << endl;



    // defines input file(s)
    ifstream suspects_input("./dataset/" + suspects_file_name);
    ifstream sequence_input("./dataset/" + sequence_file_name);

    if (!suspects_input.is_open() || !sequence_input.is_open()) {
        cout << endl << "\033[31m" << "Error opening files." << "\033[37m" << endl << endl;
        return 1;
    }


    

    // gets STR values
    string STR_string;
    getline(suspects_input, STR_string);

    vector<string> STR_vector = split_string(STR_string, ' ');
    
    // removes 'name'
    STR_vector.erase(STR_vector.begin());


    // gets DNA sequence
    string sequence;
    getline(sequence_input, sequence);

    // start counting occurencies for all STRs
    vector<int> STR_occurrencies = {};

    for(string tandem : STR_vector) // for each tande, calculates longest STR
        STR_occurrencies.push_back(longest_STR(sequence, tandem));


    // checks ,atches with the suspects
    string suspect;
    vector<string> STR_detected;
    map<string, int> matches;

    while(getline(suspects_input, suspect)){
        STR_detected = split_string(suspect, ' ');

        suspect = STR_detected[0];

        matches.insert({suspect, 0});

        STR_detected.erase(STR_detected.begin());

        for(int i = 0; i < STR_detected.size(); i++){
            if(stoi(STR_detected[i]) == STR_occurrencies[i])
                matches[suspect] = matches[suspect] + 1;
        }
    }

    // prints the suspects
    cout << endl << endl << "Suspects: " << endl;
    string padding;

    for(pair<string, int> m : matches){
        padding = "";

        for(int i = 0; i < 13 - m.first.size(); i++)
            padding = padding + " ";

        if(m.second > 0)
             cout << "     >> \033[32m" << m.first << "\033[37m" << padding << "\033[31m\033[1m" << m.second << "\033[0m\033[37m /" << STR_detected.size() <<"  match(es)" << endl;
    }
    cout << endl;


    return 0;
} // main


//



// finds the longest short-tandem-repeat
int longest_STR(const string& sequence, const string& pattern){

    // gets all the patter occurrencies
    vector<int> positions = KMP_search(sequence, pattern, get_oracle(pattern));

    int begin = 0, longest = 0;
    
    // starts counting the STR
    for(int i = 0; i < positions.size() - 1; i++){
        begin = i;

        while( positions[i + 1] - positions[i] == pattern.size() ){
            i++;
        }
                
        if(i - begin > longest)
            longest = i - begin + 1;
    }

    return longest;
} // longest_STR




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




// This function splits a string in relation to the input token.
// The return value is a vector of substrings occurred when splitting the original string 
vector<string> split_string(const string& str, char tok){
    
    vector<string> fragments = {};
    int j = 0;

    // splits the string
    for (int i = 0; i < str.size(); i++)
        if (str[i] == tok){
            fragments.push_back(str.substr(j, i - j));
            j = i + 1;
        }
    
    // last fragment
    fragments.push_back(str.substr(j, str.size() - j));
    
    return fragments;
} // split_string



/*
    0.1% su un genoma di 3B di basi è comunque tanto. CI sono alcune regione del enoma in cui quesa diversità è evidente. Grazie alluso di pattern corti noti detti Short Tande Repeata. Il numero massimo di STR che noi riusciamo a distinguere [back2back, senza gap]
    Per ciasuna STR si ripete ugulmente nel DNA, si è quasi certi che si ha un'occorrenza.
*/ 