/* @imAlessas */

#include <bits/stdc++.h>

using namespace std;


// function definition

long MTP(vector<vector<array<int, 3>>>&);

vector<vector<array<int, 3>>> get_manhattan_grid(int, int, int);

void display_grid(const vector<vector<array<int, 3>>>&, const string&);




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
    vector<vector<array<int, 3>>> manhattan_grid = get_manhattan_grid(n, m, max);

    for(auto i : manhattan_grid)
        for(auto j : i)
            cout << j[0] << " " << j[1] << " " << j[2] << endl;

    // analyzes the grid
    long highest_score = 0;


    // calculates duration
    auto stop = chrono::high_resolution_clock::now();
    int duration = chrono::duration_cast<chrono::milliseconds>(stop - start).count();

    // ouputs duration
    cout << endl << "Manhattan Tourist Problem:" << endl;
    cout << "   Highest Score:   " << "\033[1m\033[33m" << highest_score << "\033[37m \033[0m" << endl;
    cout << "   Duration:        " << "\033[34m" << duration << " ms" << "\033[37m" << endl << endl;

    // display_grid(manhattan_grid.first, manhattan_grid.second, output_file);

    return 0;
}


// generates manhattan grid given the rows, cols and max value per edge
vector<vector<array<int, 3>>> get_manhattan_grid(int n, int m, int max) {

    vector<vector<array<int, 3>>> grid(n, vector<array<int, 3>>(m));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            
            // fills the horizontal (i - 1, j) edge
            grid[i][j][0] = rand() % max;

            // fills the vertical (i, j - 1) edge
            grid[i][j][1] = rand() % max;

            //  fils the diagonal (i - 1, j - 1) edge
            if(rand() % 2)
                grid[i][j][2] = rand() % max;
            else
                grid[i][j][2] = 0;
        }
    }

    return grid;

} // get_manhattan_grid




// gets the highest score obtained by the optimal path through the gird
long MTP(vector<vector<array<int, 3>>>& grid) {

    int rows = grid.size();
    int cols = grid[0].size();

    vector<vector<int>> highest_scores(rows, vector<int>(cols));

    // TODO

    return highest_scores[0][0];
} // MTP


void display_grid(const vector<vector<array<int, 3>>>& grid, const string& output_file) {
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

    output.close();
    system(("start " + output_file).c_str());
}