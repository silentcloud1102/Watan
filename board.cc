export module Board;

import iostream;
import string;
import vector;
import Criteria;
import Goals;
using namespace std;

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
    public:
        
        Board() {
            // ============================================================
            //  Initialize all objects
            // ============================================================
            for (int i = 0; i < 54; ++i) {
                vertices.emplace_back(i, "");
            }
            for (int i = 0; i < 72; ++i) {
                edges.emplace_back(i, "");
            }
            for (int i = 0; i < 19; ++i) {
                tiles.emplace_back("LAB", i, i);
            }

            const vector<vector<int>> edgeToVertices = {
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
            const vector<vector<int>> edgeAdj = {
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
            //  Assign each edge its adjacent vertices and edges
            // ============================================================
            for (int e = 0; e < 72; ++e) {
                edges[e].addAdjacentVertex(edgeToVertices.at(e));
                edges[e].addAdjacentEdge(edgeAdj.at(e));
            }

            // ============================================================
            // Edge indices for each tile (local array)
            // ============================================================
            const vector<vector<int>> tileEdges = {
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
            // Assign edges to tiles
            //
            // No algorithm since the relationship between the edges are 
            // interesting: 
            // - there would be two patterns for edges (top edges vs side edges)
            // =====================================================================
            for (int t = 0; t < 19; ++t) {
                for (int e_idx : tileEdges[t]) {
                    if (e_idx < edges.size()) {
                        tiles[t].addEdge(edges[e_idx]);
                    }
                }
            }
            // ============================================================
            // Created algorithm for vertices
            // ============================================================
            for (int t = 0; t < 19; ++t) {
                int vertex1 = first_vertex(stoi(tiles[t].getTilenum()));
                int vertex2 = vertex1 + 1;
                int vertex3 = down_vertex_coord(vertex1);
                int vertex4 = vertex3 + 1; 
                int vertex5 = down_vertex_coord(vertex3);
                int vertex6 = vertex5 + 1;
                tiles[t].addVertex(vertices[vertex1]);
                tiles[t].addVertex(vertices[vertex2]);
                tiles[t].addVertex(vertices[vertex3]);
                tiles[t].addVertex(vertices[vertex4]);
                tiles[t].addVertex(vertices[vertex5]);
                tiles[t].addVertex(vertices[vertex6]);
            }
        }
};