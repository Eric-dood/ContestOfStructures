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

//Start of main()
int main()
{
    //Define 3D-Array
    int results[ROWS][COLS][SIMULATIONS];

    //Define the statistic codes
    vector<string> codes;
    list<string> codes2;
    set<string> codes3;

    //Define the lines (which will be used for Race 1)
    string lines;

    //Define both middle values and the "TESTCODE" string (which will be used for Race 3 & 4)
    int vec_mid, list_mid;
    string t = "TESTCODE";

    //From there, start the chrono loops.
    for (int x = 0; x < SIMULATIONS; x++)
    {
        //Race 1: Reading
        for (int i = 0; i < SIZE; i++)
        {
            //Start timing
            auto start = high_resolution_clock::now();
            //Read the file input
            ifstream fin("codes.txt");
            if (fin.is_open())
            {
                //Depending on the i value, use the appropriate function for each data strucutre
                switch (i)
                {
                    case 0: while (getline(fin, lines)) codes.push_back(lines); break;
                    case 1: while (getline(fin, lines)) codes2.push_back(lines); break;
                    case 2: while (getline(fin, lines)) codes3.insert(lines); break;
                }
            }
            //If the file is empty, print an error message
            else cout << "File not found" << endl;

            //Close the file input
            fin.close();

            //End timing
            auto end = high_resolution_clock::now();

            //Compile the duration & put it to results
            auto duration = duration_cast<microseconds>(end - start);
            results[0][i][x] = duration.count();
        }

        //Set up the vec & list sizes for later
        vec_mid = codes.size() / 2;
        list_mid = codes2.size() / 2;

        //Race 2: Sorting
        for (int i = 0; i < SIZE; i++)
        {
            //Start timing
            auto start = high_resolution_clock::now();
            switch (i)
            {
                //Depending on the i value, use the appropriate function for each data strucutre
                case 0: sort(codes.begin(), codes.end()); break;
                case 1: codes2.sort(); break;
                //std::set does not have a sort function, so it naturally does nothing
            }

            //End timing
            auto end = high_resolution_clock::now();

            //Compile the duration & put it to results
            auto duration = duration_cast<microseconds>(end - start);
            //If i is equal to 2 (which is the number for the set), set the value to -1
            results[1][i][x] = (i != 2) ? duration.count() : -1;
        }

        //Race 3: Inserting
        for (int i = 0; i < SIZE; i++)
        {
            //Start timing
            auto start = high_resolution_clock::now();
            switch (i)
            {
                //Depending on the i value, use the appropriate function for each data strucutre
                case 0: codes.insert(codes.begin() + vec_mid, t); break;
                case 1:
                {
                    //Define it
                    auto it = codes2.begin();
                    //Move to list_mid
                    advance(it, list_mid);
                    //Then insert it
                    codes2.insert(it, t);
                    break;
                }
                case 2: codes3.insert(t); break;
            }

            //End timing
            auto end = high_resolution_clock::now();

            //Compile the duration & put it to results
            auto duration = duration_cast<microseconds>(end - start);
            results[2][i][x] = duration.count();
        }

        //Race 4: Deleting
        for (int i = 0; i < SIZE; i++)
        {
            //Start timing
            auto start = high_resolution_clock::now();
            switch (i)
            {
                //Depending on the i value, use the appropriate function for each data strucutre
                case 0: codes.erase(remove(codes.begin(), codes.end(), codes[vec_mid])); break;
                case 1:
                {
                    //Define it
                    auto it = codes2.begin();
                    //Move to list_mid
                    advance(it, list_mid);
                    //Then remove the it value
                    codes2.remove(*it);
                    break;
                }
                case 2: codes3.insert(t); break;
            }

            //End timing
            auto end = high_resolution_clock::now();

            //Compile the duration & put it to results
            auto duration = duration_cast<microseconds>(end - start);
            results[3][i][x] = duration.count();
        }
    }
    
    ///Print everything
    string datatypes [] = { "Vector", "List", "Set" };
    string structs [] = { "Reading", "Sorting", "Inserting", "Deleting" };
    cout << "Number of simulations: " << SIMULATIONS << endl;
    cout << setw(WIDTH) << "Operation" << setw(WIDTH/2) << "|";
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