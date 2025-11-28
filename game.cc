export module Game;

import <string>;
import <fstream>;
import <vector>;

import Board;
import Student;

export class Game {
    Board gameBoard;

    // get methods for turn should be made available.
    int seed;
    int cur_turn;

    // a vector of players. could be replaced with array, but vectors offer more convenience and potential for expansion
    std::vector<Student> players;
    int active_id = 0;
  
  public:
    Game(int seed, Board gameBoard, std::vector<Student> players, int cur_turn = 0);
    
    void turn_num();
    

    // save methods from file and to file
    void board_from_file(std::ifstream &file);
    void load_game(std::ifstream &file);
    void save(std::string filename);

    // interface methods:
    void next_turn();
    void roll_dice(bool isfair);

    // output operator
    friend std::ostream& operator<<(std::ostream& os, Game& game);
};