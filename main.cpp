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
const int SIZE = 3, WIDTH = 10;

int main()
{
    vector<string> codes;
    list<string> codes2;
    set<string> codes3;

    string lines;
    string race;

    //Print out the Table's header
    cout << "Race" << setw(WIDTH/2) << "|" << setw(WIDTH) << "Vector" << setw(WIDTH) << "List" << setw(WIDTH) << "Set" << endl;
    for (int i = 0; i < 50; i++) cout << "-";
    cout << endl;

    //From there, start the chrono loops.
    for (int j = 0; j < 4; j++)
    {
        switch (j)
        {
            case 0: race = "Reading"; break;
            case 1: race = "Sorting"; break;
            case 2: race = "Inserting"; break;
            case 3: race = "Deleting"; break;
        }

        //Race 1: Reading
        cout << setw(WIDTH/2) << race << right << setw(WIDTH/2) << "|" << right;
        for (int i = 0; i < SIZE; i++)
        {
            //Start timing
            auto start = high_resolution_clock::now();

            if (j == 0) //Race 1: Reading
            {
                //Read the file input
                ifstream fin("codes.txt");
                if (fin.is_open())
                {
                    while (getline(fin, lines))
                    {
                        if (i == 0) codes.push_back(lines);
                        else if (i == 1) codes2.push_back(lines);
                        else if (i == 2) codes3.insert(lines);
                    }
                }
                else cout << "File not found" << endl;

                //Close the file input
                fin.close();
            }
            else if (j == 1) //Race 2: Sorting
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

            //End timing
            auto end = high_resolution_clock::now();

            //Compile the duration & print it

            auto duration = duration_cast<microseconds>(end - start);
            cout << setw(WIDTH) << duration.count() << " μs";
        }
        cout << endl;
    }
    
    return 0;
}