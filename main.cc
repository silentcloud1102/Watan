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
    bool load = false;
    bool board = false;

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
            load = true;
        } else if (argv[i] = "-board"){
            if (i + 1 < argc){
                boardfile = argv[i+1];
                ++i;
            }
            board = true;
        }
    }

    bool play_again = true;
    while (play_again){
    
        Game default_game = Game(seed);

        if (load){
            while (true){
                cout << "Would like like to play on your loaded game or start a new game?[L/N]" << endl << ">";
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
        } else if (board){
            while (true){
                cout << "Would like like to play on your board or start a new game?[B/N]" << endl << ">";
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
            cout << ", where do you want to complete an Assignment?" << endl << ">";
            int intersection;
            cin >> intersection;
            default_game.players[i].buy_criteria(intersection);
        }
        //backwards
        for (int i = 3; i >= 0; --i){
            cout << "Student " << default_game.players[i].get_name();
            cout << ", where do you want to complete an Assignment?" << endl << ">";
            int intersection;
            cin >> intersection;
            default_game.players[i].buy_criteria(intersection);
        }

        // printBoard();

        bool playing_game = true;
        while (playing_game){
            for (int i = 0; i < turnOrder.length(); ++i){
                Student * player = &default_game.players[i];

                while (true){
                    cout << "Student " << default_game.players[i].get_name() << "'s turn.";
                    player->print_status();

                    string turn_command;
                    cout << ">";
                    cin >> turn_command;

                    if (turn_command == "load"){
                        player->isfair = false;
                    } else if (turn_command == "fair"){
                        player->isfair = true;
                    } 
                    
                    if (turn_command == "roll"){
                        default_game.dice_rolls(player->isfair);
                        break;
                    } 
                }

                string command;
                while (true){
                    cout << ">";
                    cin >> command;
                    if (command == "board"){
                        // printBoard();
                    } else if (command == "status"){
                        for (int i = 0; i < 4; ++i){
                            player->print_status();
                        }
                    } else if (command == "criteria"){
                        // completions?
                    } else if (command == "achieve"){
                        cout << ">";
                        int goal;
                        cin >> goal;
                        player->buy_goal(goal);
                    } else if (command == "complete"){
                        int c;
                        cin >> c;
                        player->buy_criteria(c);
                    } else if (command == "improve"){
                        int c;
                        cin >> c;
                        player->upgrade_critiera(c);
                    } else if (command == "trade"){
                        string color;
                        string give_r;
                        string take_r;
                        cin >> color >> give_r >> take_r;

                        while (true){
                            cout << player->name << " offers " << color << " one " 
                            cout << give_r << " for one " << take_r << "." << endl;
                            cout << "Does " << color << " accept this offer?[yes/no]" << endl << ">";

                            string ans;
                            cin >> ans;
                            if (ans == "yes"){
                                Student * color2; 
                                if (color == "Blue"){
                                    color2 = default_game.players[0];
                                } else if (color == "Red"){
                                    color2 = default_game.players[1];
                                } else if (color == "Orange"){
                                    color2 = default_game.players[2];
                                } else if (color == "Yellow"){
                                    color2 = default_game.players[3];
                                }

                                // assumes give_r and take_r are all upper case, resource constructor
                                player->trade(color2, give_r, take_r);

                                break;
                            } else if (ans == "no"){
                                break;
                            }
                        }
                        
                    } else if (command == "next"){
                        break;
                    } else if (command == "save"){
                        string filename;
                        cin >> filename;
                        default_game.save(filename);
                    } else if (command == "help"){
                        cout << "Valid commands:" << endl;
                        cout << "board" << endl;
                        cout << "status" << endl;
                        cout << "criteria" << endl;
                        cout << "achieve <goal>" << endl;
                        cout << "complete <criterion>" << endl;
                        cout << "improve <criterion>" << endl;
                        cout << "trade <colour> <give> <take>" << endl;
                        cout << "next" << endl;
                        cout << "save <file>" << endl;
                        cout << "help" << endl;
                    } else {
                        cout << "Invalid command." << endl;
                    }
                }

                if (player->criteria_count >= 10){
                    // extra, not in doc
                    cout << player->name << " has 10 completed course criteria. Congratulations!";
                    playing_game = false;
                    break;
                }

            } // end of one player's turn (for loop)
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
