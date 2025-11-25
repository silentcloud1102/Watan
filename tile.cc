export module Tile;

import <vector>;
import <string>;

import Goals;
import Criterion;
import Resource;

class Tile {
  std::string resource_type;
  int dice;
  int tilenum;
  std::vector<*ISubject> goals;
  std::vector<*ISubject> course_criteria;
  public:
    void distribute_resources() const;
    Tile(std::string res, int dc, int num);
    std::string getTilenum() const;
    std::string getResource() const;
    std::string getDice() const;
    void addcourse_criterion(Criterion &v);
    void addgoal(Goal &e);
};