#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Holder {
  int number;
  string displaystr;
  
public:
  Holder(int num, string str) : number(num), displaystr(str) {}
  
  string getnum() {
    if (displaystr != "") {
      return displaystr;
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
  
  string getTilenum() {
    if (tilenum < 10) {
      return " " + to_string(tilenum);
    }
    return to_string(tilenum);
  }
  
  string getResource() {
    string result = resource;
    for(int i = 0; i < (11 - resource.length()); ++i) {
      result += " ";
    }
    return result;
  }
  
  string getDice() {
    if (dice < 10) {
      return " " + to_string(dice);
    }
    return to_string(dice);
  }
};

int main() {
  // testing our board printing
    vector<Holder> corners;
    vector<Holder> edges;
    vector<Tile> tiles;
    for (int i = 0; i < 54; ++i) {
      corners.push_back(Holder(i, ""));
    }
    for (int i = 0; i < 72; ++i) {
      edges.push_back(Holder(i, ""));  
    }
    for (int i = 0; i < 19; i++) {
      tiles.push_back(Tile("LAB", i, i));
    }

    // board printing
    cout << "                                   |" << corners[0].getnum() << "|--" << edges[0].getnum() << "--|" << corners[1].getnum() << "|" << endl;
    cout << "                                   /            \\" << endl;
    cout << "                                 " << edges[1].getnum() << "      "<< tiles[0].getTilenum() << "     " << edges[2].getnum() << "" << endl;
    cout << "                                 /     "<< tiles[0].getResource() <<"\\" << endl;
    cout << "                    |" << corners[2].getnum() << "|--" << edges[3].getnum() << "--|" << corners[3].getnum() << "|       "<< tiles[0].getDice() <<"       |" << corners[4].getnum() << "|--" << edges[4].getnum() << "--|" << corners[5].getnum() << "|" << endl;
    cout << "                    /            \\                /            \\" << endl;
    cout << "                  " << edges[5].getnum() << "      "<< tiles[1].getTilenum() << "     " << edges[6].getnum() << "             " << edges[7].getnum() << "      "<< tiles[2].getTilenum() << "     " << edges[8].getnum() << "" << endl;
    cout << "                  /     "<< tiles[1].getResource() <<"\\            /     "<< tiles[2].getResource() <<"\\" << endl;
    cout << "     |" << corners[6].getnum() << "|--" << edges[9].getnum() << "--|" << corners[7].getnum() << "|       "<< tiles[1].getDice() <<"       |" << corners[8].getnum() << "|--" << edges[10].getnum() << "--|" << corners[9].getnum() << "|       "<< tiles[2].getDice() <<"       |" << corners[10].getnum() << "|--" << edges[11].getnum() << "--|" << corners[11].getnum() << "|" << endl;
    cout << "     /            \\                /            \\                /            \\" << endl;
    cout << "   " << edges[12].getnum() << "      "<< tiles[3].getTilenum() << "     " << edges[13].getnum() << "             " << edges[14].getnum() << "      "<< tiles[4].getTilenum() << "     " << edges[15].getnum() << "             " << edges[16].getnum() << "      "<< tiles[5].getTilenum() << "     " << edges[17].getnum() << "" << endl;
    cout << "   /     "<< tiles[3].getResource() <<"\\            /     "<< tiles[4].getResource() <<"\\            /     "<< tiles[5].getResource() <<"\\" << endl;
    cout << "|" << corners[12].getnum() << "|       "<< tiles[3].getDice() <<"       |" << corners[13].getnum() << "|--" << edges[18].getnum() << "--|" << corners[14].getnum() << "|       "<< tiles[4].getDice() <<"       |" << corners[15].getnum() << "|--" << edges[19].getnum() << "--|" << corners[16].getnum() << "|       "<< tiles[5].getDice() <<"       |" << corners[17].getnum() << "|" << endl;
    cout << "   \\                /            \\                /            \\                /" << endl;
    cout << "   " << edges[20].getnum() << "             " << edges[21].getnum() << "      "<< tiles[6].getTilenum() << "     " << edges[22].getnum() << "             " << edges[23].getnum() << "      "<< tiles[7].getTilenum() << "     " << edges[24].getnum() << "             " << edges[25].getnum() << "" << endl;
    cout << "     \\            /     "<< tiles[6].getResource() <<"\\            /     "<< tiles[7].getResource() <<"\\            /" << endl;
    cout << "     |" << corners[18].getnum() << "|--" << edges[26].getnum() << "--|" << corners[19].getnum() << "|       "<< tiles[6].getDice() <<"       |" << corners[20].getnum() << "|--" << edges[27].getnum() << "--|" << corners[21].getnum() << "|       "<< tiles[7].getDice() <<"       |" << corners[22].getnum() << "|--" << edges[28].getnum() << "--|" << corners[23].getnum() << "|" << endl;
    cout << "     /            \\                /            \\                /            \\" << endl;
    cout << "   " << edges[29].getnum() << "      "<< tiles[8].getTilenum() << "     " << edges[30].getnum() << "             " << edges[31].getnum() << "      "<< tiles[9].getTilenum() << "     " << edges[32].getnum() << "             " << edges[33].getnum() << "      "<< tiles[10].getTilenum() << "     " << edges[34].getnum() << "" << endl;
    cout << "   /     "<< tiles[8].getResource() <<"\\            /     "<< tiles[9].getResource() <<"\\            /     "<< tiles[10].getResource() <<"\\" << endl;
    cout << "|" << corners[24].getnum() << "|       "<< tiles[8].getDice() <<"       |" << corners[25].getnum() << "|--" << edges[35].getnum() << "--|" << corners[26].getnum() << "|       "<< tiles[9].getDice() <<"       |" << corners[27].getnum() << "|--" << edges[36].getnum() << "--|" << corners[28].getnum() << "|       "<< tiles[10].getDice() <<"       |" << corners[29].getnum() << "|" << endl;
    cout << "   \\                /            \\                /            \\                /" << endl;
    cout << "   " << edges[37].getnum() << "             " << edges[38].getnum() << "      "<< tiles[11].getTilenum() << "     " << edges[39].getnum() << "             " << edges[40].getnum() << "      "<< tiles[12].getTilenum() << "     " << edges[41].getnum() << "             " << edges[42].getnum() << "" << endl;
    cout << "     \\            /     "<< tiles[11].getResource() <<"\\            /     "<< tiles[12].getResource() <<"\\            /" << endl;
    cout << "     |" << corners[30].getnum() << "|--" << edges[43].getnum() << "--|" << corners[31].getnum() << "|       "<< tiles[11].getDice() <<"       |" << corners[32].getnum() << "|--" << edges[44].getnum() << "--|" << corners[33].getnum() << "|       "<< tiles[12].getDice() <<"       |" << corners[34].getnum() << "|--" << edges[45].getnum() << "--|" << corners[35].getnum() << "|" << endl;
    cout << "     /            \\                /            \\                /            \\" << endl;
    cout << "   " << edges[46].getnum() << "      "<< tiles[13].getTilenum() << "     " << edges[47].getnum() << "             " << edges[48].getnum() << "      "<< tiles[14].getTilenum() << "     " << edges[49].getnum() << "             " << edges[50].getnum() << "      "<< tiles[15].getTilenum() << "     " << edges[51].getnum() << "" << endl;
    cout << "   /     "<< tiles[13].getResource() <<"\\            /     "<< tiles[14].getResource() <<"\\            /     "<< tiles[15].getResource() <<"\\" << endl;
    cout << "|" << corners[36].getnum() << "|       "<< tiles[13].getDice() <<"       |" << corners[37].getnum() << "|--" << edges[52].getnum() << "--|" << corners[38].getnum() << "|       "<< tiles[14].getDice() <<"       |" << corners[39].getnum() << "|--" << edges[53].getnum() << "--|" << corners[40].getnum() << "|       "<< tiles[15].getDice() <<"       |" << corners[41].getnum() << "|" << endl;
    cout << "   \\                /            \\                /            \\                /" << endl;
    cout << "   " << edges[54].getnum() << "             " << edges[55].getnum() << "      "<< tiles[16].getTilenum() << "     " << edges[56].getnum() << "             " << edges[57].getnum() << "      "<< tiles[17].getTilenum() << "     " << edges[58].getnum() << "             " << edges[59].getnum() << "" << endl;
    cout << "     \\            /     "<< tiles[16].getResource() <<"\\            /     "<< tiles[17].getResource() <<"\\            /" << endl;
    cout << "     |" << corners[42].getnum() << "|--" << edges[60].getnum() << "--|" << corners[43].getnum() << "|       "<< tiles[16].getDice() <<"       |" << corners[44].getnum() << "|--" << edges[61].getnum() << "--|" << corners[45].getnum() << "|       "<< tiles[17].getDice() <<"       |" << corners[46].getnum() << "|--" << edges[62].getnum() << "--|" << corners[47].getnum() << "|" << endl;
    cout << "                  \\                /            \\                /" << endl;
    cout << "                  " << edges[63].getnum() << "             " << edges[64].getnum() << "      "<< tiles[18].getTilenum() << "     " << edges[65].getnum() << "             " << edges[66].getnum() << "" << endl;
    cout << "                    \\            /     "<< tiles[18].getResource() <<"\\            /" << endl;
    cout << "                    |" << corners[48].getnum() << "|--" << edges[67].getnum() << "--|" << corners[49].getnum() << "|       "<< tiles[18].getDice() <<"       |" << corners[50].getnum() << "|--" << edges[68].getnum() << "--|" << corners[51].getnum() << "|" << endl;
    cout << "                                 \\                /" << endl;
    cout << "                                 " << edges[69].getnum() << "             " << edges[70].getnum() << "" << endl;
    cout << "                                   \\            /" << endl;
    cout << "                                   |" << corners[52].getnum() << "|--" << edges[71].getnum() << "--|" << corners[53].getnum() << "|" << endl;

}
