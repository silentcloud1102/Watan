export module Game;

import <iostream>;
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
    bool has_won(std::ostream & out) const;
    Resource generate_goosed(std::vector<int> resources, int amount);

    // save methods from file and to file
    void board_from_file(std::ifstream &file);
    void load_game(std::ifstream &file);
    void save(std::string filename, std::ostream & out);

    // interface methods: tied to player actions
    void roll_dice(std::ostream & out, std::istream & in);
    void setup(std::ostream & out, std::istream & in);
    void next_turn(std::ostream & out);
    void begin_turn(std::ostream & out) ;
    
    void board(std::ostream & out) const;
    void status(std::ostream & out) const;
    void criteria(std::ostream & out) const;
    void achieve(int goal, std::ostream & out);
    void complete(int criteria, std::ostream & out);
    void improve(int criteria, std::ostream & out);
    void trade(std::string colour, std::string give, std::string take, std::ostream & out, std::istream & in);
    void help(std::ostream & out) const;
    



    // output operator
    friend std::ostream& operator<<(std::ostream& os, Game& game);
};