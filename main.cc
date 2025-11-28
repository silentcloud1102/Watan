import <iostream>;
import <fstream>;
import <string>;
import <memory>;

import Student;
import Board;
import Game;

using namespace std;

int main(int argc, char** argv){
    int numofPlayers;

    int seed = 0; // default seed
    bool load = false;
    bool board = false;

    string loadfile;
    string boardfile;

    // Argument-line parsing;
    for (int i = 1; i < argc; i++){

        if (to_string(argv[i]) == "-seed"){
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
        } else if (string(argv[i]) = "-board"){
            if (i + 1 < argc){
                boardfile = argv[i+1];
                ++i;
            } else {
                cerr << "Error: Provide filename after -board argument!" << endl;
                return 1;
            }

            board = true;
        }
    }

    if(board && load){
        cerr << "Error: Invalid combination!" << endl;
        return 1;
    }


    bool play_again = true;
    while (play_again){
        Game game = Game(seed);

        if (load){
            while (true){
                cout << "Would like like to play on your loaded game or start a new game? [L/N]" << endl << ">";
                char response;
                cin >> response;
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
                cout << "Would like like to play on your board or start a new game? [B/N]" << endl << ">";
                char response;
                cin >> response;
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
            // starting at cur_turn 0.
            game.setup()
        }
        
        cout << game;

        bool playing_game = true;

        while (game.has_won()){
            string command;

            game.new_turn();

            while (cout << ">", cin >> command){
                if (cin.eof()){
                    game.save("backup.sv");
                    cerr << "Program ended via EOF. backup.sv created." << endl;
                    return 1;
                }

                if (command == "board"){
                    game.board();
                } else if (command == "status"){
                    game.status();
                } else if (command == "criteria"){
                    game.criteria();
                } else if (command == "achieve"){
                    int goal;
                    cin >> goal;
                    game.achieve(goal);
                } else if (command == "complete"){
                    int criteria;
                    cin >> criteria;
                    game.complete(criteria);
                } else if (command == "improve"){
                    int criteria;
                    cin >> criteria;
                    game.improve(criteria);
                } else if (command == "trade"){
                    string colour;
                    string give_r;
                    string take_r;
                    cin >> colour >> give_r >> take_r;
                    game.trade(colour, give_r, take_r);
                    
                } else if (command == "next"){
                    game.next_turn();
                    break;
                } else if (command == "save"){
                    string filename;
                    cin >> filename;
                    game.save(filename);
                } else if (command == "help"){
                    game.help();
                } else {
                    cout << "Invalid command." << endl;
                }
            }
        } 

        while (true){
            cout << "Would you like to play again?[yes/no]" << endl << ">";
            string ans;
            cin >> ans;
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
