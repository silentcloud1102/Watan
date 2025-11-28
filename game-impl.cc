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

Game::Game(int seed): seed{seed}, cur_turn{0}, rng(static_cast<unsigned>(seed)) {
        // construct board
        gameBoard = std::make_unique<Board>(seed);

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
void Game::roll_dice(){
    bool isfair = true;

    std::string cmd;
    while(true){
        std::cout << "Available commands:" << std::endl;
        std::cout << "load" << std::endl;
        std::cout << "fair" << std::endl;
        std::cout << "roll" << std::endl;
        std::cout << ">";
        std::cin >> cmd;

        if(cmd == "load"){
            std::cout << "Dice set to loaded." << std::endl;
            isfair = false;
        } else if (cmd == "fair") {
            std::cout << "Dice set to fair." << std::endl;
            isfair = true;
        } else if (cmd == "roll") {
            std::cout << "Rolling...";
            std::cin >> cmd;
            break;
        } else {
            std::cerr << "Unknown command. Try again." << std::endl;
        }
    }
    
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
                std::cerr << "Invalid roll." << std::endl;
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
            if (goose < 0 || goose > 18 || (goose == gameBoard->get_goose_tile())){
                // ask again;
                std::cerr << "Goose cannot be placed it this tile.";
                continue;
            } else {
                gameBoard->update_goose(goose);
                break;
            } 
        }
        
        // stealing:
        std::vector<std::string> victim_ids = gameBoard->goose_victims();
        std::vector<Student *> victims;
        for (int i = 0; i < numofPlayers; ++i){
            // if self or broke, don't steal :)
            if (i == active_id){
                continue;
            } else if (players[i]->resource_count() <= 0){
                continue;
            }

            // otherwise:
            for(auto it = victim_ids.begin(); it != victim_ids.end(); it++){
                if((*it)[0] == players[i]->get_name()[0]) {
                    victims.emplace_back(players[i].get());
                }
            }
        }

        if (victims.size() == 0){
            std::cout << "Student " << players[active_id] << " has no students to steal from." << std::endl;
        } else {
            std::cout << "Student " << players[active_id]->get_name() << "can choose to steal from ";
            for(auto it = victims.begin(); it != victims.end(); it++){
                std::cout << (*it)->get_name();
                if(it + 1 != victims.end()){
                    std::cout << ", ";
                } else {
                    std::cout << '.';
                }
            }

            std::string steal_from;
            bool valid_choice = false;
            while(!valid_choice){
                std::cout << "Choose a student to steal from." << std::endl << ">";
                std::cin >> steal_from;
            
                for (auto v : victims){
                    valid_choice = (steal_from == *v);
                    if(valid_choice){
                        break;
                    }
                }

                if(!valid_choice){
                    std::cout << "Invalid selection, try again." << std::endl;
                }
            }

            for (int i = 0; i < players.size(); i++){
                if(*players[i] == steal_from){
                    // randomly generate 1 resource to steal
                    Resource loss = generate_goosed(players[i]->resource_vector(), 1);
                    
                    // active gains loss, i (victim) gets goosed for loss
                    players[active_id]->resource_notify(loss);
                    players[i]->goosed(loss);

                    // use stringstream to read in.. a little inconvenient but it will do
                    std::istringstream iss {Resource::print_output(loss.to_vector()[0], 1)};
                    std::string resource;
                    iss >> resource >> resource;

                    // output to stdout
                    std::cout << "Student " << players[active_id]->get_name() << " steals ";
                    std::cout << resource << " from student " << players[i]->get_name() << '.';
                    std::cout << std::endl;
                }
            }
        }

        // end of geese.
        return;
    // Non Geese:
    } else {
       // Track resource distribution
        Resource diff[4];
        for (int i = 0; i < 4; ++i){
            // saving old
            diff[i] = players[i]->get_resource();
        }

        // changes resource for players
        gameBoard->update_tiles(roll);
        bool changed = false;

        for (int i = 0; i < 4; ++i){
            diff[i] = players[i]->get_resource() - diff[i];
            if(diff[i].count()){
                changed = true;
            }
            // measures the change
        }

        if(changed){
            for (int i = 0; i < 4; ++i){
                if(diff[i].count() == 0){
                    continue;
                }

                std::cout << "Student " << players[i]->get_name() << " gained:";

                std::vector<int> gains = diff[i].to_vector(false);
                for(int i = 0; i < gains.size(); i++){
                    std::cout << Resource::print_output(i, gains[i]) << std::endl;
                }
            }
        } else {
            std::cout << "No students gained resources." << std::endl;
        }
    }
    // Dice roll done.
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
        std::cout << "Student " << players[i]->get_name();
        std::cout << ", where do you want to complete an Assignment?" << std::endl << ">";
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
        std::cout << "Turn " << cur_turn;
    }
}

void Game::begin_turn() {

    std::cout << "Student " << players[active_id]->get_name() << "'s turn." << std::endl;
    
    // outputs status of Student
    status();

    // Then proceed to dice roll logic...
    roll_dice();
}


void Game::board() const {
    std::cout << gameBoard;
}

void Game::status() const {
    std::cout << *players[active_id];
}

void Game::criteria() const {
    std::cout << players[active_id]->completions();
}

void Game::achieve(int goal){
    try{
        players[active_id]->buy_goal(goal);
    } catch (const std::runtime_error &e){
        std::cerr << e.what() << std::endl;
    }
}

void Game::complete(int criteria){
    try{
        players[active_id]->buy_criteria(criteria);
    } catch (const std::runtime_error &e){
        std::cerr << e.what() << std::endl;
    }
}

void Game::improve(int criteria){
    try{
        players[active_id]->upgrade_criteria(criteria);
    } catch (const std::runtime_error &e){
        std::cerr << e.what() << std::endl;
    }
}

void Game::trade(std::string colour, std::string give, std::string take){
    if(!players[active_id]->can_afford(Resource{give, 1})){
        std::cerr << "You cannot afford this trade." << std::endl;
        return;
    }

    for(auto it = players.begin(); it != players.end(); it++){
        if(*(*it) == colour) {
            if((*it)->can_afford(Resource{take, 1})) {
                std::cerr << colour << " cannot afford this trade." << std::endl;
                return;
            }
            // else:
            std::cout << players[active_id]->get_name() << " offers " << colour << " one " << give << " for one " << take << "."  << std::endl;
            std::cout << "Does " << colour << " accept this offer?" << std::endl << ">";
            std::string ans;
            std::cin >> ans;

            if(ans == "yes"){
                players[active_id]->trade((*it).get(), give, take);
            } else {
                std::cout << colour << "declined the trade." << std::endl;
            }
            return;
        }
    }

    std::cout << "Student not found, try again." << std::endl;
}

void Game::help() const{
    std::cout << "Valid Commands:" << std::endl;
    std::cout << "board" << std::endl;
    std::cout << "status" << std::endl;
    std::cout << "criteria" << std::endl;
    std::cout << "achieve <goal>" << std::endl;
    std::cout << "complete <criterion>" << std::endl;
    std::cout << "improve <criterion>" << std::endl;
    std::cout << "trade <colour> <give> <take>" << std::endl;
    std::cout << "next" << std::endl;
    std::cout << "save <file>" << std::endl;
    std::cout << "help" << std::endl;
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
            // don't expect to be catched since this is an error with arguments
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
    os << *(game.gameBoard);
    return os;
}