module Board;

import <iostream>;
import <sstream>;
import <string>;
import <vector>;
import <stdexcept>;
import <algorithm>;
import <memory>;
import <random>;
import Criteria;
import Goal;
import Tile;
import Resource;


// CONSTANTS:

// Creating our vectors of data below (board will be hardcoded)
// Each index will represent the goal/criterion number 
// i.e. GoalsAdjCriterion[5] is the vector containing the ids of the criterion adjacent to goal 5 
// (the 6th goal since we start counting from 0)

//  Adjacent course criterion for each goal
const std::vector<std::vector<int>> GoalsAdjCriterion = {
    {0, 1}, {0, 3}, {1, 4}, {2, 3}, {4, 5}, {2, 7}, {3, 8}, {4, 9}, {5, 10}, {6, 7}, {8, 9}, {10, 11},
    {6, 12}, {7, 13}, {8, 14}, {9, 15}, {10, 16}, {11, 17}, {13, 14}, {15, 16}, {12, 18}, {13, 19},
    {14, 20}, {15, 21}, {16, 22}, {17, 23}, {18, 19}, {20, 21}, {22, 23}, {18, 24}, {19, 25}, {20, 26},
    {21, 27}, {22, 28}, {23, 29}, {25, 26}, {27, 28}, {24, 30}, {25, 31}, {26, 32}, {27, 33}, {28, 34},
    {29, 35}, {30, 31}, {32, 33}, {34, 35}, {30, 36}, {31, 37}, {32, 38}, {33, 39}, {34, 40}, {35, 41},
    {37, 38}, {39, 40}, {36, 42}, {37, 43}, {38, 44}, {39, 45}, {40, 46}, {41, 47}, {42, 43}, {44, 45},
    {46, 47}, {43, 48}, {44, 49}, {45, 50}, {46, 51}, {47, 52}, {49, 50}, {48, 49}, {50, 53}, {52, 53}
};

//  Adjacent goals for each goal
const std::vector<std::vector<int>> GoalsAdjGoals = {
    {1,2}, {0,3,6}, {0,4,7}, {1,5,6}, {2,7,8}, {3,9,13}, {1,3,10,14},
    {2,4,10,15}, {4,11,16}, {5,12,13}, {6,7,14,15}, {8,16,17}, {9,20},
    {5,9,18,21}, {6,10,18,22}, {7,10,19,23}, {8,11,19,24}, {11,25},
    {13,14,21,22}, {15,16,23,24}, {12,26,29}, {13,18,26,30}, {14,18,27,31},
    {15,19,27,32}, {16,19,28,33}, {17,28,34}, {20,21,29,30}, {22,23,31,32},
    {24,25,33,34}, {20,26,37}, {21,26,35,38}, {22,27,35,39}, {23,27,36,40},
    {24,28,36,41}, {25,28,42}, {30,31,38,39}, {32,33,40,41}, {29,43,46},
    {30,35,43,47}, {31,35,44,48}, {32,36,44,49}, {33,36,45,50}, {25,42,51},
    {37,38,46,47}, {39,40,48,49}, {41,42,50,51}, {37,43,54}, {38,43,52,55},
    {39,44,52,56}, {40,44,53,57}, {41,45,53,58}, {42,45,59}, {47,48,55,56},
    {49,50,57,58}, {46,60}, {47,52,60,63}, {48,52,61,64}, {49,53,61,65},
    {50,53,62,66}, {51,62}, {54,55,63}, {56,57,64,65}, {58,59,66}, {55,60,67},
    {56,61,67,69}, {57,61,68,70}, {58,62,68}, {63,64,69}, {65,66,70}, {64,67,71}, {65,68,71}, {69, 70}
};

// Adjacent course criterion for each course criterion
const std::vector<std::vector<int>> CriterionAdjCriterion = {
    {1,3},{0,4},{3,7},{0,2,8},{1,5,9},{4,10},{7,12},{2,6,13},
    {3,9,14},{4,8,15},{5,11,16},{10,17},{6,18},{7,14,19},{8,13,20},
    {9,16,21},{10,15,22},{11,23},{12,19,24},{13,18,25},{14,21,26},
    {15,20,27},{16,23,28},{17,22,29},{18,30},{19,26,31},{20,25,32},
    {21,28,33},{22,27,34},{23,35},{24,31,36},{25,30,37},{26,33,38},
    {27,32,39},{28,35,40},{29,34,41},{30,42},{31,38,43},{32,37,44},
    {33,40,45},{34,39,46},{35,47},{36,43},{37,42,48},{38,45,49},{39,44,50},
    {40,47,51},{41,46},{43,49},{44,48,50},{45,51,53},{46,50},{49,53},{50,52}
};

// Adjacent goals for each course criterion
const std::vector<std::vector<int>> CriterionAdjGoals = {
    {0,1},{0,2},{3,5},{1,3,6},{2,4,7},{4,8},{9,12},{5,9,13},
    {6,10,14},{7,10,15},{8,11,16},{11,17},{12,20},{13,18,21},{14,18,22},
    {15,19,23},{16,19,24},{17,25},{20,26,29},{21,26,30},{22,27,31},{23,27,32},
    {24,28,33},{25,28,34},{29,37},{30,35,38},{31,35,39},{32,36,40},{33,36,41},{34,42},
    {37,43,46},{38,43,47},{39,44,48},{40,44,49},{41,45,50},{42,45,51},{46,54},{47,52,55},
    {48,52,56},{49,53,57},{50,53,58},{51,59},{54,60},{55,60,63},{56,61,64},{57,61,65},
    {58,62,66},{59,62},{63,67},{64,67,69},{65,68,70},{66,68},{69,71},{70,71}
};

// goal indices for each tile stored as vectors
const std::vector<std::vector<int>> tilegoals = {
    {0, 1, 2, 6, 7, 10},
    {3, 5, 6, 13, 14, 18},
    {4, 7, 8, 15, 16, 19},
    {9, 12, 13, 20, 21, 26},
    {10, 14, 15, 22, 23, 27},
    {11, 16, 17, 24, 25, 28},
    {18, 21, 22, 30, 31, 35},
    {19, 23, 24, 32, 33, 36},
    {26, 29, 30, 37, 38, 43},
    {27, 31, 32, 39, 40, 44},
    {28, 33, 34, 41, 42, 45},
    {35, 38, 39, 47, 48, 52},
    {36, 40, 41, 49, 50, 53},
    {43, 46, 47, 54, 55, 60},
    {44, 48, 49, 56, 57, 61},
    {45, 50, 51, 58, 59, 62},
    {52, 55, 56, 63, 64, 67},
    {53, 57, 58, 65, 66, 68},
    {61, 64, 65, 69, 70, 71}
};

// Resource names to be used for Tile
const std::vector<std::string> Board::resource_names = {
    "CAFFEINE",
    "LAB",
    "LECTURE",
    "STUDY",
    "TUTORIAL",
    "NETFLIX"
};


// Printing constants used by << overload

// Leading blanks for the board;
const std::string leadblank1 = "                                   |";
const std::string leadblank2 = "                                   /            \\";
const std::string leadblank3 = "                                 ";
const std::string leadblank4 = "                                 /     ";
const std::string leadblank5 = "                    |";
const std::string leadblank6 = "                    /            ";
const std::string leadblank7 = "                  ";
const std::string leadblank8 = "                  /     ";
const std::string leadblank9 = "     |";
const std::string leadblank10 = "     /            ";
const std::string leadblank11 = "   ";
const std::string leadblank12 = "   /     ";
const std::string leadblank13 = "                                   \\            /";
const std::string leadblank14 = "     \\            /     ";
const std::string leadblank15 = "                    \\            /     ";


// Commonly used strings
const std::string blank1 = "      ";
const std::string blank2 = "             ";
const std::string blank3 = "            ";
const std::string blank4 = "     ";
const std::string top1 = "|--";
const std::string top2 = "--|";
const std::string middle1 = "\\            /     ";
const std::string middle2 = "\\            /";
const std::string middle3 = "            \\";
const std::string middle4 = "       |";
const std::string middle5 = "|       ";

// Useful methods for calculating ids of criteria based on a given id
// gives the coordinate of the vertex below the provided coordinate
int down_course_criterion_coord(int n) {
    if (n < 2 || n > 48) {
        return n + 3;
    } else if (n < 6 || n > 42) {
        return n + 5;
    } else {
        return n + 6;
    }
}

// gives the row number of the provided tile coordinate
int row_number(int tilenum) {
    if (tilenum == 0) {
        return 0;
    } else if (tilenum == 18) {
        return 9;
    } else if (((tilenum % 5) == 1) || ((tilenum % 5) == 2)) {
        return (2 * (tilenum / 5)) + 1;
    } else {
        return (2 *(tilenum / 5)) + 2;
    }
}

// provides the top-left vertex of the provided tile coordinate
int first_course_criterion(int tilenum) {
    if (tilenum < 6) {
        return tilenum * 2;
    } else if (tilenum == 18) {
        return 44;
    } else {
        return (tilenum * 2) + (row_number(tilenum) - 2);
    }
}

// prints GEESE if the tile is a goosetile, blank otherwise
std::string Board::goose_printer(std::string tile) const {
    int tile_num = std::stoi(tile);
    if (goose_tile == tile_num) {
        return "\\     GEESE      /";
    } else {
        return "\\                /";
    }
}

// Board constructor
Board::Board(unsigned seed): goose_tile{-1} {
    //  Randomizing our tiles
    std::default_random_engine rng{seed};

    // ============================================================
    //  Initialize all objects
    // ============================================================
    
    // store unique pointers for safe access to members within a vector
    for (int i = 0; i < num_of_course_criteria; ++i) {
        course_criteria.emplace_back(std::make_unique<Criteria>(i));
    }
    for (int i = 0; i < num_of_goals; ++i) {
        goals.emplace_back(std::make_unique<Goal>(i));
    }

    // construct tiles, using random generation for resource type.
    for (int i = 0; i < num_of_tiles; ++i) {
        int resource_type = rng() % 6;

        // x % 11 results has range of 0 - 10, then add 2 to get 2 - 12 as desired
        int dice_val = (rng() % 11) + 2;
        //tiles.emplace_back(resource_names[resource_type], dice_val, i);
        tiles.emplace_back(std::make_unique<Tile>(resource_names[resource_type], dice_val, i));
    }

    // ============================================================
    //  Assign each goal its adjacent course_criteria and goals
    // ============================================================
    for (int e = 0; e < num_of_goals; ++e) {
        goals[e]->set_adjacent_criteria(GoalsAdjCriterion.at(e));
        goals[e]->set_adjacent_goals(GoalsAdjGoals.at(e));
    }

    for (int i = 0; i < num_of_course_criteria; ++i) {
        course_criteria[i]->set_adjacent_criteria(CriterionAdjCriterion.at(i));
        course_criteria[i]->set_adjacent_goals(CriterionAdjGoals.at(i));
        
        /* Pointer solution: use ids instead for more uniform checks
        for (int idx : CriterionAdjCriterion[i]) {
            course_criteria[i].addAdjacentcourse_criterion(&course_criteria[idx]);
        }
        */
    }

    // ===================================================================
    // Giving tiles the goals that border it
    //
    // No algorithm because the relationship between the goals and tilenum 
    // a bit convoluted: 
    // - there would be two patterns for goals (top sides vs other sides)
    // =====================================================================
    for (int t = 0; t < num_of_tiles; ++t) {
        for (int e_idx : tilegoals[t]) {
            if (e_idx < goals.size()) {
                tiles[t]->add_goal(goals[e_idx].get());
            }
        }
    }
    // ============================================================
    // Created algorithm for course_criteria based on tile numbers
    // ============================================================
    for (int t = 0; t < num_of_tiles; ++t) {
        int course_criterion1 = first_course_criterion(std::stoi(tiles[t]->get_tilenum()));
        int course_criterion2 = course_criterion1 + 1;
        int course_criterion3 = down_course_criterion_coord(course_criterion1);
        int course_criterion4 = course_criterion3 + 1; 
        int course_criterion5 = down_course_criterion_coord(course_criterion3);
        int course_criterion6 = course_criterion5 + 1;
        tiles[t]->add_criteria(course_criteria[course_criterion1].get());
        tiles[t]->add_criteria(course_criteria[course_criterion2].get());
        tiles[t]->add_criteria(course_criteria[course_criterion3].get());
        tiles[t]->add_criteria(course_criteria[course_criterion4].get());
        tiles[t]->add_criteria(course_criteria[course_criterion5].get());
        tiles[t]->add_criteria(course_criteria[course_criterion6].get());
    }
}

// Save methods
void Board::load_save_data(std::vector<int> save_data) {
    // resType r = static_cast<resType>(save_data[i]);

    for (int i = 0; i < save_data.size(); i += 2) {
        int resource_type = save_data[i];
        int dice_val = save_data[i+1];
        if (resource_type == 5){
            continue;
        } else {
            //tiles.emplace_back(resource_names[resource_type], dice_val, i/2);
            tiles.emplace_back(std::make_unique<Tile>(resource_names[resource_type], dice_val, i/2));
        }
    }
}

std::string Board::get_save_string() {
    std::ostringstream oss;
    for (int i = 0; i < tiles.size(); i++) {
        std::string target_resource = tiles[i]->get_resource(false);

        // loop through resource names, add matching index to output stream
        for (int j = 0; j < resource_names.size(); j++) {
            if (resource_names[j] == target_resource) {
                oss << j;
                break;
            }
        }

        oss << ' ' << tiles[i]->get_tilenum(false) << ' ';
    }
    return oss.str();
}

// notifies the tiles based on the roll number
void Board::update_tiles(int roll_num) const {
    for (int i = 0; i < tiles.size(); ++i) {
        if(std::stoi(tiles[i]->get_dice(false)) == roll_num && i != goose_tile){
            tiles[i]->distribute_resources();
        }
        // else nothing
    }
}

// returns the criteria at that location
Criteria* Board::get_criteria(int criteria_num) const {
    // returns a raw pointer, no worries that Player will outlive Board
    // they will both die alongside Game
    return course_criteria[criteria_num].get();
}

// returns the goal at that location
Goal* Board::get_goal(int goal_num) const {
    // returns raw pointer, again no worries that Player will be able to access
    // post deletion as both will die alongside Game
    return goals[goal_num].get();
}


std::ostream &operator<<(std::ostream &out, const Board &b) {

    // Printing the board using our constants
    // Those with eyes: beware!
    // Skip the next few lines for your own good...
    out << leadblank1 << b.course_criteria[0]->get_num() << top1 << b.goals[0]->get_num() << top2 << b.course_criteria[1]->get_num() << "|" <<std::endl;
    out << leadblank2 <<std::endl;
    out << leadblank3 << b.goals[1]->get_num() << blank1 << b.tiles[0]->get_tilenum() << blank4 << b.goals[2]->get_num() <<std::endl;
    out << leadblank4 << b.tiles[0]->get_resource() << "\\" <<std::endl;
    out << leadblank5 << b.course_criteria[2]->get_num() << top1 << b.goals[3]->get_num() << top2 << b.course_criteria[3]->get_num() << middle5 << b.tiles[0]->get_dice() << middle4 << b.course_criteria[4]->get_num() << top1 << b.goals[4]->get_num() << top2 << b.course_criteria[5]->get_num() << "|" <<std::endl;
    out << leadblank6 << b.goose_printer(b.tiles[0]->get_tilenum()) << middle3 <<std::endl;
    out << leadblank7 << b.goals[5]->get_num() << blank1 << b.tiles[1]->get_tilenum() << blank4 << b.goals[6]->get_num() << blank2 << b.goals[7]->get_num() << blank1 << b.tiles[2]->get_tilenum() << blank4 << b.goals[8]->get_num() <<std::endl;
    out << leadblank8 << b.tiles[1]->get_resource() << middle1 << b.tiles[2]->get_resource() << "\\" <<std::endl;
    out << leadblank9 << b.course_criteria[6]->get_num() << top1 << b.goals[9]->get_num() << top2 << b.course_criteria[7]->get_num() << middle5 << b.tiles[1]->get_dice() << middle4 << b.course_criteria[8]->get_num() << top1 << b.goals[10]->get_num() << top2 << b.course_criteria[9]->get_num() << middle5 << b.tiles[2]->get_dice() << middle4 << b.course_criteria[10]->get_num() << top1 << b.goals[11]->get_num() << top2 << b.course_criteria[11]->get_num() << "|" <<std::endl;
    out << leadblank10 << b.goose_printer(b.tiles[1]->get_tilenum()) << blank3 << b.goose_printer(b.tiles[2]->get_tilenum()) << middle3 <<std::endl;
    out << leadblank11 << b.goals[12]->get_num() << blank1 << b.tiles[3]->get_tilenum() << blank4 << b.goals[13]->get_num() << blank2 << b.goals[14]->get_num() << blank1 << b.tiles[4]->get_tilenum() << blank4 << b.goals[15]->get_num() << blank2 << b.goals[16]->get_num() << blank1 << b.tiles[5]->get_tilenum() << blank4 << b.goals[17]->get_num() <<std::endl;
    out << leadblank12 << b.tiles[3]->get_resource() << middle1 << b.tiles[4]->get_resource() << middle1 << b.tiles[5]->get_resource() << "\\" <<std::endl;
    out << "|" << b.course_criteria[12]->get_num() << middle5 << b.tiles[3]->get_dice() << middle4 << b.course_criteria[13]->get_num() << top1 << b.goals[18]->get_num() << top2 << b.course_criteria[14]->get_num() << middle5 << b.tiles[4]->get_dice() << middle4 << b.course_criteria[15]->get_num() << top1 << b.goals[19]->get_num() << top2 << b.course_criteria[16]->get_num() << middle5 << b.tiles[5]->get_dice() << middle4 << b.course_criteria[17]->get_num() << "|" <<std::endl;
    out << leadblank11 << b.goose_printer(b.tiles[3]->get_tilenum()) << blank3 << b.goose_printer(b.tiles[4]->get_tilenum()) << blank3 << b.goose_printer(b.tiles[5]->get_tilenum()) <<std::endl;
    out << leadblank11 << b.goals[20]->get_num() << blank2 << b.goals[21]->get_num() << blank1 << b.tiles[6]->get_tilenum() << blank4 << b.goals[22]->get_num() << blank2 << b.goals[23]->get_num() << blank1 << b.tiles[7]->get_tilenum() << blank4 << b.goals[24]->get_num() << blank2 << b.goals[25]->get_num() <<std::endl;
    out << leadblank14 << b.tiles[6]->get_resource() << middle1 << b.tiles[7]->get_resource() << middle2 <<std::endl;
    out << leadblank9 << b.course_criteria[18]->get_num() << top1 << b.goals[26]->get_num() << top2 << b.course_criteria[19]->get_num() << middle5 << b.tiles[6]->get_dice() << middle4 << b.course_criteria[20]->get_num() << top1 << b.goals[27]->get_num() << top2 << b.course_criteria[21]->get_num() << middle5 << b.tiles[7]->get_dice() << middle4 << b.course_criteria[22]->get_num() << top1 << b.goals[28]->get_num() << top2 << b.course_criteria[23]->get_num() << "|" <<std::endl;
    out << leadblank10 << b.goose_printer(b.tiles[6]->get_tilenum()) << blank3 << b.goose_printer(b.tiles[7]->get_tilenum()) << middle3 <<std::endl;
    out << leadblank11 << b.goals[29]->get_num() << blank1 << b.tiles[8]->get_tilenum() << blank4 << b.goals[30]->get_num() << blank2 << b.goals[31]->get_num() << blank1 << b.tiles[9]->get_tilenum() << blank4 << b.goals[32]->get_num() << blank2 << b.goals[33]->get_num() << blank1 << b.tiles[10]->get_tilenum() << blank4 << b.goals[34]->get_num() <<std::endl;
    out << leadblank12 << b.tiles[8]->get_resource() << middle1 << b.tiles[9]->get_resource() << middle1 << b.tiles[10]->get_resource() << "\\" <<std::endl;
    out << "|" << b.course_criteria[24]->get_num() << middle5 << b.tiles[8]->get_dice() << middle4 << b.course_criteria[25]->get_num() << top1 << b.goals[35]->get_num() << top2 << b.course_criteria[26]->get_num() << middle5 << b.tiles[9]->get_dice() << middle4 << b.course_criteria[27]->get_num() << top1 << b.goals[36]->get_num() << top2 << b.course_criteria[28]->get_num() << middle5 << b.tiles[10]->get_dice() << middle4 << b.course_criteria[29]->get_num() << "|" <<std::endl;
    out << leadblank11 << b.goose_printer(b.tiles[8]->get_tilenum()) << blank3 << b.goose_printer(b.tiles[9]->get_tilenum()) << blank3 << b.goose_printer(b.tiles[10]->get_tilenum()) <<std::endl;
    out << leadblank11 << b.goals[37]->get_num() << blank2 << b.goals[38]->get_num() << blank1 << b.tiles[11]->get_tilenum() << blank4 << b.goals[39]->get_num() << blank2 << b.goals[40]->get_num() << blank1 << b.tiles[12]->get_tilenum() << blank4 << b.goals[41]->get_num() << blank2 << b.goals[42]->get_num() <<std::endl;
    out << leadblank14 << b.tiles[11]->get_resource() << middle1 << b.tiles[12]->get_resource() << middle2 <<std::endl;
    out << leadblank9 << b.course_criteria[30]->get_num() << top1 << b.goals[43]->get_num() << top2 << b.course_criteria[31]->get_num() << middle5 << b.tiles[11]->get_dice() << middle4 << b.course_criteria[32]->get_num() << top1 << b.goals[44]->get_num() << top2 << b.course_criteria[33]->get_num() << middle5 << b.tiles[12]->get_dice() << middle4 << b.course_criteria[34]->get_num() << top1 << b.goals[45]->get_num() << top2 << b.course_criteria[35]->get_num() << "|" <<std::endl;
    out << leadblank10 << b.goose_printer(b.tiles[11]->get_tilenum()) << blank3 << b.goose_printer(b.tiles[12]->get_tilenum()) << middle3 <<std::endl;
    out << leadblank11 << b.goals[46]->get_num() << blank1 << b.tiles[13]->get_tilenum() << blank4 << b.goals[47]->get_num() << blank2 << b.goals[48]->get_num() << blank1 << b.tiles[14]->get_tilenum() << blank4 << b.goals[49]->get_num() << blank2 << b.goals[50]->get_num() << blank1 << b.tiles[15]->get_tilenum() << blank4 << b.goals[51]->get_num() <<std::endl;
    out << leadblank12 << b.tiles[13]->get_resource() << middle1 << b.tiles[14]->get_resource() << middle1 << b.tiles[15]->get_resource() << "\\" <<std::endl;
    out << "|" << b.course_criteria[36]->get_num() << middle5 << b.tiles[13]->get_dice() << middle4 << b.course_criteria[37]->get_num() << top1 << b.goals[52]->get_num() << top2 << b.course_criteria[38]->get_num() << middle5 << b.tiles[14]->get_dice() << middle4 << b.course_criteria[39]->get_num() << top1 << b.goals[53]->get_num() << top2 << b.course_criteria[40]->get_num() << middle5 << b.tiles[15]->get_dice() << middle4 << b.course_criteria[41]->get_num() << "|" <<std::endl;
    out << leadblank11 << b.goose_printer(b.tiles[13]->get_tilenum()) << blank3 << b.goose_printer(b.tiles[14]->get_tilenum()) << blank3 << b.goose_printer(b.tiles[15]->get_tilenum()) <<std::endl;
    out << leadblank11 << b.goals[54]->get_num() << blank2 << b.goals[55]->get_num() << blank1 << b.tiles[16]->get_tilenum() << blank4 << b.goals[56]->get_num() << blank2 << b.goals[57]->get_num() << blank1 << b.tiles[17]->get_tilenum() << blank4 << b.goals[58]->get_num() << blank2 << b.goals[59]->get_num() <<std::endl;
    out << leadblank14 << b.tiles[16]->get_resource() << middle1 << b.tiles[17]->get_resource() << middle2 <<std::endl;
    out << leadblank9 << b.course_criteria[42]->get_num() << top1 << b.goals[60]->get_num() << top2 << b.course_criteria[43]->get_num() << middle5 << b.tiles[16]->get_dice() << middle4 << b.course_criteria[44]->get_num() << top1 << b.goals[61]->get_num() << top2 << b.course_criteria[45]->get_num() << middle5 << b.tiles[17]->get_dice() << middle4 << b.course_criteria[46]->get_num() << top1 << b.goals[62]->get_num() << top2 << b.course_criteria[47]->get_num() << "|" <<std::endl;
    out << leadblank7 << b.goose_printer(b.tiles[16]->get_tilenum()) << blank3 << b.goose_printer(b.tiles[17]->get_tilenum()) <<std::endl;
    out << leadblank7 << b.goals[63]->get_num() << blank2 << b.goals[64]->get_num() << blank1 << b.tiles[18]->get_tilenum() << blank4 << b.goals[65]->get_num() << blank2 << b.goals[66]->get_num() <<std::endl;
    out << leadblank15 << b.tiles[18]->get_resource() << middle2 <<std::endl;
    out << leadblank5 << b.course_criteria[48]->get_num() << top1 << b.goals[67]->get_num() << top2 << b.course_criteria[49]->get_num() << middle5 << b.tiles[18]->get_dice() << middle4 << b.course_criteria[50]->get_num() << top1 << b.goals[68]->get_num() << top2 << b.course_criteria[51]->get_num() << "|" <<std::endl;
    out << leadblank3 << b.goose_printer(b.tiles[18]->get_tilenum()) <<std::endl;
    out << leadblank3 << b.goals[69]->get_num() << blank2 << b.goals[70]->get_num() <<std::endl;
    out << leadblank13 <<std::endl;
    out << leadblank1 << b.course_criteria[52]->get_num() << top1 << b.goals[71]->get_num() << top2 << b.course_criteria[53]->get_num() << "|" <<std::endl;
    return out;
    // hallelujah
}

// updating where the goose position is, assuming that out of bounds values
// indicates that the goose is off the board 
void Board::update_goose(int new_goose_tile) {
    // assumes that we are given a valid tilenum -> Game can check whether or not it is valid
    goose_tile = new_goose_tile;
}

// provides the tile where the goose is located
int Board::get_goose_tile() const {
    return goose_tile;
}

std::vector<std::string> Board::goose_victims() const {
    int goose_tile = get_goose_tile();
    if(goose_tile != -1){
        return tiles[goose_tile]->criteria_ids();
    } else {
        return {};
    }
}
