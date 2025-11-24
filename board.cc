export module Board;

import <iostream>;
import <string>;
import <vector>;
import Criteria;
import Goals;
import Tiles;

int down_vertex_coord(int n) {
    if (n < 2 || n > 48) {
        return n + 3;
    } else if (n < 6 || n > 42) {
        return n + 5;
    } else {
        return n + 6;
    }
}

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
int first_vertex(int tilenum) {
    if (tilenum < 6) {
        return tilenum * 2;
    } else if (tilenum == 18) {
        return 44;
    } else {
        return (tilenum * 2) + (row_number(tilenum) - 2);
    }
}


export class Board {
    std::vector<Tile> tiles;
    std::vector<Goal> goals;
    std::vector<Criteria> course_criteria;
    public:
        Board(std::string seed = "");
};

friend ostream &operator<<(ostream &out, const Board &b);