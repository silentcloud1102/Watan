export module Tile;

import <vector>;
import <string>;

import Resource;
import ISubject;
import Goal;
import Criteria;

export class Tile {
  std::string resource_type;
  int dice;
  int tilenum;
  std::vector<Goal*> goals;
  std::vector<Criteria*> course_criteria;
  public:
    void distribute_resources() const;
    Tile(std::string res, int dc, int num);
    std::string getTilenum() const;
    std::string getResource() const;
    std::string getDice() const;
    void addcourse_criterion(Criteria *v);
    void addgoal(Goal *e);
};