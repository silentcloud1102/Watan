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
    // Constructor
    Tile(std::string res, int dc, int num);

    // get methods for printing
    std::string get_tilenum() const;
    std::string get_resource() const;
    std::string get_dice() const;

    // set-up methods used by board
    void add_criteria(Criteria *v);
    void add_goal(Goal *e);

    // send resources to Criteria
    void distribute_resources() const;
};