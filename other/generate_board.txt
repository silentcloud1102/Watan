#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Vertex {
  int number;
  string displaystr;
public:
  Vertex(int num, string str) : number(num), displaystr(str) {}
  
};

int down_vertex_coord(int n) {
    if (n < 2 || n > 48) {
        return n + 3;
    } else if (n < 6 || n > 42) {
        return n + 5;
    } else {
        return n + 6;
    }
}


class Edge {
    int number;
    string owner;
    std::vector<int> adjacent_vertices;
    std::vector<int> adjacent_edges;
  
    public:
    Edge(int num, string str) : number(num), owner(str) {}
    void addAdjacentVertex(const std::vector<int>& v) { adjacent_vertices = v; }
    void addAdjacentEdge(const std::vector<int>& e) { adjacent_edges = e; }
    string getnum() {
        if (owner != "") {
        return owner;
        }

        if (number < 10) {
        return " " + to_string(number);
        }
        return to_string(number);
    }
};

class Tile {
    string resource;
    int dice;
    int tilenum;

    public:
    Tile(string res, int dc, int num) : resource(res), dice(dc), tilenum(num) {}
    int row_number() const {
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
    int first_vertex() const {
        if (tilenum < 6) {
            return tilenum * 2;
        } else if (tilenum == 18) {
            return 44;
        } else {
            return (tilenum * 2) + (row_number() - 2);
        }
    }
    int first_edge() const {
        int row = row_number();
        if (tilenum == 0) {
            return 0;
        } else if (tilenum == 18) {
            return 61;
        } else if (row == 1) {
            return tilenum + 2;
        } else {
            return tilenum + (6 *(row - 1));
        }
    }
};

class Board {
    public:
        vector<Tile> tiles;
        vector<Edge> edges;
        vector<Vertex> vertices;
        Board() {
                // ============================================================
                //  Initialize all objects
                // ============================================================
                vertices.reserve(54);
                edges.reserve(72);
                tiles.reserve(19);

                for (int i = 0; i < 54; ++i) {
                    vertices.emplace_back(i, "");
                }
                for (int i = 0; i < 72; ++i) {
                    edges.emplace_back(i, "");
                }
                for (int i = 0; i < 19; ++i) {
                    tiles.emplace_back("LAB", i, i);
                }

                const std::vector<std::vector<int>> edgeToVertices = {
                    {0, 1}, {0, 3}, {1, 4}, {2, 3}, {4, 5}, {2, 7}, {3, 8}, {4, 9}, {5, 10}, {6, 7}, {8, 9}, {10, 11},
                    {6, 12}, {7, 13}, {8, 14}, {9, 15}, {10, 16}, {11, 17}, {13, 14}, {15, 16}, {12, 18}, {13, 19},
                    {14, 20}, {15, 21}, {16, 22}, {17, 23}, {18, 19}, {20, 21}, {22, 23}, {18, 24}, {19, 25}, {20, 26},
                    {21, 27}, {22, 28}, {23, 29}, {25, 26}, {27, 28}, {24, 30}, {25, 31}, {26, 32}, {27, 33}, {28, 34},
                    {29, 35}, {30, 31}, {32, 33}, {34, 35}, {30, 36}, {31, 37}, {32, 38}, {33, 39}, {34, 40}, {35, 41},
                    {37, 38}, {39, 40}, {36, 42}, {37, 43}, {38, 44}, {39, 45}, {40, 46}, {41, 47}, {42, 43}, {44, 45},
                    {46, 47}, {43, 48}, {44, 49}, {45, 50}, {46, 51}, {47, 52}, {49, 50}, {48, 49}, {50, 53}, {52, 53}
                };

                // ============================================================
                //  EDGE → ADJACENT EDGES
                // ============================================================
                const std::vector<std::vector<int>> edgeAdj = {
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
                    {56,61,67,69}, {57,61,68,70}, {58,62,68}, {63,64,69}, {65,66,70}, {64,67,71}, {65,68,71}
                };

                // ============================================================
                //  Assign each edge its adjacent vertices and edges
                // ============================================================
                for (int e = 0; e < 72; ++e) {
                    edges[e].addAdjacentVertex(edgeToVertices[e]);  // assign vertices
                    edges[e].addAdjacentEdge(edgeAdj[e]);           // assign adjacent edges
                }
        }
};

ostream &operator<<(ostream &out, Board b) {
    out << "                                   |" << b.vertices[0].getnum() << "|--" << b.edges[0].getnum() << "--|" << b.vertices[1].getnum() << "|" << endl;
    out << "                                   /            \\" << endl;
    out << "                                 " << b.edges[1].getnum() << "      " << b.tiles[0].getTilenum() << "     " << b.edges[2].getnum() << "" << endl;
    out << "                                 /     " << b.tiles[0].getResource() << "\\" << endl;
    out << "                    |" << b.vertices[2].getnum() << "|--" << b.edges[3].getnum() << "--|" << b.vertices[3].getnum() << "|       " << b.tiles[0].getDice() << "       |" << b.vertices[4].getnum() << "|--" << b.edges[4].getnum() << "--|" << b.vertices[5].getnum() << "|" << endl;
    out << "                    /            \\                /            \\" << endl;
    out << "                  " << b.edges[5].getnum() << "      " << b.tiles[1].getTilenum() << "     " << b.edges[6].getnum() << "             " << b.edges[7].getnum() << "      " << b.tiles[2].getTilenum() << "     " << b.edges[8].getnum() << "" << endl;
    out << "                  /     " << b.tiles[1].getResource() << "\\            /     " << b.tiles[2].getResource() << "\\" << endl;
    out << "     |" << b.vertices[6].getnum() << "|--" << b.edges[9].getnum() << "--|" << b.vertices[7].getnum() << "|       " << b.tiles[1].getDice() << "       |" << b.vertices[8].getnum() << "|--" << b.edges[10].getnum() << "--|" << b.vertices[9].getnum() << "|       " << b.tiles[2].getDice() << "       |" << b.vertices[10].getnum() << "|--" << b.edges[11].getnum() << "--|" << b.vertices[11].getnum() << "|" << endl;
    out << "     /            \\                /            \\                /            \\" << endl;
    out << "   " << b.edges[12].getnum() << "      " << b.tiles[3].getTilenum() << "     " << b.edges[13].getnum() << "             " << b.edges[14].getnum() << "      " << b.tiles[4].getTilenum() << "     " << b.edges[15].getnum() << "             " << b.edges[16].getnum() << "      " << b.tiles[5].getTilenum() << "     " << b.edges[17].getnum() << "" << endl;
    out << "   /     " << b.tiles[3].getResource() << "\\            /     " << b.tiles[4].getResource() << "\\            /     " << b.tiles[5].getResource() << "\\" << endl;
    out << "|" << b.vertices[12].getnum() << "|       " << b.tiles[3].getDice() << "       |" << b.vertices[13].getnum() << "|--" << b.edges[18].getnum() << "--|" << b.vertices[14].getnum() << "|       " << b.tiles[4].getDice() << "       |" << b.vertices[15].getnum() << "|--" << b.edges[19].getnum() << "--|" << b.vertices[16].getnum() << "|       " << b.tiles[5].getDice() << "       |" << b.vertices[17].getnum() << "|" << endl;
    out << "   \\                /            \\                /            \\                /" << endl;
    out << "   " << b.edges[20].getnum() << "             " << b.edges[21].getnum() << "      " << b.tiles[6].getTilenum() << "     " << b.edges[22].getnum() << "             " << b.edges[23].getnum() << "      " << b.tiles[7].getTilenum() << "     " << b.edges[24].getnum() << "             " << b.edges[25].getnum() << "" << endl;
    out << "     \\            /     " << b.tiles[6].getResource() << "\\            /     " << b.tiles[7].getResource() << "\\            /" << endl;
    out << "     |" << b.vertices[18].getnum() << "|--" << b.edges[26].getnum() << "--|" << b.vertices[19].getnum() << "|       " << b.tiles[6].getDice() << "       |" << b.vertices[20].getnum() << "|--" << b.edges[27].getnum() << "--|" << b.vertices[21].getnum() << "|       " << b.tiles[7].getDice() << "       |" << b.vertices[22].getnum() << "|--" << b.edges[28].getnum() << "--|" << b.vertices[23].getnum() << "|" << endl;
    out << "     /            \\                /            \\                /            \\" << endl;
    out << "   " << b.edges[29].getnum() << "      " << b.tiles[8].getTilenum() << "     " << b.edges[30].getnum() << "             " << b.edges[31].getnum() << "      " << b.tiles[9].getTilenum() << "     " << b.edges[32].getnum() << "             " << b.edges[33].getnum() << "      " << b.tiles[10].getTilenum() << "     " << b.edges[34].getnum() << "" << endl;
    out << "   /     " << b.tiles[8].getResource() << "\\            /     " << b.tiles[9].getResource() << "\\            /     " << b.tiles[10].getResource() << "\\" << endl;
    out << "|" << b.vertices[24].getnum() << "|       " << b.tiles[8].getDice() << "       |" << b.vertices[25].getnum() << "|--" << b.edges[35].getnum() << "--|" << b.vertices[26].getnum() << "|       " << b.tiles[9].getDice() << "       |" << b.vertices[27].getnum() << "|--" << b.edges[36].getnum() << "--|" << b.vertices[28].getnum() << "|       " << b.tiles[10].getDice() << "       |" << b.vertices[29].getnum() << "|" << endl;
    out << "   \\                /            \\                /            \\                /" << endl;
    out << "   " << b.edges[37].getnum() << "             " << b.edges[38].getnum() << "      " << b.tiles[11].getTilenum() << "     " << b.edges[39].getnum() << "             " << b.edges[40].getnum() << "      " << b.tiles[12].getTilenum() << "     " << b.edges[41].getnum() << "             " << b.edges[42].getnum() << "" << endl;
    out << "     \\            /     " << b.tiles[11].getResource() << "\\            /     " << b.tiles[12].getResource() << "\\            /" << endl;
    out << "     |" << b.vertices[30].getnum() << "|--" << b.edges[43].getnum() << "--|" << b.vertices[31].getnum() << "|       " << b.tiles[11].getDice() << "       |" << b.vertices[32].getnum() << "|--" << b.edges[44].getnum() << "--|" << b.vertices[33].getnum() << "|       " << b.tiles[12].getDice() << "       |" << b.vertices[34].getnum() << "|--" << b.edges[45].getnum() << "--|" << b.vertices[35].getnum() << "|" << endl;
    out << "     /            \\                /            \\                /            \\" << endl;
    out << "   " << b.edges[46].getnum() << "      " << b.tiles[13].getTilenum() << "     " << b.edges[47].getnum() << "             " << b.edges[48].getnum() << "      " << b.tiles[14].getTilenum() << "     " << b.edges[49].getnum() << "             " << b.edges[50].getnum() << "      " << b.tiles[15].getTilenum() << "     " << b.edges[51].getnum() << "" << endl;
    out << "   /     " << b.tiles[13].getResource() << "\\            /     " << b.tiles[14].getResource() << "\\            /     " << b.tiles[15].getResource() << "\\" << endl;
    out << "|" << b.vertices[36].getnum() << "|       " << b.tiles[13].getDice() << "       |" << b.vertices[37].getnum() << "|--" << b.edges[52].getnum() << "--|" << b.vertices[38].getnum() << "|       " << b.tiles[14].getDice() << "       |" << b.vertices[39].getnum() << "|--" << b.edges[53].getnum() << "--|" << b.vertices[40].getnum() << "|       " << b.tiles[15].getDice() << "       |" << b.vertices[41].getnum() << "|" << endl;
    out << "   \\                /            \\                /            \\                /" << endl;
    out << "   " << b.edges[54].getnum() << "             " << b.edges[55].getnum() << "      " << b.tiles[16].getTilenum() << "     " << b.edges[56].getnum() << "             " << b.edges[57].getnum() << "      " << b.tiles[17].getTilenum() << "     " << b.edges[58].getnum() << "             " << b.edges[59].getnum() << "" << endl;
    out << "     \\            /     " << b.tiles[16].getResource() << "\\            /     " << b.tiles[17].getResource() << "\\            /" << endl;
    out << "     |" << b.vertices[42].getnum() << "|--" << b.edges[60].getnum() << "--|" << b.vertices[43].getnum() << "|       " << b.tiles[16].getDice() << "       |" << b.vertices[44].getnum() << "|--" << b.edges[61].getnum() << "--|" << b.vertices[45].getnum() << "|       " << b.tiles[17].getDice() << "       |" << b.vertices[46].getnum() << "|--" << b.edges[62].getnum() << "--|" << b.vertices[47].getnum() << "|" << endl;
    out << "                  \\                /            \\                /" << endl;
    out << "                  " << b.edges[63].getnum() << "             " << b.edges[64].getnum() << "      " << b.tiles[18].getTilenum() << "     " << b.edges[65].getnum() << "             " << b.edges[66].getnum() << "" << endl;
    out << "                    \\            /     " << b.tiles[18].getResource() << "\\            /" << endl;
    out << "                    |" << b.vertices[48].getnum() << "|--" << b.edges[67].getnum() << "--|" << b.vertices[49].getnum() << "|       " << b.tiles[18].getDice() << "       |" << b.vertices[50].getnum() << "|--" << b.edges[68].getnum() << "--|" << b.vertices[51].getnum() << "|" << endl;
    out << "                                 \\                /" << endl;
    out << "                                 " << b.edges[69].getnum() << "             " << b.edges[70].getnum() << "" << endl;
    out << "                                   \\            /" << endl;
    return out << "                                   |" << b.vertices[52].getnum() << "|--" << b.edges[71].getnum() << "--|" << b.vertices[53].getnum() << "|" << endl;
}

    // out << "                                   |" << corners[0].getnum() << "|--" << edges[0].getnum() << "--|" << corners[1].getnum() << "|" << endl;
    // out << "                                   /            \\" << endl;
    // out << "                                 " << edges[1].getnum() << "      "<< tiles[0].getTilenum() << "     " << edges[2].getnum() << "" << endl;
    // out << "                                 /     "<< tiles[0].getResource() <<"\\" << endl;
    // out << "                    |" << corners[2].getnum() << "|--" << edges[3].getnum() << "--|" << corners[3].getnum() << "|       "<< tiles[0].getDice() <<"       |" << corners[4].getnum() << "|--" << edges[4].getnum() << "--|" << corners[5].getnum() << "|" << endl;
    // out << "                    /            \\                /            \\" << endl;
    // out << "                  " << edges[5].getnum() << "      "<< tiles[1].getTilenum() << "     " << edges[6].getnum() << "             " << edges[7].getnum() << "      "<< tiles[2].getTilenum() << "     " << edges[8].getnum() << "" << endl;
    // out << "                  /     "<< tiles[1].getResource() <<"\\            /     "<< tiles[2].getResource() <<"\\" << endl;
    // out << "     |" << corners[6].getnum() << "|--" << edges[9].getnum() << "--|" << corners[7].getnum() << "|       "<< tiles[1].getDice() <<"       |" << corners[8].getnum() << "|--" << edges[10].getnum() << "--|" << corners[9].getnum() << "|       "<< tiles[2].getDice() <<"       |" << corners[10].getnum() << "|--" << edges[11].getnum() << "--|" << corners[11].getnum() << "|" << endl;
    // out << "     /            \\                /            \\                /            \\" << endl;
    // out << "   " << edges[12].getnum() << "      "<< tiles[3].getTilenum() << "     " << edges[13].getnum() << "             " << edges[14].getnum() << "      "<< tiles[4].getTilenum() << "     " << edges[15].getnum() << "             " << edges[16].getnum() << "      "<< tiles[5].getTilenum() << "     " << edges[17].getnum() << "" << endl;
    // out << "   /     "<< tiles[3].getResource() <<"\\            /     "<< tiles[4].getResource() <<"\\            /     "<< tiles[5].getResource() <<"\\" << endl;
    // out << "|" << corners[12].getnum() << "|       "<< tiles[3].getDice() <<"       |" << corners[13].getnum() << "|--" << edges[18].getnum() << "--|" << corners[14].getnum() << "|       "<< tiles[4].getDice() <<"       |" << corners[15].getnum() << "|--" << edges[19].getnum() << "--|" << corners[16].getnum() << "|       "<< tiles[5].getDice() <<"       |" << corners[17].getnum() << "|" << endl;
    // out << "   \\                /            \\                /            \\                /" << endl;
    // out << "   " << edges[20].getnum() << "             " << edges[21].getnum() << "      "<< tiles[6].getTilenum() << "     " << edges[22].getnum() << "             " << edges[23].getnum() << "      "<< tiles[7].getTilenum() << "     " << edges[24].getnum() << "             " << edges[25].getnum() << "" << endl;
    // out << "     \\            /     "<< tiles[6].getResource() <<"\\            /     "<< tiles[7].getResource() <<"\\            /" << endl;
    // out << "     |" << corners[18].getnum() << "|--" << edges[26].getnum() << "--|" << corners[19].getnum() << "|       "<< tiles[6].getDice() <<"       |" << corners[20].getnum() << "|--" << edges[27].getnum() << "--|" << corners[21].getnum() << "|       "<< tiles[7].getDice() <<"       |" << corners[22].getnum() << "|--" << edges[28].getnum() << "--|" << corners[23].getnum() << "|" << endl;
    // out << "     /            \\                /            \\                /            \\" << endl;
    // out << "   " << edges[29].getnum() << "      "<< tiles[8].getTilenum() << "     " << edges[30].getnum() << "             " << edges[31].getnum() << "      "<< tiles[9].getTilenum() << "     " << edges[32].getnum() << "             " << edges[33].getnum() << "      "<< tiles[10].getTilenum() << "     " << edges[34].getnum() << "" << endl;
    // out << "   /     "<< tiles[8].getResource() <<"\\            /     "<< tiles[9].getResource() <<"\\            /     "<< tiles[10].getResource() <<"\\" << endl;
    // out << "|" << corners[24].getnum() << "|       "<< tiles[8].getDice() <<"       |" << corners[25].getnum() << "|--" << edges[35].getnum() << "--|" << corners[26].getnum() << "|       "<< tiles[9].getDice() <<"       |" << corners[27].getnum() << "|--" << edges[36].getnum() << "--|" << corners[28].getnum() << "|       "<< tiles[10].getDice() <<"       |" << corners[29].getnum() << "|" << endl;
    // out << "   \\                /            \\                /            \\                /" << endl;
    // out << "   " << edges[37].getnum() << "             " << edges[38].getnum() << "      "<< tiles[11].getTilenum() << "     " << edges[39].getnum() << "             " << edges[40].getnum() << "      "<< tiles[12].getTilenum() << "     " << edges[41].getnum() << "             " << edges[42].getnum() << "" << endl;
    // out << "     \\            /     "<< tiles[11].getResource() <<"\\            /     "<< tiles[12].getResource() <<"\\            /" << endl;
    // out << "     |" << corners[30].getnum() << "|--" << edges[43].getnum() << "--|" << corners[31].getnum() << "|       "<< tiles[11].getDice() <<"       |" << corners[32].getnum() << "|--" << edges[44].getnum() << "--|" << corners[33].getnum() << "|       "<< tiles[12].getDice() <<"       |" << corners[34].getnum() << "|--" << edges[45].getnum() << "--|" << corners[35].getnum() << "|" << endl;
    // out << "     /            \\                /            \\                /            \\" << endl;
    // out << "   " << edges[46].getnum() << "      "<< tiles[13].getTilenum() << "     " << edges[47].getnum() << "             " << edges[48].getnum() << "      "<< tiles[14].getTilenum() << "     " << edges[49].getnum() << "             " << edges[50].getnum() << "      "<< tiles[15].getTilenum() << "     " << edges[51].getnum() << "" << endl;
    // out << "   /     "<< tiles[13].getResource() <<"\\            /     "<< tiles[14].getResource() <<"\\            /     "<< tiles[15].getResource() <<"\\" << endl;
    // out << "|" << corners[36].getnum() << "|       "<< tiles[13].getDice() <<"       |" << corners[37].getnum() << "|--" << edges[52].getnum() << "--|" << corners[38].getnum() << "|       "<< tiles[14].getDice() <<"       |" << corners[39].getnum() << "|--" << edges[53].getnum() << "--|" << corners[40].getnum() << "|       "<< tiles[15].getDice() <<"       |" << corners[41].getnum() << "|" << endl;
    // out << "   \\                /            \\                /            \\                /" << endl;
    // out << "   " << edges[54].getnum() << "             " << edges[55].getnum() << "      "<< tiles[16].getTilenum() << "     " << edges[56].getnum() << "             " << edges[57].getnum() << "      "<< tiles[17].getTilenum() << "     " << edges[58].getnum() << "             " << edges[59].getnum() << "" << endl;
    // out << "     \\            /     "<< tiles[16].getResource() <<"\\            /     "<< tiles[17].getResource() <<"\\            /" << endl;
    // out << "     |" << corners[42].getnum() << "|--" << edges[60].getnum() << "--|" << corners[43].getnum() << "|       "<< tiles[16].getDice() <<"       |" << corners[44].getnum() << "|--" << edges[61].getnum() << "--|" << corners[45].getnum() << "|       "<< tiles[17].getDice() <<"       |" << corners[46].getnum() << "|--" << edges[62].getnum() << "--|" << corners[47].getnum() << "|" << endl;
    // out << "                  \\                /            \\                /" << endl;
    // out << "                  " << edges[63].getnum() << "             " << edges[64].getnum() << "      "<< tiles[18].getTilenum() << "     " << edges[65].getnum() << "             " << edges[66].getnum() << "" << endl;
    // out << "                    \\            /     "<< tiles[18].getResource() <<"\\            /" << endl;
    // out << "                    |" << corners[48].getnum() << "|--" << edges[67].getnum() << "--|" << corners[49].getnum() << "|       "<< tiles[18].getDice() <<"       |" << corners[50].getnum() << "|--" << edges[68].getnum() << "--|" << corners[51].getnum() << "|" << endl;
    // out << "                                 \\                /" << endl;
    // out << "                                 " << edges[69].getnum() << "             " << edges[70].getnum() << "" << endl;
    // out << "                                   \\            /" << endl;
    // return out << "                                   |" << corners[52].getnum() << "|--" << edges[71].getnum() << "--|" << corners[53].getnum() << "|" << endl;

int main() {
    Board b;
    // board printing
    cout << b;
}