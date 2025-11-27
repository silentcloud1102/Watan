module Game;

import Board;
import enum;

Game::Game(int seed, Board gameBoard, vector<Student> players, int cur_turn): 
    Board{gameBoard}, players{players}, cur_Turn{cur_turn}, seed{seed}{
        //Board board = Board(seed);
        // unique_ptr<Board> board = make_unique<Board>(Board(seed));
        gameBoard = Board(seed);
        for (int i = 0; i < numofPlayers; ++i){
            Student s = Student{names[i], board};
            players.emplace_back(s);
        }
}

void Game::updateBoard(){
    
}

void Game::dice_rolls(bool isfair){
    // =========================================================
    // Generating the dicerolls
    // =========================================================
    int roll;
    if (isfair){
        // random generate
        unsigned seed_val = 69;
        default_random_engine rng{seed_val};
        int roll1 = (rng() % 6) + 1;
        int roll2 = (rng() % 6) + 1;
        roll = roll1 + roll2;
    } else {
        // loaded
        while (true) {
            cout << "Input a roll between 2 and 12: ";
            cin >> roll;
            if ((roll < 2) || (12 < roll)){
                cout < "Invalid roll." << endl;
            } else {
                break;
            }
        }
    }

    // =========================================================
    // using the implications of the dice roll
    // =========================================================
    if (roll == 7) {
        // let them move the goose somewhere, then check for stealing
        gameBoard.update_goose()
    } else {
        update_tiles(roll);
    }
}


void Game::save(string filename){
    // build load file
}
