export module Tile;


class Tile {
  public:
  string resource;
  int dice;
  int tilenum;
  vector<goal> goals;
  vector<course_criterion> course_criteria;

  Tile(string res, int dc, int num) : resource(res), dice(dc), tilenum(num) {}
  
  string getTilenum() const {
    if (tilenum < 10) {
      return " " + to_string(tilenum);
    }
    return to_string(tilenum);
  }
  
  string getResource() const {
    string result = resource;
    for(int i = 0; i < (11 - resource.length()); ++i) {
      result += " ";
    }
    return result;
  }
  
  string getDice() const {
    if (dice < 10) {
      return " " + to_string(dice);
    }
    return to_string(dice);
  }
  void addcourse_criterion(const course_criterion &v) {
    course_criteria.emplace_back(v);
  }
  void addgoal(const goal &e) {
    goals.emplace_back(e);
  }
};