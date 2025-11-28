export module Board;

import <iostream>;
import <string>;
import <vector>;
import Criteria;
import Goal;
import Tile;

export class Board {
    int goose_tile;
    std::vector<Tile> tiles;
    std::vector<Goal> goals;
    std::vector<Criteria> course_criteria;
    std::string goose_printer(std::string tile) const;
    public:
        Board(unsigned seed);
        void load_saveData(std::vector<int> save_data);
        std::string saveData();
        void update_tiles(int roll_num) const;
        const Criteria& getCriteria(int criteria_num) const;
        const Goal& getGoals(int goal_num) const;
        void updateGoose(int new_goosetile);
        int getGooseTile() const;
        friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

