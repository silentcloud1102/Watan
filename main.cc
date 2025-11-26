import <iostream>;
import <fstream>;
import <string>;

import Student;
import Board;
import enum;

using namespace std;

int main(int argc, char** argv){

    int seed = 0; // default seed
    string loadfile = "";
    string boardfile = "";

    for (int i = 1; i < argc; i++){

        if (argv[i] == "-seed"){
            if (i + 1 < argc){
                istringstream iss {argv[i + 1]};
                iss >> seed;
                if (iss.fail()){
                    iss.clear();
                }
                ++i;
            }
        } else if (argv[i] == "-load"){
            if (i + 1 < argc){
                loadfile = argv[i+1];
                ifstream ifsl{loadfile};
                ++i;
            }
        } else if (argv[i] = "-board"){
            if (i + 1 < argc){
                boardfile = argv[i+1];
                ifstream ifsb{boardfile};
                ++i;
            }
        }
    }
    
    Board(seed);
    // setting up board and seed
    // update goose!

    if (loadfile != ""){
        while (true){
            cout << "Would like like to play on your loaded game or start a new game?[L/N] ";
            char response;
            cin >> response;
            if (response == 'L'){
                // read from file
                // no board file
                // vector<int> givenBoard;
                // int temp;
                // for (int i = 0; i < 38; ++i){
                //     ifsl >> temp;
                //     givenBoard.emplace_back(temp);
                // }
                // load_saveData(givenBoard);
                break;
            } else if (response == 'N'){
                // new game
                break;
            }
        }
    } else if (boardfile != ""){
        while (true){
            cout << "Would like like to play on your board or start a new game?[B/N] ";
            char response;
            cin >> response;
            if (response == 'B'){
                // read from file
                vector<int> givenBoard;
                int temp;
                for (int i = 0; i < 38; ++i){
                    ifsl >> temp;
                    givenBoard.emplace_back(temp);
                }
                load_saveData(givenBoard);
                break;
            } else if (response == 'N'){
                // new game
                break;
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
