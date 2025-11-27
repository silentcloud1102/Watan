export module Game;

import Board;
import enum;
import <string>;

using nameespace std;

export class Game {
    Board gameBoard;
    vector<Student> players;
    int cur_turn;
    int seed;
  public:
    Game(int seed, Board gameBoard, vector<Student> players, int cur_turn = 0);
    void next_turn();
    void turn_num();
    void save(string filename);
    void dice_rolls(bool isfair);
    void updateBoard(ifstream &file);
    void loadGame(ifstream &file);

};