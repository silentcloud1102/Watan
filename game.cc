export module Game;

import Board;

export class Game {
    Board gameBoard;
    vector<Student> players;
    int cur_turn;
    int goose_tile;
  public:
    void nextTurn();
    void turnNum();
    void save(string filename);
    int getGooseTile();
    void diceRolls(bool isfair);

};