export module Game;

import Board;

export class Game {
    Board gameBoard;
    vector<Student> players;
    int cur_turn;
  public:
    void nextTurn();
    void turnNum();
    void save(string filename);
    void diceRolls(bool isfair);

};