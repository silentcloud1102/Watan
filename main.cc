import <iostream>;
import <fstream>;
import <string>;

import Student;

using namespace std;

int main(int argc, char** argv){

    if (argc <= 1){
        // no arguments;
    }

    istringstream iss {argv[1]};
    string command;
    while (iss >> command){
        if (command == "-seed"){
            int seed;
            iss >> seed;
            // ============================================================
            //  Randomizing our tiles
            // ============================================================
            unsigned seed_val = 69;
            try {
            seed_val = stoi(seed);
            } catch( invalid_argument & e ) {
            } catch(out_of_range & e ) {
            }
            default_random_engine rng{seed_val};        
        } else if (command == "-load"){
            string loadfile;
            iss >> loadfile;
            ifstream ifsl{loadfile};
        } else if (command = "-board"){
            string boardfile;
            iss >> boardfile;
            ifstream ifsb{boardfile};
        }
    }

    int seed = 0; // default seed
    string loadfile = "";
    string boardfile = "";



    // start game

    Student Blue;
    Student Red;
    Student Orange;
    Student Yellow;

    Student * turnOrder[4] = {Blue, Red, Orange, Yellow};

    for (int i = 0; i < turnOrder.length(); ++i){
        cout << "Student " << // to_string(students[i]) 
        cout << ", where do you want to complete an Assignment?";
        int intersection;
        cin >> intersection;
        //studentcolor.accquire(intersection);
    }
    // only one direction right now, can do recursion but would need to make a function?
    // is that ok in main, (design wise)
    
    // printBoard();


    // start turn
    for (int i = 0; i < turnOrder.length(); ++i){
        cout << "Student " << //to_string(students[i]) << "'s turn.";
    }

}
