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
            case 0: codes.erase(codes.begin() + vec_size); break;
            case 1:
            {
                auto it = codes2.begin();
                advance(it, list_size);
                codes2.erase(it);
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

        /*    else if (j == 1) //Race 2: Sorting
            {
                if (i == 0) sort(codes.begin(), codes.end());
                else if (i == 1) codes2.sort();
                //Sets are already sorted, so that is already excluded
            }
            else if (j == 2) //Race 3: Inserting
            {
                //Define the middle value of the structures
                int middle = 0;
                string test_code = "TESTCODE";
                //Inserting at the middle of the vector
                if (i == 0)
                {
                    middle = (codes.size()) / 2;
                    auto it = codes.begin();
                    advance(it, middle);
                    codes.insert(it, test_code);
                }
                //Inserting at the middle of the list
                else if (i == 1)
                {
                    middle = (codes2.size()) / 2;
                    auto it = codes2.begin();
                    advance(it, middle);
                    codes2.insert(it, test_code);
                }
                //Since sets don't have options for inserting after or before positions
                //and the fact that it automatically sorts stuff out, just use insert()
                else if (i == 2) codes3.insert(test_code);
            }
            else if (j == 3) //Race 4: Deleting
            {
                //Define the middle value of the structures
                int middle = 0;
                //Remove the middle value of the vector
                if (i == 0)
                {
                    middle = (codes.size()) / 2;
                    auto it = codes.begin();
                    advance(it, middle);
                    codes.erase(it);
                }
                //Remove the middle value of the list
                else if (i == 1)
                {
                    middle = (codes2.size()) / 2;
                    auto it = codes2.begin();
                    advance(it, middle);
                    codes2.erase(it);
                }
                //Remove the middle value of the size
                else if (i == 2)
                {
                    middle = (codes3.size()) / 2;
                    auto it = codes3.begin();
                    advance(it, middle);
                    codes3.erase(it);
                }
            }
        }
        cout << endl;
    }*/
    
    ///Print everything
    string structs [] = { "Reading", "Sorting", "Inserting", "Deleting" };
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < SIZE; j++)
            cout << setw(WIDTH) << results[i][j] << " μs";
        cout << endl;
    }
    return 0;
}