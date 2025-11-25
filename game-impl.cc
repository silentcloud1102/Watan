module Game;

import Board;

void Game::diceRolls(bool isfair){
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
        gameBoard.updateGoose()
    } else {
        update_tiles(roll);
    }
}
