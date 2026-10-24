//COMSC-210 | Lab 26 | Eric-Giulio Hedes
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
using namespace std;
using namespace std::chrono;

//Set up the global constants
const int SIZE = 3;
const int ROWS = 4, COLS = 3;
const int SIMULATIONS = 15;
const int WIDTH = 10;

int main()
{
    int results[ROWS][COLS];

    vector<string> codes;
    list<string> codes2;
    set<string> codes3;

    string lines;
    string race;

    int vec_size, list_size;
    string t = "TESTCODE";

    //From there, start the chrono loops.
    //Race 1: Reading
    for (int i = 0; i < SIZE; i++)
    {
        //Start timing
        auto start = high_resolution_clock::now();
        //Read the file input
        ifstream fin("codes.txt");
        if (fin.is_open())
        {
            switch (i)
            {
                case 0: while (getline(fin, lines)) codes.push_back(lines); break;
                case 1: while (getline(fin, lines)) codes2.push_back(lines); break;
                case 2: while (getline(fin, lines)) codes3.insert(lines); break;
            }
        }
        else cout << "File not found" << endl;

        //Close the file input
        fin.close();

        //End timing
        auto end = high_resolution_clock::now();

        //Compile the duration & put it to results
        auto duration = duration_cast<microseconds>(end - start);
        results[0][i] = duration.count();
    }

    //Set up the vec & list sizes for later
    vec_size = codes.size() / 2;
    list_size = codes2.size() / 2;

    //Race 2: Sorting
    for (int i = 0; i < SIZE; i++)
    {
        //Start timing
        auto start = high_resolution_clock::now();
        switch (i)
        {
            case 0: sort(codes.begin(), codes.end()); break;
            case 1: codes2.sort(); break;
        }

        //End timing
        auto end = high_resolution_clock::now();

        //Compile the duration & put it to results
        auto duration = duration_cast<microseconds>(end - start);
        if (i != 2) results[1][i] = duration.count();
        else results[1][i] = -1;
    }

    //Race 3: Inserting
    for (int i = 0; i < SIZE; i++)
    {
        //Start timing
        auto start = high_resolution_clock::now();
        switch (i)
        {
            case 0: codes.insert(codes.begin() + vec_size, t); break;
            case 1:
            {
                auto it = codes2.begin();
                advance(it, list_size);
                codes2.insert(it, t);
                break;
            }
            case 2: codes3.insert(t); break;
        }

        //End timing
        auto end = high_resolution_clock::now();

        //Compile the duration & put it to results
        auto duration = duration_cast<microseconds>(end - start);
        results[2][i] = duration.count();
    }

    //Race 4: Deleting
    for (int i = 0; i < SIZE; i++)
    {
        //Start timing
        auto start = high_resolution_clock::now();
        switch (i)
        {
            case 0: codes.erase(remove(codes.begin(), codes.end(), codes[vec_size])); break;
            case 1:
            {
                auto it = codes2.begin();
                advance(it, list_size);
                codes2.remove(*it);
                break;
            }
            case 2: codes3.insert(t); break;
        }

        //End timing
        auto end = high_resolution_clock::now();

        //Compile the duration & put it to results
        auto duration = duration_cast<microseconds>(end - start);
        results[3][i] = duration.count();
    }
    
    ///Print everything
    string datatypes [] = { "Vector", "List", "Set" };
    string structs [] = { "Reading", "Sorting", "Inserting", "Deleting" };
    cout << setw(WIDTH) << "Structures" << setw(WIDTH/2) << "|";
    for (int i = 0; i < SIZE; i++)
        cout << setw(WIDTH + 3) << datatypes[i] << setw(WIDTH/2);
    cout << endl;
    for (int i = 0; i < 50; i++)
        cout << "-";
    cout << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << setw(WIDTH) << structs[i] << setw(WIDTH/2) << "|";
        for (int j = 0; j < SIZE; j++)
            cout << setw(WIDTH) << results[i][j] << " μs";
        cout << endl;
    }
    return 0;
}