import <iostream>;
import <fstream>;
import <string>;

import Student;

using namespace std;

int main(int argc, char** argv){

    int seed = 0; // default seed
    string loadfile = "";
    string boardfile = "";

    if (argc <= 1){
        // no arguments, use default
    } else {
        for (int i = 1; i < argc; i++){
            istringstream iss {argv[i]};
            string command;
            if (command == "-seed"){
                if (i + 1 < argc){
                    iss >> seed;
                    ++i;
                    // ============================================================
                    //  Randomizing our tiles
                    // ============================================================
                    unsigned seed_val = 69;
                    try {
                    seed_val = stoi(seed);
                    } catch(invalid_argument & e ) {
                    } catch(out_of_range & e ) {
                    }
                    default_random_engine rng{seed_val};
                }
            } else if (command == "-load"){
                if (i + 1 < argc){
                    iss >> loadfile;
                    ifstream ifsl{loadfile};
                    ++i;
                }
            } else if (command = "-board"){
                if (i + 1 < argc){
                    iss >> boardfile;
                    ifstream ifsb{boardfile};
                    ++i;
                }
            }
        }
    }


    // setting up board and seed

    if (loadfile != ""){
        // read from file
        // no board file
    } else if (boardfile != ""){
        // read from file
        // no load file

        // 19 tile resources + 19 tile values = 38
        int r;
        int value;
        for (int i = 0; i < 38; ++i){
            ifsb >> r;
            ifsb >> value;
            
            // reading conditions
            if (r == 0){
                //"CAFFEINE"
            } else if (r == 1){
                //"LAB",
            } else if (r == 2){
                //"LECTURE",
            } else if (r == 3){
                //"STUDY",
            } else if (r == 4){
                //"TUTORIAL",
            } else if (r == 5){
                //"NETFLIX"
                value = -1;
            }
        }
    }


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
