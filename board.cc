export module Board;

import <iostream>;
import <string>;
import <vector>;
import <memory>;
import Criteria;
import Goal;
import Tile;

export class Board {
    // resource names to pass to Tiles
    static const std::vector<std::string> resource_names;

    // constants for the desired sizes, to initialize and improve readability
    static const int num_of_goals = 72;
    static const int num_of_course_criteria = 54;
    static const int num_of_tiles = 19;

    int goose_tile;
    
    // std::vector<Tile> tiles;
    // std::vector<Goal> goals;
    // std::vector<Criteria> course_criteria;
    std::vector<std::unique_ptr<Tile>> tiles;
    std::vector<std::unique_ptr<Goal>> goals;
    std::vector<std::unique_ptr<Criteria>> course_criteria;
    
    std::string goose_printer(std::string tile) const;

    public:
        // constructor
        Board(unsigned seed);

        // update tiles passes on notifications to criteria (Subjects observed by Player)
        void update_tiles(int roll_num) const;

        // get methods that return pointers, for Student to access and acquire/upgrade
        Criteria* get_criteria(int criteria_num) const;
        Goal* get_goal(int goal_num) const;

        // goose handling
        void update_goose(int new_goose_tile);
        int get_goose_tile() const;
        std::vector<std::string> goose_victims() const;
        // output
        friend std::ostream &operator<<(std::ostream &out, const Board &b);

        // save methods
        void load_save_data(std::vector<int> save_data);
        std::string get_save_string();
};

