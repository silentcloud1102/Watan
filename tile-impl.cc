module Tile;

import <vector>;
import <string>;

import Goals;
import Criterion;
import Resource;


void Tile::distribute_resources() const {
      resource = Resource(resource_type);
      for (int i = 0; i < 6; ++i) {
        course_criteria[i]->newResource(resource);
      }
    }
Tile::Tile(std::string res, int dc, int num) : resource_type(res), dice(dc), tilenum(num) {}

std::string Tile::getTilenum() const {
    if (tilenum < 10) {
    return " " + to_std::string(tilenum);
    }
    return to_std::string(tilenum);
}

std::string Tile::getResource() const {
    std::string result = resource_type;
    for(int i = 0; i < (11 - resource.length()); ++i) {
    result += " ";
    }
    return result;
}

std::string Tile::getDice() const {
    if (dice < 10) {
    return " " + to_string(dice);
    }
    return to_string(dice);
}
void Tile::addcourse_criterion(Criterion &v) {
    course_criteria.emplace_back(v);
}
void Tile::addgoal(Goal &e) {
    goals.emplace_back(e);
}