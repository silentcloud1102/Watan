module Board;

import <iostream>;
import <string>;
import <vector>;
import <stdexcept>;
import <algorithm>;
import <random>;
import Criteria;
import Goals;
import Tile;
import Resource;
import Student
using namespace std;

// gives the coordinate of the vertex below the provided coordinate
int down_vertex_coord(int n) {
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
int first_vertex(int tilenum) {
    if (tilenum < 6) {
        return tilenum * 2;
    } else if (tilenum == 18) {
        return 44;
    } else {
        return (tilenum * 2) + (row_number(tilenum) - 2);
    }
}

// prints GEESE if the tile is a goosetile, blank otherwise
string Board::goose_printer(string tile) const {
    int tile_num = stoi(tile);
    if (goose_tile == tile_num) {
        return "\\     GEESE      /";
    } else {
        return "\\                /";
    }
}

// Board constructor
Board::Board(unsigned seed) {
    goose_tile = -1;
    //  Randomizing our tiles
    default_random_engine rng{seed};

    // ========================================================================================
    // Creating our vectors of data below (board will be hardcoded)
    //
    //
    // Each index will represent the goal/criterion number 
    // i.e. GoalsAdjCriterion[5] is the criterion adjacent to goal 5 
    // (the 6th goal since we start counting from 0)
    // ========================================================================================


    // ============================================================
    //  Adjacent course criterion for each goal
    // ============================================================
    const vector<vector<int>> GoalsAdjCriterion = {
        {0, 1}, {0, 3}, {1, 4}, {2, 3}, {4, 5}, {2, 7}, {3, 8}, {4, 9}, {5, 10}, {6, 7}, {8, 9}, {10, 11},
        {6, 12}, {7, 13}, {8, 14}, {9, 15}, {10, 16}, {11, 17}, {13, 14}, {15, 16}, {12, 18}, {13, 19},
        {14, 20}, {15, 21}, {16, 22}, {17, 23}, {18, 19}, {20, 21}, {22, 23}, {18, 24}, {19, 25}, {20, 26},
        {21, 27}, {22, 28}, {23, 29}, {25, 26}, {27, 28}, {24, 30}, {25, 31}, {26, 32}, {27, 33}, {28, 34},
        {29, 35}, {30, 31}, {32, 33}, {34, 35}, {30, 36}, {31, 37}, {32, 38}, {33, 39}, {34, 40}, {35, 41},
        {37, 38}, {39, 40}, {36, 42}, {37, 43}, {38, 44}, {39, 45}, {40, 46}, {41, 47}, {42, 43}, {44, 45},
        {46, 47}, {43, 48}, {44, 49}, {45, 50}, {46, 51}, {47, 52}, {49, 50}, {48, 49}, {50, 53}, {52, 53}
    };
    // ============================================================
    //  Adjacent goals for each goal
    // ============================================================
    const vector<vector<int>> GoalsAdjGoals = {
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
    // ============================================================
    // Adjacent course criterion for each course criterion
    // ============================================================
    vector<vector<int>> CriterionAdjCriterion = {
        {1,3},{0,4},{3,7},{0,2,8},{1,5,9},{4,10},{7,12},{2,6,13},
        {3,9,14},{4,8,15},{5,11,16},{10,17},{6,18},{7,14,19},{8,13,20},
        {9,16,21},{10,15,22},{11,23},{12,19,24},{13,18,25},{14,21,26},
        {15,20,27},{16,23,28},{17,22,29},{18,30},{19,26,31},{20,25,32},
        {21,28,33},{22,27,34},{23,35},{24,31,36},{25,30,37},{26,33,38},
        {27,32,39},{28,35,40},{29,34,41},{30,42},{31,38,43},{32,37,44},
        {33,40,45},{34,39,46},{35,47},{36,43},{37,42,48},{38,45,49},{39,44,50},
        {40,47,51},{41,46},{43,49},{44,48,50},{45,51,53},{46,50},{49,53},{50,52}
    };
    // ============================================================
    // Adjacent goals for each course criterion
    // ============================================================
    vector<vector<int>> CriterionAdjGoals = {
        {0,1},{0,2},{3,5},{1,3,6},{2,4,7},{4,8},{9,12},{5,9,13},
        {6,10,14},{7,10,15},{8,11,16},{11,17},{12,20},{13,18,21},{14,18,22},
        {15,19,23},{16,19,24},{17,25},{20,26,29},{21,26,30},{22,27,31},{23,27,32},
        {24,28,33},{25,28,34},{29,37},{30,35,38},{31,35,39},{32,36,40},{33,36,41},{34,42},
        {37,43,46},{38,43,47},{39,44,48},{40,44,49},{41,45,50},{42,45,51},{46,54},{47,52,55},
        {48,52,56},{49,53,57},{50,53,58},{51,59},{54,60},{55,60,63},{56,61,64},{57,61,65},
        {58,62,66},{59,62},{63,67},{64,67,69},{65,68,70},{66,68},{69,71},{70,71}
    };
    // ============================================================
    // goal indices for each tile (local array)
    // ============================================================
    const vector<vector<int>> tilegoals = {
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
    // ============================================================
    //  Initialize all objects
    // ============================================================
    vector<string> resource_names = {
        "CAFFEINE",
        "LAB",
        "LECTURE",
        "STUDY",
        "TUTORIAL",
        "NETFLIX"
    };

    // constants for the desired sizes, to initialize and improve readability
    int num_of_goals = 72;
    int num_of_course_criteria = 54
    int num_of_tiles = 19;

    for (int i = 0; i < num_of_course_criteria; ++i) {
        course_criteria.emplace_back(i);
    }
    for (int i = 0; i < num_of_goals; ++i) {
        goals.emplace_back(i);
    }
    for (int i = 0; i < num_of_tiles; ++i) {
        int resource_type = rng() % 6;
        int dice_val = (rng() % 11) + 2;
        tiles.emplace_back(resource_names[resource_type], dice_val, i);
    }
    // ============================================================
    //  Assign each goal its adjacent course_criteria and goals
    // ============================================================
    for (int e = 0; e < num_of_goals; ++e) {
        goals[e].set_adjacent_criteria(GoalsAdjCriterion.at(e));
        goals[e].set_adjacent_goals(GoalsAdjGoals.at(e));
    }
    for (int i = 0; i < num_of_course_criteria; ++i) {
        
        
        /* Pointer solution: use ids instead for more uniform checks
        for (int idx : CriterionAdjCriterion[i]) {
            course_criteria[i].addAdjacentcourse_criterion(&course_criteria[idx]);
        }
        */

        course_criteria[i].set_adjacent_criteria(CriterionAdjCriterion.at(i));
        course_criteria[i].set_adjacent_goals(CriterionAdjGoals.at(i));
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
                tiles[t].addgoal(goals[e_idx]);
            }
        }
    }
    // ============================================================
    // Created algorithm for course_criteria based on tile numbers
    // ============================================================
    for (int t = 0; t < num_of_tiles; ++t) {
        int course_criterion1 = first_course_criterion(stoi(tiles[t].getTilenum()));
        int course_criterion2 = course_criterion1 + 1;
        int course_criterion3 = down_course_criterion_coord(course_criterion1);
        int course_criterion4 = course_criterion3 + 1; 
        int course_criterion5 = down_course_criterion_coord(course_criterion3);
        int course_criterion6 = course_criterion5 + 1;
        tiles[t].addcourse_criterion(course_criteria[course_criterion1]);
        tiles[t].addcourse_criterion(course_criteria[course_criterion2]);
        tiles[t].addcourse_criterion(course_criteria[course_criterion3]);
        tiles[t].addcourse_criterion(course_criteria[course_criterion4]);
        tiles[t].addcourse_criterion(course_criteria[course_criterion5]);
        tiles[t].addcourse_criterion(course_criteria[course_criterion6]);
    }
}

void Board::load_saveData(vector<int> save_data) {
    vector<string> resource_names = {
        "CAFFEINE",
        "LAB",
        "LECTURE",
        "STUDY",
        "TUTORIAL",
        "NETFLIX"
    };

    // resType r = static_cast<resType>(save_data[i]);

    for (int i = 0; i < save_data.size(); i += 2) {
        int resource_type = save_data[i];
        int dice_val = save_data[i+1];
        if (resource_type == 5){
            continue;
        } else {
            tiles.emplace_back(resource_names[resource_type], dice_val, i/2);
        }
    }
}

string Board::saveData() {
    // resource names have trailing spaces since getResource() outputs the string with
    // trailing spaces to have the board print properly
    vector<string> resource_names_with_spaces = {
        "CAFFEINE   ",
        "LAB        ",
        "LECTURE    ",
        "STUDY      ",
        "TUTORIAL   ",
        "NETFLIX    "
    };
    string saved_data = "";
    for (int i = 0; i < tiles.size(); i++) {
        int resource_type = 0;
        for (int j = 0; j < resource_names_with_spaces.size(); j++) {
            if (resource_names_with_spaces[j] == tiles[i].getResource()) {
                resource_type = to_string(j) + " ";
            }
        }
        saved_data + resource_type;
        if (i != 18) {
            saved_data += tiles[i].getTileNum() + " ";
        } else {
            saved_data += tiles[i].getTileNum();
        }
    }
    return saved_data;
}

// notifies the tiles based on the roll number
void Board::update_tiles(int roll_num) const {
    for (int i = 0; i < tiles.size(); ++i) {
        if (i != goose_tile) {
            tiles[i].distributeResources();
        }
    }
}

// returns the criteria at that location
Criteria& Board::getCriteria(int criteria_num) const {
    return course_criterion[criteria_num];
}

// returns the goal at that location
Goal& Board::getGoals(int goal_num) const {
    return goals[goal_num];
}

ostream &operator<<(ostream &out, const Board &b) {
    // ============================================================
    // Leading blanks for the board;
    // ============================================================
    string leadblank1 = "                                   |";
    string leadblank2 = "                                   /            \\";
    string leadblank3 = "                                 ";
    string leadblank4 = "                                 /     ";
    string leadblank5 = "                    |";
    string leadblank6 = "                    /            ";
    string leadblank7 = "                  ";
    string leadblank8 = "                  /     ";
    string leadblank9 = "     |";
    string leadblank10 = "     /            ";
    string leadblank11 = "   ";
    string leadblank12 = "   /     ";
    string leadblank13 = "                                   \\            /";
    string leadblank14 = "     \\            /     ";
    string leadblank15 = "                    \\            /     ";

    // ============================================================
    // Commonly used strings
    // ============================================================
    string blank1 = "      ";
    string blank2 = "             ";
    string blank3 = "            ";
    string blank4 = "     ";
    string top1 = "|--";
    string top2 = "--|";
    string middle1 = "\\            /     ";
    string middle2 = "\\            /";
    string middle3 = "            \\";
    string middle4 = "       |";
    string middle5 = "|       ";


    // ============================================================
    // Printing the board using our constants
    // ============================================================
    out << leadblank1 << b.course_criteria[0].getnum() << top1 << b.goals[0].getnum() << top2 << b.course_criteria[1].getnum() << "|" << endl;
    out << leadblank2 << endl;
    out << leadblank3 << b.goals[1].getnum() << blank1 << b.tiles[0].getTilenum() << blank4 << b.goals[2].getnum() << endl;
    out << leadblank4 << b.tiles[0].getResource() << "\\" << endl;
    out << leadblank5 << b.course_criteria[2].getnum() << top1 << b.goals[3].getnum() << top2 << b.course_criteria[3].getnum() << middle5 << b.tiles[0].getDice() << middle4 << b.course_criteria[4].getnum() << top1 << b.goals[4].getnum() << top2 << b.course_criteria[5].getnum() << "|" << endl;
    out << leadblank6 << b.goose_printer(b.tiles[0].getTilenum()) << middle3 << endl;
    out << leadblank7 << b.goals[5].getnum() << blank1 << b.tiles[1].getTilenum() << blank4 << b.goals[6].getnum() << blank2 << b.goals[7].getnum() << blank1 << b.tiles[2].getTilenum() << blank4 << b.goals[8].getnum() << endl;
    out << leadblank8 << b.tiles[1].getResource() << middle1 << b.tiles[2].getResource() << "\\" << endl;
    out << leadblank9 << b.course_criteria[6].getnum() << top1 << b.goals[9].getnum() << top2 << b.course_criteria[7].getnum() << middle5 << b.tiles[1].getDice() << middle4 << b.course_criteria[8].getnum() << top1 << b.goals[10].getnum() << top2 << b.course_criteria[9].getnum() << middle5 << b.tiles[2].getDice() << middle4 << b.course_criteria[10].getnum() << top1 << b.goals[11].getnum() << top2 << b.course_criteria[11].getnum() << "|" << endl;
    out << leadblank10 << b.goose_printer(b.tiles[1].getTilenum()) << blank3 << b.goose_printer(b.tiles[2].getTilenum()) << middle3 << endl;
    out << leadblank11 << b.goals[12].getnum() << blank1 << b.tiles[3].getTilenum() << blank4 << b.goals[13].getnum() << blank2 << b.goals[14].getnum() << blank1 << b.tiles[4].getTilenum() << blank4 << b.goals[15].getnum() << blank2 << b.goals[16].getnum() << blank1 << b.tiles[5].getTilenum() << blank4 << b.goals[17].getnum() << endl;
    out << leadblank12 << b.tiles[3].getResource() << middle1 << b.tiles[4].getResource() << middle1 << b.tiles[5].getResource() << "\\" << endl;
    out << "|" << b.course_criteria[12].getnum() << middle5 << b.tiles[3].getDice() << middle4 << b.course_criteria[13].getnum() << top1 << b.goals[18].getnum() << top2 << b.course_criteria[14].getnum() << middle5 << b.tiles[4].getDice() << middle4 << b.course_criteria[15].getnum() << top1 << b.goals[19].getnum() << top2 << b.course_criteria[16].getnum() << middle5 << b.tiles[5].getDice() << middle4 << b.course_criteria[17].getnum() << "|" << endl;
    out << leadblank11 << b.goose_printer(b.tiles[3].getTilenum()) << blank3 << b.goose_printer(b.tiles[4].getTilenum()) << blank3 << b.goose_printer(b.tiles[5].getTilenum()) << endl;
    out << leadblank11 << b.goals[20].getnum() << blank2 << b.goals[21].getnum() << blank1 << b.tiles[6].getTilenum() << blank4 << b.goals[22].getnum() << blank2 << b.goals[23].getnum() << blank1 << b.tiles[7].getTilenum() << blank4 << b.goals[24].getnum() << blank2 << b.goals[25].getnum() << endl;
    out << leadblank14 << b.tiles[6].getResource() << middle1 << b.tiles[7].getResource() << middle2 << endl;
    out << leadblank9 << b.course_criteria[18].getnum() << top1 << b.goals[26].getnum() << top2 << b.course_criteria[19].getnum() << middle5 << b.tiles[6].getDice() << middle4 << b.course_criteria[20].getnum() << top1 << b.goals[27].getnum() << top2 << b.course_criteria[21].getnum() << middle5 << b.tiles[7].getDice() << middle4 << b.course_criteria[22].getnum() << top1 << b.goals[28].getnum() << top2 << b.course_criteria[23].getnum() << "|" << endl;
    out << leadblank10 << b.goose_printer(b.tiles[6].getTilenum()) << blank3 << b.goose_printer(b.tiles[7].getTilenum()) << middle3 << endl;
    out << leadblank11 << b.goals[29].getnum() << blank1 << b.tiles[8].getTilenum() << blank4 << b.goals[30].getnum() << blank2 << b.goals[31].getnum() << blank1 << b.tiles[9].getTilenum() << blank4 << b.goals[32].getnum() << blank2 << b.goals[33].getnum() << blank1 << b.tiles[10].getTilenum() << blank4 << b.goals[34].getnum() << endl;
    out << leadblank12 << b.tiles[8].getResource() << middle1 << b.tiles[9].getResource() << middle1 << b.tiles[10].getResource() << "\\" << endl;
    out << "|" << b.course_criteria[24].getnum() << middle5 << b.tiles[8].getDice() << middle4 << b.course_criteria[25].getnum() << top1 << b.goals[35].getnum() << top2 << b.course_criteria[26].getnum() << middle5 << b.tiles[9].getDice() << middle4 << b.course_criteria[27].getnum() << top1 << b.goals[36].getnum() << top2 << b.course_criteria[28].getnum() << middle5 << b.tiles[10].getDice() << middle4 << b.course_criteria[29].getnum() << "|" << endl;
    out << leadblank11 << b.goose_printer(b.tiles[8].getTilenum()) << blank3 << b.goose_printer(b.tiles[9].getTilenum()) << blank3 << b.goose_printer(b.tiles[10].getTilenum()) << endl;
    out << leadblank11 << b.goals[37].getnum() << blank2 << b.goals[38].getnum() << blank1 << b.tiles[11].getTilenum() << blank4 << b.goals[39].getnum() << blank2 << b.goals[40].getnum() << blank1 << b.tiles[12].getTilenum() << blank4 << b.goals[41].getnum() << blank2 << b.goals[42].getnum() << endl;
    out << leadblank14 << b.tiles[11].getResource() << middle1 << b.tiles[12].getResource() << middle2 << endl;
    out << leadblank9 << b.course_criteria[30].getnum() << top1 << b.goals[43].getnum() << top2 << b.course_criteria[31].getnum() << middle5 << b.tiles[11].getDice() << middle4 << b.course_criteria[32].getnum() << top1 << b.goals[44].getnum() << top2 << b.course_criteria[33].getnum() << middle5 << b.tiles[12].getDice() << middle4 << b.course_criteria[34].getnum() << top1 << b.goals[45].getnum() << top2 << b.course_criteria[35].getnum() << "|" << endl;
    out << leadblank10 << b.goose_printer(b.tiles[11].getTilenum()) << blank3 << b.goose_printer(b.tiles[12].getTilenum()) << middle3 << endl;
    out << leadblank11 << b.goals[46].getnum() << blank1 << b.tiles[13].getTilenum() << blank4 << b.goals[47].getnum() << blank2 << b.goals[48].getnum() << blank1 << b.tiles[14].getTilenum() << blank4 << b.goals[49].getnum() << blank2 << b.goals[50].getnum() << blank1 << b.tiles[15].getTilenum() << blank4 << b.goals[51].getnum() << endl;
    out << leadblank12 << b.tiles[13].getResource() << middle1 << b.tiles[14].getResource() << middle1 << b.tiles[15].getResource() << "\\" << endl;
    out << "|" << b.course_criteria[36].getnum() << middle5 << b.tiles[13].getDice() << middle4 << b.course_criteria[37].getnum() << top1 << b.goals[52].getnum() << top2 << b.course_criteria[38].getnum() << middle5 << b.tiles[14].getDice() << middle4 << b.course_criteria[39].getnum() << top1 << b.goals[53].getnum() << top2 << b.course_criteria[40].getnum() << middle5 << b.tiles[15].getDice() << middle4 << b.course_criteria[41].getnum() << "|" << endl;
    out << leadblank11 << b.goose_printer(b.tiles[13].getTilenum()) << blank3 << b.goose_printer(b.tiles[14].getTilenum()) << blank3 << b.goose_printer(b.tiles[15].getTilenum()) << endl;
    out << leadblank11 << b.goals[54].getnum() << blank2 << b.goals[55].getnum() << blank1 << b.tiles[16].getTilenum() << blank4 << b.goals[56].getnum() << blank2 << b.goals[57].getnum() << blank1 << b.tiles[17].getTilenum() << blank4 << b.goals[58].getnum() << blank2 << b.goals[59].getnum() << endl;
    out << leadblank14 << b.tiles[16].getResource() << middle1 << b.tiles[17].getResource() << middle2 << endl;
    out << leadblank9 << b.course_criteria[42].getnum() << top1 << b.goals[60].getnum() << top2 << b.course_criteria[43].getnum() << middle5 << b.tiles[16].getDice() << middle4 << b.course_criteria[44].getnum() << top1 << b.goals[61].getnum() << top2 << b.course_criteria[45].getnum() << middle5 << b.tiles[17].getDice() << middle4 << b.course_criteria[46].getnum() << top1 << b.goals[62].getnum() << top2 << b.course_criteria[47].getnum() << "|" << endl;
    out << leadblank7 << b.goose_printer(b.tiles[16].getTilenum()) << blank3 << b.goose_printer(b.tiles[17].getTilenum()) << endl;
    out << leadblank7 << b.goals[63].getnum() << blank2 << b.goals[64].getnum() << blank1 << b.tiles[18].getTilenum() << blank4 << b.goals[65].getnum() << blank2 << b.goals[66].getnum() << endl;
    out << leadblank15 << b.tiles[18].getResource() << middle2 << endl;
    out << leadblank5 << b.course_criteria[48].getnum() << top1 << b.goals[67].getnum() << top2 << b.course_criteria[49].getnum() << middle5 << b.tiles[18].getDice() << middle4 << b.course_criteria[50].getnum() << top1 << b.goals[68].getnum() << top2 << b.course_criteria[51].getnum() << "|" << endl;
    out << leadblank3 << b.goose_printer(b.tiles[18].getTilenum()) << endl;
    out << leadblank3 << b.goals[69].getnum() << blank2 << b.goals[70].getnum() << endl;
    out << leadblank13 << endl;
    out << leadblank1 << b.course_criteria[52].getnum() << top1 << b.goals[71].getnum() << top2 << b.course_criteria[53].getnum() << "|" << endl;
    return out;
}

// updating where the goose position is, assuming that out of bounds values
// indicates that they wish to take the goose off the board 
// (also assumes main will ensure the values are correct, so it will accept any value)
void updateGoose(int new_goosetile) {
    // assumes that we are given a valid tilenum -> Game can check whether or not it is valid
    goose_tile = new_goosetile;
}

// provides the tile where the goose is located
int getGooseTile() const {
    return goose_tile;
}
