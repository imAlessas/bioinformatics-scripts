#include <bits/stdc++.h>

using namespace std;

void generate_DNA_sequence(long long m){
    ofstream output("input.txt");

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
}