module Game;

import Board;

void Game::diceRolls(bool isfair){
    if (isfair){
        // random generate
    } else {
        // loaded
        int roll;
        while (true){
            cout << "Input a roll between 2 and 12: ";
            cin >> roll;
            if ((roll < 2) || (12 < roll)){
                cout < "Invalid roll." << endl;
            } else {
                return roll;
            }
        }
        
    }
}