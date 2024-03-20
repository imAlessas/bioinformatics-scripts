#include <bits/stdc++.h>

using namespace std;

// function definition
void generate(long long m, const string& file_name);


/*
    Generates .txt files containing random generated data.
    Estimated execution time: ~ 15 minutes
    Estimated total files size: ~ 4 GB
*/
int main(){
    /*
        Convention for file name:
            "type-length.extension"
    */

    long long length;
    string type, extension, file_name;


    /* --- PATTERN --- */


    // generates a pattern of 5 characters
    length = 5;
    type = "pattern";
    extension = ".txt";

    file_name = type + "-" + to_string(length) + extension;
    generate(length, file_name);



    // generates a pattern of 10 characters
    length = 10;
    type = "pattern";
    extension = ".txt";

    file_name = type + "-" + to_string(length) + extension;
    generate(length, file_name);



    // generates a pattern of 20 characters
    length = 20;
    type = "pattern";
    extension = ".txt";

    file_name = type + "-" + to_string(length) + extension;
    generate(length, file_name);



    // generates a pattern of 30 characters
    length = 30;
    type = "pattern";
    extension = ".txt";

    file_name = type + "-" + to_string(length) + extension;
    generate(length, file_name);



    // generates a pattern of 50 characters
    length = 50;
    type = "pattern";
    extension = ".txt";

    file_name = type + "-" + to_string(length) + extension;
    generate(length, file_name);



    // generates a pattern of 100 characters
    length = 100;
    type = "pattern";
    extension = ".txt";

    file_name = type + "-" + to_string(length) + extension;
    generate(length, file_name);

    



    /* --- SEQUENCE --- */

    // generates a sequence of 10k characters
    length = 10000;
    type = "sequence";
    extension = ".txt";

    file_name = type + "-" + to_string(length) + extension;
    generate(length, file_name);



    // generates a sequence of 100k characters
    length = 100000;
    type = "sequence";
    extension = ".txt";

    file_name = type + "-" + to_string(length) + extension;
    generate(length, file_name);



    // generates a sequence of 1M characters
    length = 1000000;
    type = "sequence";
    extension = ".txt";

    file_name = type + "-" + to_string(length) + extension;
    generate(length, file_name);



    // generates a sequence of 10M characters
    length = 10000000;
    type = "sequence";
    extension = ".txt";

    file_name = type + "-" + to_string(length) + extension;
    generate(length, file_name);



    // generates a sequence of 100M characters
    length = 100000000;
    type = "sequence";
    extension = ".txt";

    file_name = type + "-" + to_string(length) + extension;
    generate(length, file_name);



    // generates a sequence of 1B characters
    length = 1000000000;
    type = "sequence";
    extension = ".txt";

    file_name = type + "-" + to_string(length) + extension;
    generate(length, file_name);



    // generates a sequence of 3.2B characters
    length = 3200000000;
    type = "sequence";
    extension = ".txt";

    file_name = type + "-" + to_string(length) + extension;
    generate(length, file_name);




    return 0;
} // main


// creates or modifies a file named "file_name" with a sequence of m characters representing a random sequence of DNA
void generate(long long m, const string& file_name){
    auto start = chrono::high_resolution_clock::now();
    
    ofstream output(file_name);

    while (m--) {
        switch ((rand() % 4) + 1)
        {
        case 1:
            output << "A";
            break;
        case 2:
            output << "C";
            break;
        case 3:
            output << "G";
            break;
        case 4:
            output << "T";
            break;
        }
    }

    output << endl;
    output.close();

    auto duration = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count();

    // outputs the creations stats
    string spaces = "";
    for(int i = file_name.size(); i < 35; i++)
        spaces += " ";
    
    cout << file_name << spaces << duration << endl;
} // generate