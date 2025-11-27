import <iostream>;
import <fstream>;
import <string>;
import <memory>;

import Student;
import Board;
import Game;

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
                ++i;
            }
        } else if (argv[i] = "-board"){
            if (i + 1 < argc){
                boardfile = argv[i+1];
                ++i;
            }
        }
    }
    
    
    Game default_game = Game(seed);

    if (loadfile != ""){
        while (true){
            cout << "Would like like to play on your loaded game or start a new game?[L/N] ";
            char response;
            cin >> response;
            if (response == 'L'){
                ifstream ifsl{loadfile};
                default_game.loadGame(ifsl);
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
                ifstream ifsb{boardfile};
                default_game.updateBoard(ifsb);
                break;
            } else if (response == 'N'){
                // new game
                break;
            }
        }
    }
    


    // start game 
    
    // Student * turnOrder[4] = {Blue, Red, Orange, Yellow};
    // magic numbers!!! make numof players field in game?

    for (int i = 0; i < 4; ++i){
        cout << "Student " << default_game.players[i].get_name(); 
        cout << ", where do you want to complete an Assignment?";
        int intersection;
        cin >> intersection;
        default_game.players[i].buy_criteria(intersection);
    }
    //backwards
    for (int i = 3; i > 0; --i){
        cout << "Student " << default_game.players[i].get_name();
        cout << ", where do you want to complete an Assignment?";
        int intersection;
        cin >> intersection;
        default_game.players[i].buy_criteria(intersection);
    }

    // printBoard();

    // start turn
    for (int i = 0; i < turnOrder.length(); ++i){
        cout << "Student " << default_game.players[i].get_name() << "'s turn.";
        default_game.players[i].print_status();
    }

}
