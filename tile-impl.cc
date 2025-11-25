module Tile;

import <vector>;
import <string>;

import ISubject;
import Resource;


void Tile::distribute_resources() const {
      Resource resource = Resource(resource_type);
      for (int i = 0; i < 6; ++i) {
        course_criteria[i]->newResource(resource);
      }
    }
Tile::Tile(std::string res, int dc, int num) : resource_type(res), dice(dc), tilenum(num) {}

std::string Tile::getTilenum() const {
    if (tilenum < 10) {
    return " " + std::to_string(tilenum);
    }
    return std::to_string(tilenum);
}

std::string Tile::getResource() const {
    std::string result = resource_type;
    for(int i = 0; i < (11 - resource_type.length()); ++i) {
    result += " ";
    }
    return result;
}

std::string Tile::getDice() const {
    if (dice < 10) {
    return " " + std::to_string(dice);
    }
    return std::to_string(dice);
}
void Tile::addcourse_criterion(ISubject &v) {
    course_criteria.emplace_back(v);
}
void Tile::addgoal(ISubject &e) {
    goals.emplace_back(e);
}