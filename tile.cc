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
    void distribute_resources() const {
      resource = Resource(resource_type);
      for (int i = 0; i < 6; ++i) {
        course_criteria[i]->newResource(resource);
      }
    }
    Tile(std::string res, int dc, int num) : resource_type(res), dice(dc), tilenum(num) {}
    
    std::string getTilenum() const {
      if (tilenum < 10) {
        return " " + to_std::string(tilenum);
      }
      return to_std::string(tilenum);
    }
    
    std::string getResource() const {
      std::string result = resource_type;
      for(int i = 0; i < (11 - resource.length()); ++i) {
        result += " ";
      }
      return result;
    }
    
    std::string getDice() const {
      if (dice < 10) {
        return " " + to_string(dice);
      }
      return to_string(dice);
    }
    void addcourse_criterion(const Criterion &v) {
      course_criteria.emplace_back(v);
    }
    void addgoal(const Goal &e) {
      goals.emplace_back(e);
    }
};