export module Board;

import <iostream>;
import <string>;
import <vector>;
import Criteria;
import Goals;
import Tiles;

export class Board {
    int goose_tile;
    std::vector<Tile> tiles;
    std::vector<Goal> goals;
    std::vector<Criteria> course_criteria;
    std::string goose_printer(int tile_num) const;
    public:
        Board(unsigned seed);
        void load_saveData(std::vector<int> save_data);
        std::vector<int> saveData();
        void update_tiles(int roll_num, int goose_tile) const;
        Criteria& getCriteria(int criteria_num) const;
        Goal& getGoals(int goal_num) const;
        void updateGoose(int new_goosetile);
        int getGooseTile() const;
};

friend ostream &operator<<(ostream &out, const Board &b);