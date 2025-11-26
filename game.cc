export module Game;

import Board;

export class Game {
    Board gameBoard;
    vector<Student> players;
    int cur_turn;
  public:
    void next_turn();
    void turn_num();
    void save(string filename);
    void dice_rolls(bool isfair);

};