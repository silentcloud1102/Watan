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
  
  public:
    Game(int seed, Board gameBoard, std::vector<Student> players, int cur_turn = 0);
    void next_turn();
    void turn_num();
    void dice_rolls(bool isfair);

    // save methods from file and to file
    void board_from_file(std::ifstream &file);
    void load_game(std::ifstream &file);
    void save(std::string filename);

    // output operator
    friend std::ostream& operator<<(std::ostream& os, Game& game);
};