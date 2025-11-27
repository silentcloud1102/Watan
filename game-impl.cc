module Game;

import Board;
import Student
import <string>;
import <fstream>;
import <vector>;

using namespace std;

const numofPlayers = 4;
const string names[numofPlayers] = {"Blue", "Red", "Orange", "Yellow"};

Game::Game(int seed, Board gameBoard, vector<Student> players, int cur_turn): 
    Board{gameBoard}, players{players}, cur_Turn{cur_turn}, seed{seed}{
        
        //Board board = Board(seed);
        // unique_ptr<Board> board = make_unique<Board>(Board(seed));
        gameBoard = Board(seed);
        for (int i = 0; i < numofPlayers; ++i){
            Student s = Student{names[i], *gameBoard};
            players.emplace_back(s);
        }
}

void Game::updateBoard(ifstream &file){
    // read from file
    vector<int> givenBoard;
    int temp;
    for (int i = 0; i < 38; ++i){
        if (!(file >> temp)){
            break;
        }
        givenBoard.emplace_back(temp);
    }
    gameBoard->load_saveData(givenBoard);
}

void Game::loadGame(ifstream &file){
    int file_turn;
    getline(ifsl, file_turn);
    cur_turn = file_turn;

    for (int i = 0; i < numofPlayers; ++i){
        string line;
        getline(file, line);
        //playerColor pc = static_cast<playerColor>(i);
        players[i].read_save_string(line);
    }

    // reads board line
    this->updateBoard(file);

    int goose;
    file >> goose;
    gameBoard->updateGoose(goose);
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
    ofstream out(filename);
    if (!out) {
        std::cerr << "open failed\n";
        return;
    }

    // cur_turn
    out << this->cur_turn << endl;

    // players
    for (int i = 0; i < numofPlayers; ++i){
        this->players[i].get_save_string() << endl;
    }

    // board
    out << this->gameBoard.saveData() << endl;

    // goose
    out << this->gameBoard.getGooseTile() << endl;
}
