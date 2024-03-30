/* @imAlessas */

#include <bits/stdc++.h>

using namespace std;


// function definition

long MTP(vector<vector<int>>&, vector<vector<int>>&);

pair<vector<vector<int>>, vector<vector<int>>> get_manhattan_grid(int, int, int);

void display_grid(vector<vector<int>>&, vector<vector<int>>&, const string&);




int main() {

    const string output_file = "manhattan-grid.txt";

    // sets up the input values
    int n, m, max;

    cout << endl << "Type the dimension of the Manhattan Grid" << endl;

    cout << "    Rows: ";
    cin >> n;

    cout <<  "    Cols: ";
    cin >> m;

    cout << endl << "What is the maximum value per edge? ";
    cin >> max;
    cout << endl;



    auto start = chrono::high_resolution_clock::now();
    
    // creates the grid
    pair<vector<vector<int>>, vector<vector<int>>> manhattan_grid = get_manhattan_grid(n, m, max);

    // analyzes the grid
    long highest_score = MTP(manhattan_grid.first, manhattan_grid.second);


    // calculates duration
    auto stop = chrono::high_resolution_clock::now();
    int duration = chrono::duration_cast<chrono::milliseconds>(stop - start).count();

    // ouputs duration
    cout << endl << "Manhattan Tourist Problem:" << endl;
    cout << "   Highest Score:   " << "\033[1m\033[33m" << highest_score << "\033[37m \033[0m" << endl;
    cout << "   Duration:        " << "\033[34m" << duration << " ms" << "\033[37m" << endl << endl;

    display_grid(manhattan_grid.first, manhattan_grid.second, output_file);

    return 0;
}


// generates manhattan grid given the rows, cols and max value per edge
pair<vector<vector<int>>, vector<vector<int>>> get_manhattan_grid(int n, int m, int max) {

    vector<vector<int>> down(n, vector<int>(m - 1));
    vector<vector<int>> right(n - 1, vector<int>(m));

    // Populate the down vector with random values
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++) {
            down[i][j] = rand() % max;
        }
    }

    // Populate the right vector with random values
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            right[i][j] = rand() % max;
        }
    }
    
    return {down, right};
} // get_manhattan_grid




// gets the highest score obtained by the optimal path through the gird
long MTP(vector<vector<int>>& down, vector<vector<int>>& right) {

    int n = down.size();
    int m = right.size();

    // creates a 2D vector containing "n + 1" vectors, each of them with "m + 1" values, all 0s
    vector<vector<long>> highest_scores(n + 1, vector<long>(m + 1, 0));

    // Initialize the first row and column
    for (int i = 1; i <= n; i++) {
        highest_scores[i][0] = highest_scores[i - 1][0] + down[i - 1][0];
    }
    for (int j = 1; j <= m; j++) {
        highest_scores[0][j] = highest_scores[0][j - 1] + right[0][j - 1];
    }


    // Fill the rest of the table
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            highest_scores[i][j] = max(highest_scores[i - 1][j] + down[i - 1][j - 1], highest_scores[i][j - 1] + right[i - 1][j - 1]);
        }
    }

    return highest_scores[n - 1][m - 1];
} // MTP


void display_grid(vector<vector<int>>& down, vector<vector<int>>& right, const string& output_file) {
    ofstream output(output_file);

    /*  Reference graphics
        ■────n────■────n────■────n────■
        │         │         │         │
        n         n         n         n
        │         │         │         │
        ■────n────■────n────■────n────■
        │         │         │         │
        n         n         n         n
        │         │         │         │
        ■────n────■────n────■────n────■
        │         │         │         │
        n         n         n         n
        │         │         │         │
        ■────n────■────n────■────n────■
    */

    // TODO
    int n = down.size();
    int m = down[0].size() + 1;

    // Print the grid
    for (int i = 0; i <= n; i++) {
        // Print the top row
        output << "        ■";
        for (int j = 0; j < m - 1; j++) {
            output << "───" << down[i][j] << "───■";
        }
        output << "\n";

        // Print the middle row
        output << "       │";
        for (int j = 0; j < m - 1; j++) {
            output << "       │";
        }
        output << "       │\n";

        // Print the bottom row
        output << "       │";
        for (int j = 0; j < m - 1; j++) {
            if (i < n) {
                output << right[i][j] << "       │";
            } else {
                output << "       │";
            }
        }
        output << "\n";

        // Print the middle row
        output << "       │";
        for (int j = 0; j < m - 1; j++) {
            output << "       │";
        }
        output << "       │\n";
    }

    // Print the bottom row
    output << "        ■";
    for (int j = 0; j < m - 1; j++) {
        output << "───■";
    }
    output << "\n";

    output.close();
    system(("start " + output_file).c_str());
}