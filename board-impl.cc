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
using namespace std;

Board::Board(string seed = "") {
    // ============================================================
    //  Randomizing our tiles
    // ============================================================
    if (seed == "") {
        seed = "I am a random test case :)"; // same test case each time
    }
    default_random_engine rng{stoi(seed)};
    
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

    for (int i = 0; i < 54; ++i) {
        course_criteria.emplace_back(i);
    }
    for (int i = 0; i < 72; ++i) {
        goals.emplace_back(i);
    }
    for (int i = 0; i < 19; ++i) {
        int resource_type = rng() % 6;
        int dice_val = (rng() % 11) + 2;
        tiles.emplace_back(resource_names[resource_type], dice_val, i);
    }

    const vector<vector<int>> goalTocourse_criteria = {
        {0, 1}, {0, 3}, {1, 4}, {2, 3}, {4, 5}, {2, 7}, {3, 8}, {4, 9}, {5, 10}, {6, 7}, {8, 9}, {10, 11},
        {6, 12}, {7, 13}, {8, 14}, {9, 15}, {10, 16}, {11, 17}, {13, 14}, {15, 16}, {12, 18}, {13, 19},
        {14, 20}, {15, 21}, {16, 22}, {17, 23}, {18, 19}, {20, 21}, {22, 23}, {18, 24}, {19, 25}, {20, 26},
        {21, 27}, {22, 28}, {23, 29}, {25, 26}, {27, 28}, {24, 30}, {25, 31}, {26, 32}, {27, 33}, {28, 34},
        {29, 35}, {30, 31}, {32, 33}, {34, 35}, {30, 36}, {31, 37}, {32, 38}, {33, 39}, {34, 40}, {35, 41},
        {37, 38}, {39, 40}, {36, 42}, {37, 43}, {38, 44}, {39, 45}, {40, 46}, {41, 47}, {42, 43}, {44, 45},
        {46, 47}, {43, 48}, {44, 49}, {45, 50}, {46, 51}, {47, 52}, {49, 50}, {48, 49}, {50, 53}, {52, 53}
    };

    // ============================================================
    //  Goal → adjacent Goals
    // ============================================================
    const vector<vector<int>> goalAdj = {
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
    //  Assign each goal its adjacent course_criteria and goals
    // ============================================================
    for (int e = 0; e < 72; ++e) {
        goals[e].addAdjacentcourse_criterion(goalTocourse_criteria.at(e));
        goals[e].addAdjacentgoal(goalAdj.at(e));
    }

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

    // ===================================================================
    // Giving tiles the goals that border it
    //
    // No algorithm because the relationship between the goals and tilenum 
    // a bit convoluted: 
    // - there would be two patterns for goals (top sides vs other sides)
    // =====================================================================
    for (int t = 0; t < 19; ++t) {
        for (int e_idx : tilegoals[t]) {
            if (e_idx < goals.size()) {
                tiles[t].addgoal(goals[e_idx]);
            }
        }
    }
    // ============================================================
    // Created algorithm for course_criteria based on tile numbers
    // ============================================================
    for (int t = 0; t < 19; ++t) {
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

ostream &operator<<(ostream &out, const Board &b) {
    out << "                                   |" << b.course_criteria[0].getnum() << "|--" << b.goals[0].getnum() << "--|" << b.course_criteria[1].getnum() << "|" << endl;
    out << "                                   /            \\" << endl;
    out << "                                 " << b.goals[1].getnum() << "      " << b.tiles[0].getTilenum() << "     " << b.goals[2].getnum() << "" << endl;
    out << "                                 /     " << b.tiles[0].getResource() << "\\" << endl;
    out << "                    |" << b.course_criteria[2].getnum() << "|--" << b.goals[3].getnum() << "--|" << b.course_criteria[3].getnum() << "|       " << b.tiles[0].getDice() << "       |" << b.course_criteria[4].getnum() << "|--" << b.goals[4].getnum() << "--|" << b.course_criteria[5].getnum() << "|" << endl;
    out << "                    /            \\                /            \\" << endl;
    out << "                  " << b.goals[5].getnum() << "      " << b.tiles[1].getTilenum() << "     " << b.goals[6].getnum() << "             " << b.goals[7].getnum() << "      " << b.tiles[2].getTilenum() << "     " << b.goals[8].getnum() << "" << endl;
    out << "                  /     " << b.tiles[1].getResource() << "\\            /     " << b.tiles[2].getResource() << "\\" << endl;
    out << "     |" << b.course_criteria[6].getnum() << "|--" << b.goals[9].getnum() << "--|" << b.course_criteria[7].getnum() << "|       " << b.tiles[1].getDice() << "       |" << b.course_criteria[8].getnum() << "|--" << b.goals[10].getnum() << "--|" << b.course_criteria[9].getnum() << "|       " << b.tiles[2].getDice() << "       |" << b.course_criteria[10].getnum() << "|--" << b.goals[11].getnum() << "--|" << b.course_criteria[11].getnum() << "|" << endl;
    out << "     /            \\                /            \\                /            \\" << endl;
    out << "   " << b.goals[12].getnum() << "      " << b.tiles[3].getTilenum() << "     " << b.goals[13].getnum() << "             " << b.goals[14].getnum() << "      " << b.tiles[4].getTilenum() << "     " << b.goals[15].getnum() << "             " << b.goals[16].getnum() << "      " << b.tiles[5].getTilenum() << "     " << b.goals[17].getnum() << "" << endl;
    out << "   /     " << b.tiles[3].getResource() << "\\            /     " << b.tiles[4].getResource() << "\\            /     " << b.tiles[5].getResource() << "\\" << endl;
    out << "|" << b.course_criteria[12].getnum() << "|       " << b.tiles[3].getDice() << "       |" << b.course_criteria[13].getnum() << "|--" << b.goals[18].getnum() << "--|" << b.course_criteria[14].getnum() << "|       " << b.tiles[4].getDice() << "       |" << b.course_criteria[15].getnum() << "|--" << b.goals[19].getnum() << "--|" << b.course_criteria[16].getnum() << "|       " << b.tiles[5].getDice() << "       |" << b.course_criteria[17].getnum() << "|" << endl;
    out << "   \\                /            \\                /            \\                /" << endl;
    out << "   " << b.goals[20].getnum() << "             " << b.goals[21].getnum() << "      " << b.tiles[6].getTilenum() << "     " << b.goals[22].getnum() << "             " << b.goals[23].getnum() << "      " << b.tiles[7].getTilenum() << "     " << b.goals[24].getnum() << "             " << b.goals[25].getnum() << "" << endl;
    out << "     \\            /     " << b.tiles[6].getResource() << "\\            /     " << b.tiles[7].getResource() << "\\            /" << endl;
    out << "     |" << b.course_criteria[18].getnum() << "|--" << b.goals[26].getnum() << "--|" << b.course_criteria[19].getnum() << "|       " << b.tiles[6].getDice() << "       |" << b.course_criteria[20].getnum() << "|--" << b.goals[27].getnum() << "--|" << b.course_criteria[21].getnum() << "|       " << b.tiles[7].getDice() << "       |" << b.course_criteria[22].getnum() << "|--" << b.goals[28].getnum() << "--|" << b.course_criteria[23].getnum() << "|" << endl;
    out << "     /            \\                /            \\                /            \\" << endl;
    out << "   " << b.goals[29].getnum() << "      " << b.tiles[8].getTilenum() << "     " << b.goals[30].getnum() << "             " << b.goals[31].getnum() << "      " << b.tiles[9].getTilenum() << "     " << b.goals[32].getnum() << "             " << b.goals[33].getnum() << "      " << b.tiles[10].getTilenum() << "     " << b.goals[34].getnum() << "" << endl;
    out << "   /     " << b.tiles[8].getResource() << "\\            /     " << b.tiles[9].getResource() << "\\            /     " << b.tiles[10].getResource() << "\\" << endl;
    out << "|" << b.course_criteria[24].getnum() << "|       " << b.tiles[8].getDice() << "       |" << b.course_criteria[25].getnum() << "|--" << b.goals[35].getnum() << "--|" << b.course_criteria[26].getnum() << "|       " << b.tiles[9].getDice() << "       |" << b.course_criteria[27].getnum() << "|--" << b.goals[36].getnum() << "--|" << b.course_criteria[28].getnum() << "|       " << b.tiles[10].getDice() << "       |" << b.course_criteria[29].getnum() << "|" << endl;
    out << "   \\                /            \\                /            \\                /" << endl;
    out << "   " << b.goals[37].getnum() << "             " << b.goals[38].getnum() << "      " << b.tiles[11].getTilenum() << "     " << b.goals[39].getnum() << "             " << b.goals[40].getnum() << "      " << b.tiles[12].getTilenum() << "     " << b.goals[41].getnum() << "             " << b.goals[42].getnum() << "" << endl;
    out << "     \\            /     " << b.tiles[11].getResource() << "\\            /     " << b.tiles[12].getResource() << "\\            /" << endl;
    out << "     |" << b.course_criteria[30].getnum() << "|--" << b.goals[43].getnum() << "--|" << b.course_criteria[31].getnum() << "|       " << b.tiles[11].getDice() << "       |" << b.course_criteria[32].getnum() << "|--" << b.goals[44].getnum() << "--|" << b.course_criteria[33].getnum() << "|       " << b.tiles[12].getDice() << "       |" << b.course_criteria[34].getnum() << "|--" << b.goals[45].getnum() << "--|" << b.course_criteria[35].getnum() << "|" << endl;
    out << "     /            \\                /            \\                /            \\" << endl;
    out << "   " << b.goals[46].getnum() << "      " << b.tiles[13].getTilenum() << "     " << b.goals[47].getnum() << "             " << b.goals[48].getnum() << "      " << b.tiles[14].getTilenum() << "     " << b.goals[49].getnum() << "             " << b.goals[50].getnum() << "      " << b.tiles[15].getTilenum() << "     " << b.goals[51].getnum() << "" << endl;
    out << "   /     " << b.tiles[13].getResource() << "\\            /     " << b.tiles[14].getResource() << "\\            /     " << b.tiles[15].getResource() << "\\" << endl;
    out << "|" << b.course_criteria[36].getnum() << "|       " << b.tiles[13].getDice() << "       |" << b.course_criteria[37].getnum() << "|--" << b.goals[52].getnum() << "--|" << b.course_criteria[38].getnum() << "|       " << b.tiles[14].getDice() << "       |" << b.course_criteria[39].getnum() << "|--" << b.goals[53].getnum() << "--|" << b.course_criteria[40].getnum() << "|       " << b.tiles[15].getDice() << "       |" << b.course_criteria[41].getnum() << "|" << endl;
    out << "   \\                /            \\                /            \\                /" << endl;
    out << "   " << b.goals[54].getnum() << "             " << b.goals[55].getnum() << "      " << b.tiles[16].getTilenum() << "     " << b.goals[56].getnum() << "             " << b.goals[57].getnum() << "      " << b.tiles[17].getTilenum() << "     " << b.goals[58].getnum() << "             " << b.goals[59].getnum() << "" << endl;
    out << "     \\            /     " << b.tiles[16].getResource() << "\\            /     " << b.tiles[17].getResource() << "\\            /" << endl;
    out << "     |" << b.course_criteria[42].getnum() << "|--" << b.goals[60].getnum() << "--|" << b.course_criteria[43].getnum() << "|       " << b.tiles[16].getDice() << "       |" << b.course_criteria[44].getnum() << "|--" << b.goals[61].getnum() << "--|" << b.course_criteria[45].getnum() << "|       " << b.tiles[17].getDice() << "       |" << b.course_criteria[46].getnum() << "|--" << b.goals[62].getnum() << "--|" << b.course_criteria[47].getnum() << "|" << endl;
    out << "                  \\                /            \\                /" << endl;
    out << "                  " << b.goals[63].getnum() << "             " << b.goals[64].getnum() << "      " << b.tiles[18].getTilenum() << "     " << b.goals[65].getnum() << "             " << b.goals[66].getnum() << "" << endl;
    out << "                    \\            /     " << b.tiles[18].getResource() << "\\            /" << endl;
    out << "                    |" << b.course_criteria[48].getnum() << "|--" << b.goals[67].getnum() << "--|" << b.course_criteria[49].getnum() << "|       " << b.tiles[18].getDice() << "       |" << b.course_criteria[50].getnum() << "|--" << b.goals[68].getnum() << "--|" << b.course_criteria[51].getnum() << "|" << endl;
    out << "                                 \\                /" << endl;
    out << "                                 " << b.goals[69].getnum() << "             " << b.goals[70].getnum() << "" << endl;
    out << "                                   \\            /" << endl;
    out << "                                   |" << b.course_criteria[52].getnum() << "|--" << b.goals[71].getnum() << "--|" << b.course_criteria[53].getnum() << "|" << endl;
    return out;
}