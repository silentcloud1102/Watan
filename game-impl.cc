module Game;

import Board;
import Student
import <string>;
import <fstream>;
import <vector>;

using namespace std;

const numofPlayers = 4;
const string names[numofPlayers] = {"Blue", "Red", "Orange", "Yellow"};

Game::Game(int seed, Board gameBoard, vector<Student> players, int cur_turn): 
    Board{gameBoard}, players{players}, cur_Turn{cur_turn}, seed{seed}{
        
        //Board board = Board(seed);
        // unique_ptr<Board> board = make_unique<Board>(Board(seed));
        gameBoard = Board(seed);
        for (int i = 0; i < numofPlayers; ++i){
            Student s = Student{names[i], *gameBoard};
            players.emplace_back(s);
        }
}

void Game::board_from_file(ifstream &file){
    // read from file
    vector<int> givenBoard;
    int temp;
    for (int i = 0; i < 38; ++i){
        if (!(file >> temp)){
            break;
        }
        givenBoard.emplace_back(temp);
    }
    gameBoard->load_save_data(givenBoard);
}

void Game::load_game(std::ifstream &file){
    std::string line;
    std::getline(file, line);
    // first line is the turn number
    cur_turn = line.stoi();

    // next 4 lines are player data
    for (int i = 0; i < numofPlayers; ++i){
        std::getline(file, line);
        //playerColor pc = static_cast<playerColor>(i);
        players[i].read_save_string(line);
    }

    // reads board line
    board_from_file(file);

    std::getline(file, line)
    gameBoard->update_goose(line.stoi());
}

void Game::dice_rolls(bool isfair){
    // =========================================================
    // Generating the dicerolls
    // =========================================================
    int roll;
    if (isfair){
        // random generate
        unsigned seed_val = 69;
        default_random_engine rng{seed_val};
        int roll1 = (rng() % 6) + 1;
        int roll2 = (rng() % 6) + 1;
        roll = roll1 + roll2;
    } else {
        // loaded
        while (true) {
            cout << "Input a roll between 2 and 12: ";
            cin >> roll;
            if ((roll < 2) || (12 < roll)){
                cout < "Invalid roll." << endl;
            } else {
                break;
            }
        }
    }

    // =========================================================
    // using the implications of the dice roll
    // =========================================================
    if (roll == 7) {
        // lose half of resources if more than 10 randomly, print out
        for (int i = 0; i < numofPlayers; ++i){
            int amount = players[i].held_resources.count();
            if (amount >= 10){
                int generate = amount/2;

                ///////// need to randomly generate half of what they have




                Resource r;
                players[i].held_resources -= r;
                Resource * resources = players[i].held_resources;

                cout << "Student " << players[i].name << "loses ";
                cout << generate << "resources to the geese. They lose:" << endl;

                cout << resources.caffeine << " caffeine" << endl;
                cout << resources.lab << " lab" << endl;
                cout << resources.lecture << " lecture" << endl;
                cout << resources.study << " study" << endl;
                cout << resources.tutorial << " tutorial" << endl;
            }
        }

        while (true){
            // let them move the goose somewhere, then check for stealing 
            int goose;
            cout << "Choose where to place the GEESE." << endl << ">";
            cin >> goose;
            if (goose < 0 || 18 < goose || (goose == gameBoard.goose_tile)){
                // ask again;
                continue;
            } else {
                gameBoard.update_goose(goose);
                break;
            } 
        }
        
        // steal




    } else {

        Resource diff[4];
        for (int i = 0; i < 4; ++i){
            // saving old
            diff[i] = players[i].held_resources;
        }

        // changes resource for players
        update_tiles(roll);

        for (int i = 0; i < 4; ++i){
            diff[i] -= players[i].held_resources;
        }


        // Resource old0 = players[0];
        // Resource old1 = players[1];
        // Resource old2 = players[2];
        // Resource old3 = players[3];
        
        // // changes resource for players
        // update_tiles(roll);

        // Resource diff[4];

        // diff[0] = players[0].held_resources - old0;
        // diff[1] = players[1].held_resources - old1;
        // diff[2] = players[2].held_resources - old2;
        // diff[3] = players[3].held_resources - old3;

        bool changed = false;
        
        for (int i = 0; i < 4; ++i){
            cout << "Student " << players[i] << " gained:";

            if (diff[i].caffeine != 0){
                cout << -diff[i].caffeine << " CAFFEINE" << endl;
                changed = true;
            } else if (diff[i].lab != 0){
                cout << -diff[i].lab << " LAB" << endl;
                changed = true;
            } else if (diff[i].lecture != 0){
                cout << -diff[i].lecture << " LECTURE" << endl;
                changed = true;
            } else if (diff[i].study != 0){
                cout << -diff[i].study << " STUDY" << endl;
                changed = true;
            } else if (diff[i].tutorial != 0){
                cout << -diff[i].tutorial << " TUTORIAL" << endl;
                changed = true;
            }
        }

        if (!changed){
            cout << "No students gained resources." << endl;
        }
    }
}


void Game::save(string filename){
    // build load file
    ofstream out(filename);
    if (!out) {
        std::cerr << "open failed\n";
        return;
    }

    // cur_turn
    out << this->cur_turn << endl;

    // players
    for (int i = 0; i < numofPlayers; ++i){
        out << this->players[i].get_save_string() << endl;
    }

    // board
    out << this->gameBoard.save_data() << endl;

    // goose
    out << this->gameBoard.get_goose_tile() << endl;
}


ostream& operator<<(ostream& os, Game& game){
    os << game.gameBoard;
    return os;
}