import <iostream>;
import <fstream>;
import <string>;
import <memory>;

import Student;
import Board;
import Game;
import enum;

using namespace std;

int main(int argc, char** argv){

    numofPlayers = 4;
    string names[numofPlayers] = {"Blue", "Red", "Orange", "Yellow"};

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
                ++i;
            }
        } else if (argv[i] = "-board"){
            if (i + 1 < argc){
                boardfile = argv[i+1];
                ++i;
            }
        }
    }
    
    //Board board = Board(seed);
    unique_ptr<Board> board = make_unique<Board>(Board(seed));
    // default game
    vector<Student> players;
    for (int i = 0; i < numofPlayers; ++i){
        Student s = Student{names[i], board};
        players.emplace_back(s);
    }
    Game default_game = Game(*board, players);

    // setting up board and seed
    // update goose!

    if (loadfile != ""){
        while (true){
            cout << "Would like like to play on your loaded game or start a new game?[L/N] ";
            char response;
            cin >> response;
            if (response == 'L'){
                // read from file
                int cur_turn;
                ifstream ifsl{loadfile};
                getline(ifsl, cur_turn);
                vector<Student> players;
                for (int i = 0; i < numofPlayers; ++i){
                    string line;
                    getline(ifsl, line);
                    //playerColor pc = static_cast<playerColor>(i);
                    Student s = Student{names[i], board};
                    s.read_save_string(line);
                    players.emplace_back(s);
                }

                // can i put in a function
                vector<int> givenBoard;
                int temp;
                for (int i = 0; i < 38; ++i){
                    ifsl >> temp;
                    givenBoard.emplace_back(temp);
                }
                board->load_saveData(givenBoard);

                int goose;
                ifsl >> goose;
                board->updateGoose(goose);


                //////////////
                ///////////
                // not sure lol
                default_game = Game(*board, players, cur_turn);

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
                ifstream ifsl{loadfile};
                for (int i = 0; i < 38; ++i){
                    ifsl >> temp;
                    givenBoard.emplace_back(temp);
                }
                board->load_saveData(givenBoard);
                break;
            } else if (response == 'N'){
                // new game
                break;
            }
        }
    }
    


    // start game 

    Student * turnOrder[4] = {Blue, Red, Orange, Yellow};

    for (int i = 0; i < turnOrder.length(); ++i){
        cout << "Student " << // to_string(students[i]) 
        cout << ", where do you want to complete an Assignment?";
        int intersection;
        cin >> intersection;
        //studentcolor.accquire(intersection);
    }
    //backwards
    for (int i = (turnOrder.length - 1); i > 0; --i){
        cout << "Student " << // to_string(students[i]) 
        cout << ", where do you want to complete an Assignment?";
        int intersection;
        cin >> intersection;
        //studentcolor.accquire(intersection);
    }

    // printBoard();
    // start turn
    for (int i = 0; i < turnOrder.length(); ++i){
        cout << "Student " << //to_string(students[i]) << "'s turn.";
    }

}
