module Game;

import <iostream>;
import <string>;
import <fstream>;
import <vector>;
import <stdexcept>;
import <memory>;
import <algorithm>;
import <random>;

import Resource;
import Board;
import Student;


const int numofPlayers = 4;
const std::string names[numofPlayers] = {"Blue", "Red", "Orange", "Yellow"};

Game::Game(int seed): seed{seed}, cur_turn{0}, rng(static_cast<unsigned>(seed)){
        // construct board
        std::unique_ptr<Board> gameBoard = std::make_unique<Board>(Board(seed));

        // construct players vector
        for (int i = 0; i < numofPlayers; ++i){
            players.emplace_back(std::make_unique<Student>(names[i], gameBoard.get()));
        }
}

Resource Game::generate_goosed(std::vector<int> resources, int amount){
    std::shuffle(resources.begin(), resources.end(), rng);

    int vals[5]{};
    for(int i = 0;  i < amount; i++){
        vals[resources[i]]++;
    }

    return Resource{vals[0], vals[1], vals[2], vals[3], vals[4]};
}


// Interface methods:
void Game::roll_dice(bool isfair){

    // Generating the dicerolls
    int roll;
    if (isfair){
        // random generation
        int roll1 = (rng() % 6) + 1;
        int roll2 = (rng() % 6) + 1;
        roll = roll1 + roll2;
    } else {
        // loaded
        while (true) {
            std::cout << "Input a roll between 2 and 12: ";
            std::cin >> roll;
            if ((roll < 2) || (12 < roll)){
                std::cout << "Invalid roll." << std::endl;
            } else {
                break;
            }
        }
    }
    std::cout << "Roll: " << roll << std::endl;

    // if 7, GEESE!
    if (roll == 7) {
        // randomly lose half of resources if more than 10, print out results of lost
        for (auto it = players.begin(); it != players.end(); it++){
            int amount = (*it)->resource_count();
            if (amount >= 10){
                Resource loss = generate_goosed((*it)->resource_vector(), amount/2);

                (*it)->goosed(loss);

                
                std::cout << "Student " << (*it)->get_name() << " loses ";
                std::cout << amount/2 << " resources to the geese. They lose:" << std::endl;
                std::vector<int> values = loss.to_vector(false);
                
                for(int i = 0; i < values.size(); i++){
                    std::cout << Resource::print_output(i, values[i]) << std::endl;
                }
            }
        }
        
        // now let them move the goose somewhere
        int goose;
        while (true){
            std::cout << "Choose where to place the GEESE." << std::endl << ">";
            std::cin >> goose;
            if (goose < 0 || 18 < goose || (goose == gameBoard->get_goose_tile())){
                // ask again;
                continue;
            } else {
                gameBoard->update_goose(goose);
                break;
            } 
        }
        
        // steal
        std::string steal_from;
        int steal_from_count = 0;
        std::cout << "Student " << players[active_id]->get_name() << "can choose to steal from ";
        for (int i = 0; i < numofPlayers; ++i){
            Resource zero = Resource{0,0,0,0,0};
            if (i == active_id){
                continue;
            } else if (players[i]->get_resource() <= zero){
                continue;
            }

            for (int j = 0; j < players[i]->criteria.size(); ++j){
                for (int x = 0; x < gameBoard->tiles[goose].course_criteria.size(); ++x){
                    if (players[i]->criteria[j] == gameBoard->tiles[goose].course_criteria[x]){
                        ++steal_from_count;
                        if (i == (numofPlayers - 1)){
                            std::cout << players[i]->get_name() << "." << std::endl;
                        } else {
                            std::cout << players[i]->get_name() << ", ";
                        }
                    }
                }
            }
        }

        if (steal_from_count == 0){
            std::cout << "Student " << players[active_id] << " has no students to steal from." << std::endl;
        } else {
            std::cout << "Choose a student to steal from." << std::endl << ">";
            std::cin >> steal_from;
            
            int steal_from_index = -1;
            for (int i = 0; i < numofPlayers){
                if (steal_from == players[i]->name){
                    steal_from_index = i;
                    break;
                }
            }




            // randomly generate which 1 resource to steal? but have to make sure the student has it

            Resource r;
            players[active_id]->get_resource() += r;
            players[steal_from_index]->get_resource() -= r;
            std::cout << "Student " << players[active_id] << " steals " 
            std::cout << !!!!!!!!!!!!<resource> << " from student " << steal_from << "." << std::endl;
        }

    // Non Geese:
    } else {
       // Track resource distribution
        Resource diff[4];
        for (int i = 0; i < 4; ++i){
            // saving old
            diff[i] = players[i]->get_resource();
        }

        // changes resource for players
        update_tiles(roll);

        for (int i = 0; i < 4; ++i){
            diff[i] -= players[i]->get_resource();
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
            std::cout << "Student " << players[i] << " gained:";

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

void Game::setup(){
    // setup = true so buy_criteria does not deduct from held_resources.
    for (int i = 0; i < numofPlayers; ++i){
        std::cout << *this;
        std::cout << "Student " << players[i]->get_name(); 
        std::cout << ", where do you want to complete an Assignment?" << std::endl << ">";
        int idx;
        std::cin >> idx;
        try{
            players[i]->buy_criteria(idx, true);
        } catch (const std::runtime_error &e) {
            std::cerr << e.what() << std::endl;
            i--;
        }
    }

    //backwards
    for (int i = (numofPlayers - 1); i >= 0; --i){
        std::cout << *this;
        cout << "Student " << players[i]->get_name();
        cout << ", where do you want to complete an Assignment?" << std::endl << ">";
        int idx;
        std::cin >> idx;
        try{
            players[i]->buy_criteria(idx, true);
        } catch (const std::runtime_error &e) {
            std::cerr << e.what() << std::endl;
            i++;
        }
    }

    cur_turn++;
    return;
}

// next turn (new active player)
void Game::next_turn(){
    active_id++;

    if(active_id >= numofPlayers){
        active_id = 0;
        cur_turn++;
    }
}

void Game::begin_turn(){

    std::cout << "Student " << players[active_id]->get_name() << "'s turn." << std::endl;
    
    // outputs status of Student
    std::cout << *players[active_id];

    // Then proceed to dice roll logic...
}

// info methods:
int Game::turn_num() const{
    return cur_turn;
}

bool Game::has_won() const{
    for(auto it = players.begin(); it != players.end(); it++){
        if ((*it)->get_criteria_count() >= 10) {
            std::cout << "Student " << (*it)->get_name() << " has won!";
            return true;
        }
    }
    return false;
}
// Save methods:

// Generate save
void Game::save(std::string filename){
    // build load file
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Open failed! Aborting save..." << std::endl;
        return;
    }

    // cur_turn
    out << this->cur_turn << std::endl;

    // players
    for (int i = 0; i < numofPlayers; ++i){
        out << this->players[i]->get_save_string() << std::endl;
    }

    // board
    out << this->gameBoard->get_save_string() << std::endl;

    // goose
    out << this->gameBoard->get_goose_tile() << std::endl;
}

// Read board line from save (used by -board and -load)
void Game::board_from_file(std::ifstream &file){
    // read from file
    std::vector<int> givenBoard;
    std::string line;
    std::getline(file, line);

    std::istringstream iss {line};
    int temp;
    for (int i = 0; i < 38; ++i){
        if (!(iss >> temp)){
            throw std::runtime_error("Invalid save file format, expected 38 integers");
        }
        givenBoard.emplace_back(temp);
    }
    gameBoard->load_save_data(givenBoard);

}

// Read game from save, used by -load
void Game::load_game(std::ifstream &file){
    std::string line;
    std::getline(file, line);
    // first line is the turn number
    cur_turn = std::stoi(line);

    // next 4 lines are player data
    for (int i = 0; i < numofPlayers; ++i){
        std::getline(file, line);
        //playerColor pc = static_cast<playerColor>(i);
        players[i]->read_save_string(line);
    }

    // reads board line
    board_from_file(file);

    std::getline(file, line);
    gameBoard->update_goose(std::stoi(line));
}


std::ostream& operator<<(std::ostream& os, Game& game){
    os << game.gameBoard;
    return os;
}