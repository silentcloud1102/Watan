export module Game;

import <string>;
import <fstream>;
import <vector>;
import <memory>;
import <random>;

import Resource;
import Board;
import Student;

export class Game {
    std::unique_ptr<Board> gameBoard;

    // get methods for turn should be made available.
    int seed;
    int cur_turn;

    std::default_random_engine rng;

    // a vector of players. could be replaced with array, but vectors offer more convenience and potential for expansion
    std::vector<std::unique_ptr<Student>> players;
    int active_id = 0;
  
  public:
    Game(int seed);
    
    int turn_num() const;
    bool has_won() const;
    Resource generate_goosed(std::vector<int> resources, int amount);

    // save methods from file and to file
    void board_from_file(std::ifstream &file);
    void load_game(std::ifstream &file);
    void save(std::string filename);

    // interface methods: tied to player actions
    void next_turn();
    void roll_dice(bool isfair);
    

    // output operator
    friend std::ostream& operator<<(std::ostream& os, Game& game);
};