export module Game;

import Board;
import Student

import <string>;
import <fstream>;
import <vector>;


export class Game {
    Board gameBoard;
    std::vector<Student> players;
    int cur_turn;
    int seed;

  public:
    Game(int seed, Board gameBoard, std::vector<Student> players, int cur_turn = 0);
    void next_turn();
    void turn_num();
    void save(std::string filename);
    void dice_rolls(bool isfair);
    void board_from_file(std::ifstream &file);
    void load_game(std::ifstream &file);
    friend std::ostream& operator<<(std::ostream& os, Game& game);
};