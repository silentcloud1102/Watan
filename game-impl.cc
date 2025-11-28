module Game;

import Board;
import Student
import <string>;
import <fstream>;
import <vector>;
import <stdexcept>;


const numofPlayers = 4;
const string names[numofPlayers] = {"Blue", "Red", "Orange", "Yellow"};

Game::Game(int seed, Board gameBoard, std::vector<Student> players, int cur_turn): 
    Board{gameBoard}, players{players}, cur_Turn{cur_turn}, seed{seed}{
        
        //Board board = Board(seed);
        // unique_ptr<Board> board = make_unique<Board>(Board(seed));
        gameBoard = Board(seed);
        for (int i = 0; i < numofPlayers; ++i){
            Student s = Student{names[i], *gameBoard};
            players.emplace_back(s);
        }
}

std::ifstream & Game::board_from_file(std::ifstream &file){
    // read from file
    std::vector<int> givenBoard;
    std::string line;
    std::getline(file, line);

    int temp;
    for (int i = 0; i < 38; ++i){
        if (!(line >> temp)){
            throw std::runtime_error("Invalid save file format, expected 38 integers");
        }
        givenBoard.emplace_back(temp);
    }
    gameBoard->load_save_data(givenBoard);

    return file;
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

void Game::dice_rolls(bool isfair, int playerIndex){

    // Generating the dicerolls
    int roll;
    if (isfair){
        // random generate
        unsigned seed_val = 69;
        std::default_random_engine rng{seed_val};
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

                cout << resources.caffeine << " CAFFIENE" << endl;
                cout << resources.lab << " LAB" << endl;
                cout << resources.lecture << " LECTURE" << endl;
                cout << resources.study << " STUDY" << endl;
                cout << resources.tutorial << " TUTORIAL" << endl;
            }
        }


        // let them move the goose somewhere
        int goose;
        while (true){
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
        int steal_from_count = 0;
        cout << "Student " << player[playerIndex].name << "can choose to steal from ";
        for (int i = 0; i < numofPlayers; ++i){
            Resource zero = Resource{0,0,0,0,0};
            if (i == playerIndex){
                continue;
            } else if (players[i].held_resources <= zero){
                continue;
            }

            for (int j = 0; j < players[i].criteria.size(); ++j){
                for (int x = 0; x < gameBoard.tiles[goose].course_criteria.size(); ++x){
                    if (players[i].criteria[j] == gameBoard.tiles[goose].course_criteria[x]){
                        ++steal_from_count;
                        if (i == (numofPlayers - 1)){
                            cout << players[i].name << "." << endl;
                        } else {
                            cout << players[i].name << ", ";
                        }
                    }
                }
            }
        }

        if (steal_from_count == 0){
            cout << "Student " << players[playerIndex] << " has no students to steal from." << endl;
        } else {
            cout << "Choose a student to steal from." << endl << ">";
            string steal_from;
            cin >> steal_from;
            
            int steal_from_index = -1;
            for (int i = 0; i < numofPlayers){
                if (steal_from == players[i].name){
                    steal_from_index = i;
                    break;
                }
            }




            // randomly generate which 1 resource to steal? but have to make sure the student has it

            Resource r;
            players[playerIndex].held_resources += r;
            players[steal_from_index].held_resources -= r;
            cout << "Student " << players[playerIndex] << " steals " 
            cout << !!!!!!!!!!!!<resource> << " from student " << steal_from << "." << endl;
        }


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
        
        // Okay to have cin/cout here since this is our main interface with the game
        for (int i = 0; i < 4; ++i){
            cout << "Student " << players[i] << " gained:";

            if (diff[i].caffeine != 0){
                std::cout << -diff[i].caffeine << " CAFFEINE" << std::endl;
                changed = true;
            } else if (diff[i].lab != 0){
                std::cout << -diff[i].lab << " LAB" << std::endl;
                changed = true;
            } else if (diff[i].lecture != 0){
                std::cout << -diff[i].lecture << " LECTURE" << std::endl;
                changed = true;
            } else if (diff[i].study != 0){
                std::cout << -diff[i].study << " STUDY" << std::endl;
                changed = true;
            } else if (diff[i].tutorial != 0){
                std::cout << -diff[i].tutorial << " TUTORIAL" << std::endl;
                changed = true;
            }
        }

        if (!changed){
            std::cout << "No students gained resources." << std::endl;
        }
    }
}


void Game::save(std::string filename){
    // build load file
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "open failed\n";
        return;
    }

    // cur_turn
    out << this->cur_turn << std::endl;

    // players
    for (int i = 0; i < numofPlayers; ++i){
        out << this->players[i].get_save_string() << std::endl;
    }

    // board
    out << this->gameBoard.save_data() << std::endl;

    // goose
    out << this->gameBoard.get_goose_tile() << std::endl;
}


std::ostream& operator<<(std::ostream& os, Game& game){
    os << game.gameBoard;
    return os;
}