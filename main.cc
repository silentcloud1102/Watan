import <iostream>;
import <fstream>;
import <string>;
import <memory>;

import Student;
import Board;
import Game;

using namespace std;

int main(int argc, char** argv){
    int numofPlayers = 4;

    int seed = 0; // default seed
    bool load = false;
    bool board = false;
    bool colour = true;

    string loadfile;
    string boardfile;

    // Argument-line parsing;
    for (int i = 1; i < argc; i++){

        if (string(argv[i]) == "-seed"){
            if (i + 1 < argc){
                istringstream iss {argv[i + 1]};
                iss >> seed;
                if (iss.fail()){
                    cerr << "Error: Seed could not be read, must be integer value." << endl;
                    return 1; 
                }
                ++i;
            } else {
                cerr << "Error: Provide seed after -seed argument!" << endl;
                return 1;
            }
        } else if (string(argv[i]) == "-load"){
            if (i + 1 < argc){
                loadfile = argv[i+1];
                ++i;
            } else {
                cerr << "Error: Provide filename after -load argument!" << endl;
                return 1;
            }
            load = true;
        } else if (string(argv[i]) == "-board"){
            if (i + 1 < argc){
                boardfile = argv[i+1];
                ++i;
            } else {
                cerr << "Error: Provide filename after -board argument!" << endl;
                return 1;
            }

            board = true;
        } else if (string(argv[i]) == "-colour"){
            if(i + 1 < argc){
                if(argv[i+1] == "true"){
                    colour = true;
                } else if(argv[i+1] == "false") {
                    colour = false;
                } else {
                    cerr << "Error: Provide true/false after -colour argument!" << endl;
                    return 1;
                }
            } else {
                cerr << "Invalid arguments structure." << endl;
                return 1;
            }
        }
    }

    if(board && load){
        cerr << "Error: Invalid combination!" << endl;
        return 1;
    }


    bool play_again = true;
    while (play_again){
        Game game = Game(seed, colour);

        if (load){
            while (true){
                cout << "Would you like to play on your loaded game or start a new game?[L/N]" << endl << ">";
                char response;
                cin >> response;
                if (cin.eof()){
                    cerr << "Program ended via EOF." << endl;
                    return 1;
                }
                if (response == 'L'){
                    ifstream ifsl{loadfile};
                    game.load_game(ifsl);
                    break;
                } else if (response == 'N'){
                    // new game
                    break;
                }
            }
        } else if (board){
            while (true){
                cout << "Would you like to play on your board or start a new game?[B/N]" << endl << ">";
                char response;
                cin >> response;
                if (cin.eof()){
                    cerr << "Program ended via EOF." << endl;
                    return 1;
                }
                if (response == 'B'){
                    ifstream ifsb{boardfile};
                    game.board_from_file(ifsb);
                    break;
                } else if (response == 'N'){
                    // new game
                    break;
                }
            }
        }
        

        // start game 
        if(!load){
            cout << 1;
            // starting at cur_turn 0.
            game.setup(cout, cin);
        }
        
        cout << game;

        bool playing_game = true;

        while (!game.has_won(cout)){
            string command;

            if (cin.eof()){
                game.save("backup.sv", cout);
                cerr << "Program ended via EOF. backup.sv created." << endl;
                return 1;
            }
            game.begin_turn(cout);
            // Then proceed to dice roll logic...
            game.roll_dice(cout, cin);

            while (cout << ">", cin >> command){
                if (command == "board"){
                    game.board(cout);
                } else if (command == "status"){
                    game.status(cout);
                } else if (command == "criteria"){
                    game.criteria(cout);
                } else if (command == "achieve"){
                    int goal;
                    cin >> goal;
                    game.achieve(goal, cout);
                } else if (command == "complete"){
                    int criteria;
                    cin >> criteria;
                    game.complete(criteria, cout);
                } else if (command == "improve"){
                    int criteria;
                    cin >> criteria;
                    game.improve(criteria, cout);
                } else if (command == "trade"){
                    string colour;
                    string give_r;
                    string take_r;
                    cin >> colour >> give_r >> take_r;
                    if (give_r != "CAFFEINE" && give_r != "LAB" && give_r != "LECTURE" && 
                        give_r != "STUDY" && give_r != "TUTORIAL") {
                        cout << "Please resources in the form: CAFFEINE, LAB, LECTURE, STUDY, TUTORIAL" << endl;
                        continue;
                    }
                    if (take_r != "CAFFEINE" && take_r != "LAB" && take_r != "LECTURE" && 
                        take_r != "STUDY" && take_r != "TUTORIAL") {
                        cout << "Please resources in the form: CAFFEINE, LAB, LECTURE, STUDY, TUTORIAL" << endl;
                        continue;
                    }
                    game.trade(colour, give_r, take_r, cout, cin);
                    
                } else if (command == "next"){
                    game.next_turn(cout);
                    break;
                } else if (command == "save"){
                    string filename;
                    cin >> filename;
                    game.save(filename, cout);
                } else if (command == "help"){
                    game.help(cout);
                } else {
                    cout << "Invalid command." << endl;
                }
                if (game.has_won(cout)) break;
            }
        } 

        while (true){
            cout << "Would you like to play again? [yes/no]" << endl << ">";
            string ans;
            cin >> ans;
            if (cin.eof()){
                    cerr << "Program ended via EOF." << endl;
                    return 1;
            }
            if (ans == "yes"){
                play_again = true;
                break;
            } else if (ans == "no"){
                play_again = false;
                break;
            }
        }
    }
}
